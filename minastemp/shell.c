#include "shell.h"

/**
 * main - shell
 * Return: 0
 */

int main(void)
{
	char *buffer = NULL, **line;
	size_t bufsize = 0;
	pid_t pid;
	while(1)
	{
		write(STDOUT_FILENO, "$>", 2);
		getline(&buffer, &bufsize, stdin);
		//_history(buffer);
		line = tokenize(buffer, " ");
		if (!line)
			perror("mem allocation failed");
		//checkforbuiltin(line)
		if (cmdchk(line))
		{
			if(!(pid = fork()))
				execve(line[0], line, NULL);
			_putstring("program executed");
		}

	}
	return (0);
}
