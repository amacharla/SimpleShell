#include "shell.h"

/**
 * main - shell
 * Return: 0
 */

int main(void)
{
	char *buffer = NULL, **tokens;
	size_t bufsize = 0;
	pid_t pid;
	int status, check;

	while(1)
	{
		_putstring("$---->");
		getline(&buffer, &bufsize, stdin);
		/*_history(buffer);*/
		tokens = tokenize(buffer, " ");
		if (!tokens)
			perror("mem allocation failed");
		/*checkforbuiltin(line)*/
		if (cmdchk(tokens))
		{
			pid = fork();
			if (pid == -1)
				perror("failed to fork");
			if (pid == 0)
			{
				check = execve(tokens[0], tokens, NULL);
				if (check == -1)
					_exit(EXIT_FAILURE);
			}
			else
				wait(&status);
		}
		else
			_putstring("command not found\n");
	}
	return (0);
}
