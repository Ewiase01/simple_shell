#include "sheel.h"

/**
 * is_interactive - checks if shell is in interactive mode
 *
 * @pew: pointer to the pew struct
 *
 * Return: 1 if interactive mode, else return 0
 */
int _is_interactive(_aww *pew)
{
	return (isatty(STDIN_FILENO) && pew->readfd <= 2);
}

/**
 * is_delimiter - checks if character is a delimiter
 *
 * @c: the character to check
 * @d: the delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char c, char *d)
{
	for (int i = 0; d[i] != '\0'; i++)
	{
		if (d[i] == c)
			return (i);
	}
	return (0);
}

/**
 * is_alpha - checks if character is an alphabetic character
 *
 * @y: the character to check
 *
 * Return: 1 if y is alphatic, else return 0
 */
int is_alpha(int y)
{
	int i;

	for (i = 'a'; i <= 'z'; i++)
	{
		if (y == i)
			return (1);
	}

	for (i = 'A'; i <= 'z'; i++)
	{
		if (y == i)
			return (1);
	}

	return (0);
}

/**
 * _atoi - converts a string to an integer
 *
 * @s: the string to be converted
 *
 * Return: 0 if no numbers is in string, converted number if otherwise
 */
int _atoi(char *s)
{
	int a, b = 1, c = 0, x;
	unsigned int m = 0;

	for (a = 0; s[a] != '\0' && c != 2; a++)
	{
		if (s[a] == '-')
			b *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			c = 1;
			m *= 10;
			m += (s[a] - '0');
		}
		else if (c == 1)
			c = 2;
	}

	if (b == -1)
		x = -m;
	else
		x = m;

	return (x);
}
