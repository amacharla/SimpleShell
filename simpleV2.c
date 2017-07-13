#include "shell.h"

/**
 * main - shell
 * Return: 0
 */

int main(void)
{
<<<<<<< HEAD
	extern char **environ;
=======
>>>>>>> 2c10a3472eddd3389008bc918458029c0764b125
	char *buffer = NULL, **line;
	size_t bufsize = 0;
	pid_t pid;
	int status;

	while(1)
	{
		_putstring("$>");
		getline(&buffer, &bufsize, stdin);
		//_history(buffer);
		line = tokenize(buffer, " ");
		if (!line)
			perror("mem allocation failed");
		//checkforbuiltin(line)
		if (cmdchk(line))
		{
			pid = fork();
			if (pid == -1)
				perror("failed to fork");
			else if (pid > 0)
				waitpid(pid, &status, 0);
			else
			{
				execve(line[0], line, environ);
				_exit(EXIT_FAILURE);
			}
		}
<<<<<<< HEAD
		else
			_putstring("command not found");
=======

>>>>>>> 2c10a3472eddd3389008bc918458029c0764b125
	}
	return (0);
}
