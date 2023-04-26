#include "shell.h"

/**
 * find_command - searches for a command in the PATH environment variable
 * @command: the name of the command to search for
 *
 * Return: a string containing the full path to the command, 
 * or NULL if not found
 */
char *find_command(char *command)
{
	char *path, *dir, *fullpath;
	struct stat st;

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	dir = strtok(path, ":");
	while (dir)
	{
		fullpath = build_path(dir, command);
		if (stat(fullpath, &st) == 0)
		{
			free(path);
			return (fullpath);
		}
		free(fullpath);
		dir = strtok(NULL, ":");
	}

	free(path);
	return (NULL);
}

/**
 * build_path - concatenates a directory and a command to create a full path
 * @dir: the directory
 * @command: the command
 *
 * Return: a string containing the full path, or NULL on failure
 */
char *build_path(char *dir, char *command)
{
	char *path;
	size_t len1, len2, len;

	len1 = strlen(dir);
	len2 = strlen(command);
	len = len1 + len2 + 2;
	path = malloc(sizeof(char) * len);
	if (!path)
		return (NULL);

	sprintf(path, "%s/%s", dir, command);
	path[len - 1] = '\0';
	return (path);
}

/**
 * execute_command - executes a command with arguments
 * @command: the command and arguments to execute
 * @envp: the environment variables
 *
 * Return: the status of the executed command
 */
int execute_command(char **command, char **envp)
{
	char *fullpath;
	pid_t child_pid;
	int status;

	fullpath = find_command(command[0]);
	if (!fullpath)
	{
		_eputs("command not found\n");
		return (127);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(fullpath);
		return (1);
	}

	if (child_pid == 0)
	{
		execve(fullpath, command, envp);
		perror("execve");
		free(fullpath);
		exit(127);
	}

	wait(&status);
	free(fullpath);
	return (status);
}
