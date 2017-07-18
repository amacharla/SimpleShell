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
		_printf("$ ");
		check = getline(&buffer, &bufsize, stdin);
		if (check == -1 && buffer == NULL)
		{
			perror("getline() Failed");
			/*_alloc(&buffer, -1);*/
			exit(EXIT_FAILURE);
		}
		/*TOKENIZE & COMMAND CHECK*/
		tokens = tokenize(buffer, " ");
		if (tokens == NULL)
		{
			perror("tokenize() Failed");
			/*_alloc(&buffer, -1);*/
		}
		if (_strncmp(tokens[0], "exit", 4))
			exit(EXIT_SUCCESS);
		/*Check if cmd and if special cmd*/
		isCmd = cmdchk(tokens, env);

		if (isCmd == 0)/*COMMAND EXECUTION*/
			check = cmdExec(tokens, env);
		else if (isCmd >= 1)/*SPECIAL CMD EXECUTION*/
			check = specialExec(tokens, env, isCmd);
		else/*NO COMMAND FOUND*/
		{
			_printf("hsh: %d: %s: not found\n", count, tokens[0]);
			/*_alloc(&buffer, -1);*/
		}

		if (check == EXIT_FAILURE)
		{
			perror("Execution Failed");
			/*_alloc(NULL, -1);*/
			exit(EXIT_FAILURE);
		}
		count++;
	}
	return (EXIT_SUCCESS);
}
