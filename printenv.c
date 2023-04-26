#include "shell.h"

/**
 * _printenv - print the environment variables
 * @env: the array of environment variables
 *
 * Return: 0 on success, 1 on failure
 */
int _printenv(char **env)
{
	int i;

	if (!env)
		return (1);

	for (i = 0; env[i]; i++)
		_puts(env[i]);

	return (0);
}

/**
 * env_builtin - implementation of the env built-in command
 * @args: arguments to the command
 * @env: array of environment variables
 *
 * Return: 0 on success, 1 on failure
 */
int env_builtin(char **args, char **env)
{
	(void) args;

	return (_printenv(env));
}
