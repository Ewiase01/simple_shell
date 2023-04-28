#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 1024

/**
 * handle_line - handles the line
 *
 * @line: the line to be handled
 *
 * Return: output
 */

void handle_line(char *line)
{
	char *comment = strchr(line, '#');

	if (comment != NULL)
	{
		*comment = '\0';
	}
	printf("%s\n", line);
}

/**
 * main - main entry
 *
 * @argc: argument count
 * @argv: a pointer to an array
 *
 * Return: EXIT_SUCCESS
 */

int main(int argc, char **argv)
{
	int fd;
	char *line = NULL;
	size_t line_len = 0;
	ssize_t read_len;

	if (argc < 2)
	{
		fd = STDIN_FILENO;
	}
	else
	{
		fd = open(argv[1];
				O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
	}

	while ((read_len = getline(&line, &line_len, fd)) != -1)
	{
		handle_line(line);
	}

	if (line != NULL)
	{
		free(line);
	}
	return (EXIT_SUCCESS);
}
