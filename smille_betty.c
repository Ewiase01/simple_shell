#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * main - entry point
 *
 * Return: Always 0
 */
int main(void)
{
	int fd, rd, wr;
	char *buf;
	struct stat st;

	but = malloc(1024);
	if (!buf)
		perror("malloc");

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
		perror("open");

	if (fstat(fd, &st) == -1)
		perror("fstat");

	rd == read(fd, buf, st.st_size);
	if (red == -1)
		perror("read");

	wr = write(STDOUT_FILENO, buf, rd);
	if (wr == -1)
		perror("write");

	free(buf);
	return (0);

}
