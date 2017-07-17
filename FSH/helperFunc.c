#include "shellHeader.h"
/**
 * tokenize -  splits string into smaller strings
 * and palces them in an array
 * @string: string being examined
 * @delimiter: where the sting is being split
 * Return: array of char pointers representing tokens
 */
char **tokenize(char *string, const char *delimiter)
{
	char **tokens, *token, *arguments;
	size_t i, numtokens = 1;

	/* duplicates string so we can manipulate it*/
	arguments = _strdup(string);
	if (arguments == NULL)
		return (NULL);
	/*go through string and count the delimiters*/
	for (i = 0; arguments[i]; i++)
		if (arguments[i] == *delimiter)
			numtokens++;
	/*allocate space in char *array  to hold tokens from string*/
	tokens = malloc(sizeof(char *) * (numtokens + 1));
	if (tokens == NULL)
		return (NULL);
	/*get each token and store it in char *array*/
	token = strtok(arguments, delimiter);
	for (i = 0; token; i++)
	{
		token = cutspecial(token);/*===================MAKE FUNCTION TO CUT OF NEWLINE, TAB========*/
		tokens[i] = token;
		token = strtok(NULL, delimiter);
		_alloc(&tokens[i], 1); /* ADDED TO MEMORY STORAGE*/
	}
	tokens[i] = NULL;

	return (tokens);

}

char *cutspecial(char *string)
{
	int i, j;
	char special[] = {'\n', '\t', 0};

	if (string == NULL)
		return (NULL);
	for (i = 0; string[i]; i++)
	{
		for (j = 0; special[j]; j++)
			if (string[i] == special[j])
				string[i] = '\0';
	}

	return (string);
}
/**
 * _getenv - gets desired enviroment variable
 * @name: KEY
 * @environ: enviroment variables
 * Return: VALUE (string)
 */
char *_getenv(char *name, char **environ)
{
	char *value;
	unsigned int i;

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)))
		{
			/*make space for the VALUE*/
			value = malloc(sizeof(char) * _strlen(environ[i]) - _strlen(name));
			if (!value)
				return (NULL);
			_strcpy(value, environ[i]);
			value = strtok(value, "=");/*cut off key*/
			value = strtok(NULL, "\0");/*get value*/
			_alloc(&value, 1);/* ADDED TO MEMORY STORAGE */
			return (value);
		}
	}
	return (NULL);
}
/**
 * cmdchk - checks in PATH if the first token is an executiable.
 * @token: first token
 * @environ: enviroment variables
 * Return: -1 Failure | 0 no cmd | 1 cmd | 2 special cmd
 */
int cmdchk(char **tokens, char **environ)
{
	int i = 0, controller = 0;
	char **paths, *path, *cmd;
	char *special [] = {"echo", "cd", "set", "unset", 0};

	path = _getenv("PATH", environ);
	if (!path)
		return (-1);
	paths = tokenize(path, ":");
	if (!paths)
		return (-1);
	cmd = _strdup(tokens[0]);
	while (paths[i])
	{
		tokens[0] = _addpath(paths[i], cmd);
		if (!access(tokens[0], F_OK))/*if path found*/
		{
			controller = 1;
			break;
		}
		i++;
	}
	for (i = 0; special[i]; i++)
	{
		if ((strcmp(cmd, special[i]) == 0))/*if special*/
		{
			controller = 2;
			break;
		}
	}
	return (controller);
}
