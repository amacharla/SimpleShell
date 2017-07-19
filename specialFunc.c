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
		if (tokens[1][1] != '\0')
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

	if (tokens[1] == NULL)
		check = chdir(_getenv("HOME", env));
	else
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

/**
 * cp - function that copies the content of a file to another file
 * @copy: first argument (file name) to copy from
 * @paste: second argument (creates files and copies content)
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int _cp(char **tokens)
{
	int fdC, fdP, count;
	char *copy = tokens[1], *paste = tokens[2];
	char buffer[1024];

	if (copy == NULL || paste == NULL)
	{
		perror("CP: Invalid arguments");
		return (EXIT_FAILURE);
	}
	fdC = open(copy, O_RDONLY);
	fdP = open(paste, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (fdC == -1 || fdP == -1)
		return (EXIT_FAILURE);

	do {/*read multiple times if more content then given size*/
	count = read(fdC, buffer, 1024);
	if (count != 0)
		count = write(fdP, buffer, count);
	if (count == -1)
		break;
	} while (count); /*untill count becomes 0*/

	count = close(fdC), count = close(fdP);
	if (count == -1)
	{
		perror("CP Failed");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
