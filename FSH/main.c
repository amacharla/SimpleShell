#include "shellHeader.h"
#define UNUSED(x) (void)(x)
/**
 * main - Entry point for hsh
 * @argc: attribute unused
 * @argv: attribute unused
 * @env: used to pass enviroment conf to functions
 * Return: Success or Failure
 */
int main(int argc, char **argv, char **env)
{
	char **tokens, *buffer = NULL;
	size_t bufsize = 0;
	int check, isCmd, count = 1;

	UNUSED(argc), UNUSED(argv);
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
		tokens = tokenize(buffer, " ");/*TOKENIZE & COMMAND CHECK*/
		if (tokens == NULL)
		{
			perror("tokenize() Failed");
			/*_alloc(&buffer, -1);*/
		}
		if (_strncmp(tokens[0], "exit", 4))
			exit(EXIT_SUCCESS);
		isCmd = cmdchk(tokens, env);/*Check if cmd and if special cmd*/
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
