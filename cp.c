#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define size 1204

int cp(char *copy, char *paste);
/**
 * main - entry point and error handling
 * @argc: argument count
 * @argv: arguments after command being executed
 * Return: 0 Success else exit with error code and message
 */
int main(int argc, char **argv)
{
	int errorCheck;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	if (argv[1] && argv[2])
		errorCheck = cp(argv[1], argv[2]);
	switch (errorCheck)
	{
	case 98:
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	case 99:
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		exit(99);
	default:
		return (0);
	}
	return (0);
}
/**
 * cp - function that copies the content of a file to another file
 * @copy: first argument (file name) to copy from
 * @paste: second argument (creates files and copies content)
 * Return: 0- success |98, 99 -read and write fails|exits if cant close fd
 */
int cp(char *copy, char *paste)
{
	int fd, fdC, fdP, count, check, check2;
	char buffer[size];

	fdC = open(copy, O_RDONLY);
	fdP = open(paste, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (fdC == -1 || fdP == -1)
		return (fdC == -1 ? 98 : 99);

	do {/*read multiple times if more content then given size*/
	count = read(fdC, buffer, size);
	if (count == -1)
		return (98);
	if (count != 0)
		check = write(fdP, buffer, count);
	if (check == -1)
		return (99);
	} while (count); /*untill count becomes 0*/

	check = close(fdC), check2 = close(fdP);
	if (check == -1 || check2 == -1)
	{
		fd = ((check == -1) ? fdC : fdP);
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd), exit(100);
	}
	return (0);
}
