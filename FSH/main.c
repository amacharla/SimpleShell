#include "shellHeader.h"

int main(int argc, char **argv, char**env)
{
	(void)(argc);
	(void)(argv);
	char *buffer = NULL, **tokens;
	size_t bufsize = 0;
	pid_t pid;
	int status, check;

	while (1)
	{
		_putsstring("$");
		check = getline(&buffer, &bufsize, stdin);
		if (check == -1 && bufer == NULL)
		{
			perror("getline() Failed");
			_alloc(&buffer, -1);
			return (EXIT_FAILURE);
		}
		tokens = tokenize(buffer, " ");
		if (tokens == NULL)
		{
			perror("tokenize() Failed");
			_alloc(&buffer, -1);
		}
		else
			isCmd = cmdchk(tokens[0]);
		if (isCmd == 1)
		{
			cmd = _addpath(tokens[0]);
			isSpecial = _specialchk(tokens);

			if (isSpecial == 0)
				check = cmdExec(cmd, tokens);
			else
				check = specialExec(cmd, tokens);

			if (check == -1)
			{
				perror("Execution Failed");
				_alloc(&tokens, -1);
				return (EXIT_FAILURE);
			}
		}
		else
		{
			_putstring("hsh: %d: tokens[0]: not found\n",
		}

	}
}
