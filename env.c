#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - main entry
 *
 * @argc: argument
 * @argv: pointer
 * @envp: pointer
 *
 * Return: Always 0
 */
int main(int argc, char *argv[], char *envp[])
{
	char **env;

	for (env = envp; *env != 0; env++)
	{
		printf("%s\n", *env);
	}
	return (0);
}
