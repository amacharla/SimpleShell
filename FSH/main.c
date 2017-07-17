#include "shellHeader.h"

int main(int argc, char **argv, char**env)
{
	(void)(argc);
	(void)(argv);
	char *buffer = NULL, **tokens, *cmd;
	size_t bufsize = 0;
	pid_t pid;
	int status, check, isCmd, count = 1;

	while (1)
	{	/*GET INPUT*/
		_printf("$");
		check = getline(&buffer, &bufsize, stdin);
		if (check == -1 && buffer == NULL)
		{
			perror("getline() Failed");
			/*_alloc(&buffer, -1);*/
			return (EXIT_FAILURE);
		}
		/*TOKENIZE & COMMAND CHECK*/
		tokens = tokenize(buffer, " ");
		if (tokens == NULL)
		{
			perror("tokenize() Failed");
			/*_alloc(&buffer, -1);*/
		}
		/*Check if cmd and if special cmd*/
		isCmd = cmdchk(tokens, env);

		if (isCmd == 1)/*COMMAND EXECUTION*/
			check = cmdExec(tokens, env);
		else if (isCmd == 2)/*SPECIAL CMD EXECUTION*/
			check = specialExec(tokens, env);
		else/*NO COMMAND FOUND*/
		{
			_printf("hsh: %d: %s: not found\n", count, tokens[0]);
			/*_alloc(&buffer, -1);*/
		}

		if (check == -1)
		{
			perror("Execution Failed");
			/*_alloc(NULL, -1);*/
			return (EXIT_FAILURE);
		}
		count++;
	}
	return (EXIT_SUCCESS);
}
