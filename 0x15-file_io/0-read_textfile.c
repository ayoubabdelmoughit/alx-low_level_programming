#include "main.h"
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
	int fille;
	int length, wrotechar;
	char *buff;

	if (filename == NULL || letters == 0)
		return (0);
	buff = malloc(sizeof(char) * (letters));
	if (buff == NULL)
		return (0);

	fille = open(filename, O_RDONLY);
	if (fille == -1)
	{
		free(buff);
		return (0);
	}
	length = read(fifle, buff, letters);
	if (length == -1)
	{
		free(buff);
		close(fille);
		return (0);
	}

	wrotechar = write(STDOUT_FILENO, buff, length);

	free(buff);
	close(fille);
	if (wrotechar != length)
		return (0);
	return (length);
}
