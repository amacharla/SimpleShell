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
		check = getline(&buffer, &bufsize, stdin);
		if (check == -1 && buffer == NULL)
			perro("Getline failed");
		/*_history(buffer);*/
		tokens = tokenize(buffer, " ");
		if (!tokens)
			perror("Memory Allocation Failed");
		/*checkforbuiltin(line)*/
		if (cmdchk(tokens))
		{
			pid = fork();
			if (pid == -1)
				perror("Failed to Fork");
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
			_putstring("Command Not Found\n");
	}
	return (status);
}
