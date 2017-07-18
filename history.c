#include "shellHeader.h"
/**
 * history_file - creates the history file or appends to it
 * @filename: name of file to create
 * @text_content: text to add in file
 * Return: returns 1 on succesm , -1 on failure
 */
int history_file(const char *filename, char *text_content)
{
	int c, fd, i = 0;

	if (filename == NULL)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (-1);
	if (text_content == NULL || text_content[0] == '\0')
	{
		close(fd);
		return (1);
	}
	while (text_content[i])
		i++;
	c = write(fd, text_content, i);
	if (c == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

/**
 * history -  reads the history and prints it to stdout
 * @filename: name of history file
 * Return: returns 1 if success or 0 if fail
 */
int history(const char *filename)
{
	int c, fd, i = 1;
	char text[1024], *buf;

	fd = open(filename, O_RDONLY);
	while (c)
	{
	c = read(fd, text, 1024);
	if (c == -1)
		return (0);
	if (i == 1)
		_printf("0  ");
	buf = strtok(text, "\n");
	while (buf)
	{
		_printf("%s", buf);
		_printf("%d  ", i);
		buf = strtok(NULL, "\n");
		i++;
	}
	}
	return (1);
}
