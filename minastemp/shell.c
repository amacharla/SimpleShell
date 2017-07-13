#include "shell.h"

/**
 * main - shell
 * Return: 0
 */

int main(void)
{
	extern char **environ;
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
		else
			_putstring("command not found");
	}
	return (0);
}
