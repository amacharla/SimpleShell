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
		{'c', print_char}, {'s', print_string},
		{'d', print_number}, {'\0', NULL}
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

ssize_t _getline(char **lineptr, size_t *n)
{
	ssize_t readcount;
	size_t bytes = 100, maxbytes = 1024, i;
	char *buffer;

	if (*n > 1)
		bytes = *n;
	if (*lineptr == NULL)
		buffer = malloc(sizeof(char) * maxbytes);
	else
		buffer = *lineptr;

	do {
		readcount = read(STDIN_FILENO, buffer, bytes);
		if (readcount == -1)
			return (-1);
		for (i = 0; buffer[i]; i++)
		{
			if (buffer[i] == '\n' || buffer[i] == '\t')
				buffer[i] = '\0';
		}
		if (buffer[i] == '\0')
		{
			buffer = _realloc(buffer, 0, i);
			break;
		}
		i++;
	} while (1);

	*lineptr = buffer;
	n = &i;
	return ((ssize_t) bytes);

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

	if (str == NULL && i == 0)/*if str is null and never been run before*/
		return (NULL);
	if (str != NULL)/*during the first run*/
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
					i--;/*replace delim with null*/
					token[i] = '\0';
					token = _realloc(token, 0, i);/*realloc to required amount*/
					if (statictok == NULL || token == NULL)
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
 * specialExec - executes special cmds func like echo, cd, set, unset
 * @tokens: command and its arguments
 * @env: current enviroment
 * @controller: point to the right special function to execute the cmd
 * Return: SUCCESS or FAILURE
 */
int specialExec(char **tokens, char **env, int controller)
{
	int check;

	/*if cmd is null or controller is <= 0*/
	if (tokens[0] == NULL || controller <= 0)
		return (EXIT_FAILURE);

	if (controller == 1)/* ECHO */
		check = _echo(tokens, env);
	else if (controller == 2)/* CD */
		check = _cd(tokens, env);
	else if (controller == 3)/* ENV */
		check = _env(env);
	else if (controller == 4)/* HISTORY */
		check = history(env);
	else if (controller == 5)/* CP */
		check = _cp(tokens);
	/*else if (controller = 6) SET
		check = _set(tokens, env);*/
	/*else if (controller = 7) UNSET
		check = _unset(tokens, env);*/
	else/* ADD MORE SPECIAL CASES */
	{
		perror("Special Execution Failed");
		return (EXIT_FAILURE);
	}

	if (check == EXIT_FAILURE)
	{
		perror("Special Execution Failed");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * signal_handler - handle a signal
 * @s: signal no
 */
void signal_handler(int s)
{
	if (s == SIGINT)
		_printf("\n$ ");
}
