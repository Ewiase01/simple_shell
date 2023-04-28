#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 64

/**
 * main - main entry
 */
int main(void)
{
	char *line = NULL;
	char *args[MAX_ARGS];
	int status;

	while (1)
	{
		printf("Shell> ");
		if (getline(&line, &MAX_CMD_LENGTH, stdin) == -1)
		{
			printf("Exiting shell...\n");
			break;
		}

		int argc = 0;
		char *token = strtok(line, " \n");
		while (token != NULL && argc < MAX_ARGS - 1)
		{
			args[argc++] = token;
			token = strtok(NULL, " \n");
		}
		args[argc] = NULL;

		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
		} else if (pid == 0)
		{

			if (execvp(args[0], args) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		} else
		{

			waitpid(pid, &status, 0);
		}
	}

	free(line);
	exit(EXIT_SUCCESS);
}
