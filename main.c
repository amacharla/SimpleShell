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
	int check, isCmd, count = 1, interactive = 0, j = 0;
	struct stat sb;

	UNUSED(argc), UNUSED(argv);

	signal(SIGINT, signal_handler);
	if (fstat(STDIN_FILENO, &sb) == -1)
	{
		perror("Fstat error");
		_exit(EXIT_FAILURE);
	}
	if ((sb.st_mode & S_IFMT) == (S_IFIFO || S_IFREG))
		interactive = 1;
	if (!interactive)
		_printf("$ ");
	while (getline(&buffer, &bufsize, stdin) != -1)
	{
		history_file(buffer, env);
		tokens = tokenize(buffer, " ");/*TOKENIZE & COMMAND CHECK*/
		if (tokens == NULL)
		{
			perror("tokenize() Failed");
			/*_alloc(&buffer, -1);*/
		}
		if (!_strcmp(tokens[0], "exit"))
			_exit(EXIT_SUCCESS);
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
		if (!interactive)
			_printf("$ ");
		count++;
		fflush(stdin);
		free(buffer);
		while(tokens[j])
			free(tokens[j]), j++;
	}
	return (EXIT_SUCCESS);
}
