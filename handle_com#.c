#include "shell.h"

/**
 * prompt - Print prompt and get user input.
 */
void prompt(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	printf("($) ");

	if (getline(&line, &len, stdin) == -1)
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		exit(EXIT_SUCCESS);
	}

	if (line[0] != '#' && line[0] != '\n')
	{
		/* Tokenize the input line */
		char **args = malloc(sizeof(char *) * (read + 1));

		if (args == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		tokenize(line, args);

		/* Execute the command */
		if (execute(args) == -1)
		{
			fprintf(stderr, "Command not found\n");
		}

		/* Free memory */
		free(args);
	}

	free(line);
}

/**
 * tokenize - Tokenize a string into arguments.
 * @line: Input string to tokenize.
 * @args: Array of pointers to store the arguments.
 */
void tokenize(char *line, char **args)
{
	int i = 0;
	char *token = strtok(line, " \t\n");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}

	args[i] = NULL;
}

/**
 * execute - Execute a command.
 * @args: Array of pointers to the command and its arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		/* Child process */
		if (execvp(args[0], args) == -1)
		{
			perror("execvp error");
			_exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		/* Error */
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (0);
}

/**
 * sighandler - Signal handler for Ctrl+C.
 * @sig_num: Signal number caught.
 */
void sighandler(int sig_num)
{
	signal(SIGINT, sighandler);
	fflush(stdout);
}

/**
 * main - Entry point.
 * @argc: Argument count.
 * @argv: Array of pointers to arguments.
 *
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	/* Check if running in interactive mode */
	if (isatty(STDIN_FILENO))
	{
		signal(SIGINT, sighandler);

		while (1)
		{
			prompt();
		}
	}
	/* Non-interactive mode */
	else
	{
