#include "shellHeader.h"
/**
 * history_file - creates the history file or appends to it
 * @filename: name of file to create
 * @text_content: text to add in file
 * Return: returns 1 on succesm , -1 on failure
 */
int history_file(char *text_content, char **env)
{
	int c, fd, i = 0, status;
	char *filename = ".simple_shell_history";
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		chdir(_getenv("HOME", env));
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (fd == -1)
			return (EXIT_FAILURE);
		if (text_content == NULL || text_content[0] == '\0')
		     {
			     close(fd);
			     return (EXIT_FAILURE);
		     }
		while (text_content[i])
			i++;
		c = write(fd, text_content, i);
		if (c == -1)
		{
			close(fd);
			return (EXIT_FAILURE);
		}
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
		wait(&status);
	return (EXIT_SUCCESS);
}

/**
 * history -  reads the history and prints it to stdout
 * @filename: name of history file
 * Return: returns 1 if success or 0 if fail
 */
int history(char **env)
{
	int c = 1, fd, i = 0, status;
	char text[1024], *buf, *filename = ".simple_shell_history";
	pid_t pid;

	pid = fork();
	if (pid == -1)
                return (EXIT_FAILURE);
        if (pid == 0)
	{
		chdir(_getenv("HOME", env));/*history file in home dir*/
		fd = open(filename, O_RDONLY);/*open file to read*/
		while (c)
		{
			c = read(fd, text, 1024);/*read from history file*/
			if (c == -1)
				return (EXIT_FAILURE);
			if (c != 0)
			{
				buf = strtok(text, "\n");
				while (buf && *buf != EOF)
				{
				       	_printf("%d  %s\n", i, buf);
					buf = strtok(NULL, "\n\0EOF");
					i++;
				}
			}
		}
		exit(EXIT_SUCCESS);
	}
	else
		wait(&status);
	return (EXIT_SUCCESS);
}
