#include "shell.h"

/**
 * built_exit - Exits the shell
 * @args: The arguments passed to the built-in
 *
 * Return: Always returns 0
 */
int built_exit(char **args)
{
	free(args);
	exit(0);
}

while (1)
{

	printf("$ ");
	fflush(stdout);
	fgets(command, MAX_COMMAND_LENGTH, stdin);

	command[strcspn(command, "\n")] = '\0';

	char* token = strtok(command, " ");

	int i = 0;

	while (token != NULL && i < MAX_ARGS - 1)
	{
        	args[i++] = token;
        	token = strtok(NULL, " ");
	}

	args[i] = NULL;


    if (strcmp(args[0], "exit") == 0)
	{
        	built_exit(args);
	}


	pid_t pid = fork();

	if (pid == 0)
	{
		execvp(args[0], args);
		perror("execvp");
		exit(1);
	}
	else if (pid < 0) 
	{
		perror("fork");
	}
	else 
	{
		waitpid(pid, &status, 0);
	}
}
