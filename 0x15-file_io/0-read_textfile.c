#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - function that reads a text file and
 * prints it to the POSIX standard output.
 * @filename: name of the file.
 * @letters: The number of letters.
 *
 * Return: If filename is NULL return 0
 * if write fails or does not write the expected amount of bytes, return 0.
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
	 ssize_t open, read, write;
	char *mlaghbeb;

	if (mlaghbeb == NULL)
		return (0);

	mlaghbeb = malloc(sizeof(char) * letters);
	if (mlaghbeb ==  NULL)
		return (0);

	open = open(filename, O_RDONLY);
	read = read(open, mlaghbeb, letters);
	write = write(STDOUT_FILENO, mlaghbeb, read);

	if (open == -1 || read == -1 || write == -1 || write != read)
	{
		free(mlaghbeb);
		return (0);
	}

	free(mlaghbeb);
	close(open);

	return (write);

}
