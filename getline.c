#include "shell.h"

/**
 * _memcpy - copies a memory area from src to dest
 * @dest: pointer to the destination buffer
 * @src: pointer to the source buffer
 * @n: number of bytes to copy
 *
 * Return: pointer to the destination buffer
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;

	while (n--)
	*d++ = *s++;

	return (dest);
}


/**
 * _getline - read a line of input from the user
 *
 * Return: pointer to the line read, or NULL on failure
 */
char *_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int pos = 0;
	int n;

	while (1)
	{
	if (pos >= n)
	{
		pos = 0;
		n = read(STDIN_FILENO, buffer, BUFFER_SIZE);

		if (n <= 0)
		{
			return (NULL);
		}
        }


		for (; pos < n; pos++)
		{
			if (buffer[pos] == '\n')
			{
			char *line = malloc(pos + 1);

				if (!line)
				{
					perror("malloc");
					return NULL;
				}
				_memcpy(line, buffer, pos);
				line[pos] = '\0';
				pos++;
				return (line);
			}
		}

	}
}
