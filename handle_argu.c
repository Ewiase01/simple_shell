#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGS 10
#define MAX_LINE_LENGTH 1024

void execute_command(char **args);

/**
 * main - main entry
 *
 * Return: Always 0
 */

int main(void)
{
	char *args[MAX_ARGS];
	char line[MAX_LINE_LENGTH];

	while (1)
	{
		printf("> ");
		fflush(stdout);

		if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL)
		{
			break;
		}

		int num_args = 0;
		char *token = strtok(line, " \n");

		while (token != NULL && num_args < MAX_ARGS)
		{
			args[num_args++] = token;
			token = strtok(NULL, " \n");
		}

		if (num_args == 0)
		{
			continue;
		}

		if (strcmp(args[0], "cd") == 0)
		{
			if (num_args != 2)
			{
				fprintf(stderr, "Usage: cd <directory>\n");
			}
			else if (chdir(args[1]) != 0)
			{
				perror("chdir");
			}
			continue;
		}

		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			execute_command(args);
			exit(EXIT_FAILURE);
		} else
		{
			int status;

			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
			}
		}
	}

	return (0);
}

/**
 * execute_command - excutes a command
 *
 * @args: pointer
 */
void execute_command(char **args)
{
	if (access(args[0], X_OK) == -1)
	{
		perror(args[0]);
		exit(EXIT_FAILURE);
	}

	if (execvp(args[0], args) == -1)
	{
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
}
