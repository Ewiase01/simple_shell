#include "shell.h"


/**
 * _puts - prints a string to stdout
 * @str: the string to be printed
 *
 * Return: the number of characters printed
 */
int _puts(char *str)
{
	int len = 0;

	while (*str)
	{
		len += write(STDOUT_FILENO, str, 1);
		str++;
	}

	return (len);
}


/**
 * print_env - prints the environment variables
 * @env: the array of environment variables
 *
 * Return: 0 on success, 1 on failure
 */
int print_env(char **env)
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

	return (print_env(env));
}
