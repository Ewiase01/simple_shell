#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\r\n\a"

/**
 * shell_loop - main loop that reads command lines and executes them
 */
void shell_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("$ ");
		line = read_line();
		args = split_line(line);
		status = execute(args);

		free(line);
		free(args);
	} while (status);
}

/**
 * read_line - read a line of input from stdin
 *
 * Return: the line read (including newline), or NULL on error or EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
			perror("read_line");
	}

	return (line);
}

/**
 * split_line - split a line into arguments
 * @line: the line to split
 *
 * Return: an array of pointers to the arguments, terminated by a NULL pointer
 */
char **split_line(char *line)
{
	int bufsize = BUFFER_SIZE, pos = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "split_line: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIM);
	while (token)
	{
		tokens[pos++] = token;

		if (pos >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "split_line: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIM);
	}

	tokens[pos] = NULL;
	return (tokens);
}

/**
 * execute - execute a command with arguments
 * @args: the command and arguments
 *
 * Return: 1 to continue the loop, 0 to exit
 */
int execute(char **args)
{
	if (!args[0])
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0);

	return (launch(args));
}

/**
 * launch - launch a command with arguments in a new process
 * @args: the command and arguments
 *
 * Return: 1 to continue the loop, 0 to exit
 */
int launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("launch");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("launch");
	}
	else
	{

		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while  (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
