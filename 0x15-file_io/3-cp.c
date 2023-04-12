#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
/**
 * close_errchk - closes a file descriptor and prints
 * an error message if it fails
 *
 * @fd: file descriptor to close
 *
 * Return: 0 on success, -1 on failure
 */
int close_erchk(int fd)
{
	int error;

	error = close(fd);
	if (error == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		return (100);
	}
	return (0);
}

/**
 * write_err - error handler for a write error
 *
 * @fd1: first descriptor to close
 * @fd2: second descriptor to close
 * @filename: filename prompting the error
 *
 * Return: 99
 */
int write_error(int fd1, int fd2, char *filename)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", filename);
	close_erchk(fd1);
	close_erchk(fd2);
	return (99);
}

/**
 * read_err - error handler for a read error
 *
 * @fd1: first descriptor to close
 * @fd2: second descriptor to close
 * @filename: filename prompting the error
 *
 * Return: 98
 */
int read_error(int fd1, int fd2, char *filename)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", filename);
	close_erchk(fd1);
	close_erchk(fd2);
	return (98);
}

/**
 * main - copy one file to another, new file with perms 664
 * usage - cp file_from file_to
 *
 * @ac: number of arg
 * @av: list of args
 *
 * Return: 97 if incorrect num of args
 * 98 if file_from does not exist or unreadable
 * 99 if write fails
 * 100 if file close fails
 * 0 otherwise
 */
int main(int argc, char *argv[])
{
	char buffur[1024];
	int lenghtr, lenghtw, file_from, file_to, error;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		return (97);
	}
	file_from = open(argv[1], O_RDONLY);
	if (file_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n",
			argv[1]);
		return (98);
	}
	file_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC,
		       S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (file_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
		close_erchk(file_from);
		return (99);
	}
	do {
		lenghtr = read(file_from, buffur, 1024);
		if (lenghtr == -1)
			return (read_error(file_from, file_to, argv[1]));
		lenghtw = write(file_to, buffur, lenghtr);
		if (lenghtw == -1 || lenghtw != lenghtr)
			return (write_error(file_from, file_to, argv[2]));
	} while (lenghtr == 1024);
	error = close_erchk(file_from);
	error += close_erchk(file_to);
	if (error != 0)
		return (100);
	return (0);
}
