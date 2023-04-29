#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * change_directory - changes directory
 *
 * @path: the path
 */
void change_directory(char *path)
{
	char cwd[BUFFER_SIZE];

	if (strcmp(path, "-") == 0)
	{
		path = getenv("OLDPWD");
		if (path == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return;
		}
		printf("%s\n", path);
	}
	if (chdir(path) == -1)
	{
		perror("cd");
	} else
	{
		setenv("OLDPWD", getcwd(cwd, sizeof(cwd)), 1);
		setenv("PWD", path, 1);
	}
}

/**
 * main - main entry
 *
 * @argc: argument
 * @argv: pointer
 *
 * Return: 0 or 1 on success
 */
int main(int argc, char *argv[])
{
	char *path = NULL;

	if (argc == 1)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
	}
	else if (argc == 2)
	{
		path = argv[1];
	} else
	{
		fprintf(stderr, "cd: too many arguments\n");
		return (1);
	}
	change_directory(path);
	return (0);
}
