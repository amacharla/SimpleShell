#include "shellHeader.h"

/**
** _printf - gives output
** @format: char
** Return: num of chars
**/
int _printf(const char *format, ...)
{
	unsigned int i, j, count;
	char mod;
	va_list arguments;

	pstruct print_func [] = {
		{'c', print_char}, {'s', print_string}, {'i', print_number},
		{'d', print_number}, {'%', print_percent}, {'\0', NULL}
	};
	va_start(arguments, format);
	i = 0, j = 0, count = 0;
	while (format && format[i])
	{
		if (!(format[i] == '%' && format[i + 1]))
			{_putchar(format[i]); count++; i++; continue; } /*move to next argument*/
		mod = format[i + 1];
		while (print_func[j].type)
		{
			if (print_func[j].type == mod)
			{
				count += print_func[j].printer(arguments);
				i++;
				break;
			}
			j++;
		}
		if (print_func[j].type == '\0')
		{
			_putchar('%');
			_putchar(mod);
			count += 2;
			i++; /*move past %*/
		}
		j = 0; /*reset transverse for type if matched or hits null*/
		i++; /*move past mod*/
	}
	va_end(arguments);
	return (count);
}

/**
 * _strtok - splits string based of delimiter
 * Uses Static var to remember string.
 * @str: input string thats duplicated and modified
 * @delim: delimiter used to break the duplicated string
 * Return: individual tokens or NULL if fails
 */
char *_strtok(char *str, const char *delim)
{
	static char *statictok;
	static size_t i;
	char *token;
	size_t j;

	/*if str is null and never been run before*/
	if (str == NULL && i == 0)
		return (NULL);

	/*during the first run*/
	if (str != NULL)
	{
		token = _strdup(str);/*duplicate string*/

		for (i = 0; token[i]; i++)/*loop through token*/
		{
			for (j = 0; delim[j]; j++)/*loop through delim*/
			{
				if (token[i] == delim[j])/*if match*/
				{
					i++;/*duplicate remainder of token for latter access*/
					statictok = _strdup(&token[i]);
					if (statictok == NULL)
						return (NULL);
					i--;/*replace delim with null*/
					token[i] = '\0';
					/*realloc to required amount*/
					token = _realloc(token, 0, i);
					if (token == NULL)
						return (NULL);
					return (token);
				}
				if (token[i] == '\n')/*no match but when string ends in \n*/
				{
					free(statictok);/*free static token1 used to save remainder*/
					return (token);
				}
			}
		}
		if (token == NULL)/*no match return duplicate copy*/
		{
			free(statictok);
			return (token);
	}
	}
	if (str == NULL)/*strtok(NULL,delim); access rest of tokens*/
		return (_strtok(statictok, delim));/*use previously saved remainder*/

	return (NULL);
}

/**
 * cmdExec - execute executables found in PATH
 * @tokens: command and arguments
 * @env: current enviroment
 * Return: Status or Failure
 */
int cmdExec(char **tokens, char **env)
{
	pid_t pid;
	int status, check;

	pid = fork();
	if (pid == -1)
		perror("Failed to Fork");
	if (pid == 0)
	{
		check = execve(tokens[0], tokens, env);
		if (check == -1)
			_exit(EXIT_FAILURE);
	}
	else
		wait(&status);

	return (status);
}

/**
 * specialExec - executes special cmds like echo, cd, set, unset
 * @tokens: command and its arguments
 * @env: current enviroment
 * Return: SUCCESS or FAILURE
 */
int specialExec(char **tokens, char **env)
{
	pid_t pid;
	int status, check, i = 0;
	char *value, *cmd = NULL;
	char *special [] = {"echo", "cd", "set", "unset", 0};

	do {/*searches string for special commands*/
		cmd = _strstr(tokens[0], special[i]);
		i++;
	} while (cmd == NULL);/*if none found str returns NULL*/
	i--;/*special identifier*/
	if (i == 0)/* ECHO */
	{
		if (_strstr(tokens[1], "$") != NULL)
		{
			value = &tokens[1][1];/*set KEY after $*/
			tokens[1] = _getenv(value, env); /*replace KEY with VALUE*/
		}
		check = cmdExec(tokens, env);/*regulary execute cmd*/
		if (check == -1)
		{
			perror("Echo EXECUTION Failed");
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	else if (i == 1)/* CD */
		check = chdir(tokens[1]);
		if (check == -1)
		{
			perror("CD Failed");
			return (EXIT_FAILURE);
		}
	else/* ADD MORE SPECIAL CASES */
	{
		perror("EXECUTION Failed");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
