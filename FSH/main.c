#include "shellHeader.h"

int main(int argc, char **argv, char**env)
{
	(void)(argc);
	(void)(argv);
	char *buffer = NULL, **tokens;
	size_t bufsize = 0;
	pid_t pid;
	int status, check, count = 1;

	while (1)
	{	/*GET INPUT*/
		_printf("$");
		check = getline(&buffer, &bufsize, stdin);
		if (check == -1 && bufer == NULL)
		{
			perror("getline() Failed");
			_alloc(&buffer, -1);
			return (EXIT_FAILURE);
		}
		/*TOKENIZE & COMMAND CHECK*/
		tokens = tokenize(buffer, " ");
		if (tokens == NULL)
		{
			perror("tokenize() Failed");
			_alloc(&buffer, -1);
		}
		else
			isCmd = cmdchk(tokens[0], env);
		if (isCmd == 1)/*COMMAND EXECUTION*/
		{
			cmd = _addpath(tokens[0]);
			isSpecial = _specialchk(tokens);

			if (isSpecial == 0)/*not special*/
				check = cmdExec(cmd, tokens);
			else/*is special*/
				check = specialExec(cmd, tokens);

			if (check == -1)
			{
				perror("Execution Failed");
				_alloc(&tokens, -1);
				return (EXIT_FAILURE);
			}
		}
		else/*NO COMMAND FOUND*/
		{
			_printf("hsh: %d: %s: not found\n", count, tokens[0]);
			_alloc(&buffer, -1);
		}
		count++;
	}
	return (EXIT_SUCCESS);
}
