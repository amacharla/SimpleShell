#include "shellHeader.h"
/**
 * _echo - prints sys varables, stdin, pid
 * @tokens: command and arguments
 * @env: enviroment variables used for getenv()
 * Return: SUCCESS or FAILURE
 */
int _echo(char **tokens, char **env)
{
	pid_t pid;
	char *value;
	int check;

	if (_strstr(tokens[1], "$") != NULL)/*get enviroment var*/
	{
		if (tokens[1][1] == '$')
		{
			pid = getpid();
			_printf("%d\n", (int) pid);
			return (EXIT_SUCCESS);
		}
		else
		{
			value = &tokens[1][1];/*set KEY after $*/
			tokens[1] = _getenv(value, env); /*replace KEY with VALUE*/
		}
	}
	else if (_strstr(tokens[1], "*") != NULL)/* ls current directory*/
	{
		tokens[0] = "ls";
		tokens[1] = ".";
		if (cmdchk(tokens, env) != 0)
			return (EXIT_FAILURE);
	}

	check = cmdExec(tokens, env);/*execute cmd which updated tokens*/
	if (check == EXIT_FAILURE)
	{
		perror("Echo Execution Failed");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * _cd - changes directory
 * @tokens: command and arguments
 * @env: enviroment variables used for getenv()
 * Return: SUCCESS or FAILURE
 */
int _cd(char **tokens, char **env)
{
	int check;
	(void)(env);

	check = chdir(tokens[1]);
	if (check == -1)
	{
		perror("CD Failed");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * _env - prints enviroment
 * @env: enviroment variables used for getenv()
 * Return: SUCCESS or FAILURE
 */
int _env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
		_printf("%s\n", env[i]);
	return (EXIT_SUCCESS);
}
