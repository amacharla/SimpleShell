#include "shell.h"

char *_strdup(char *str)
{
	char *a;
	int i, j;

	if (str == NULL)
		return (NULL);
	/* length of str */
	for (i = 0; str[i]; i++)
		;
	i++; /*include null character*/
	/*allocating memory for a*/
	a = malloc(i * sizeof(char));
	/*checks if memory is allocated and if str is null*/
	if (a == NULL)
		return (NULL);
	/*coping string*/
	for (j = 0; j < i && str[j] != '\n'; j++)
		a[j] = str[j];
	a = realloc(a, j);
	if (a == NULL)
		return (NULL);
	return (a);
}

char *_getenv(char *name)
{
        extern char **environ;
        char *token;
        unsigned int i;

        for(i = 0; environ[i]; i++)
        {
		if (_strncmp(environ[i], name, _strlen(name)))
		{
			token = malloc(sizeof(char) * _strlen(environ[i]) - _strlen(name) + 1);
			if (!token)
				return (NULL);
			_strcpy(token, environ[i]);
			token = strtok(token, "=");/*cut of key*/
			token = strtok(NULL, "\0");/*get value*/
			return (token);
                }
        }
        return (NULL);
}


char **tokenize(char *string, const char *delimiter)
{
	char **tokens, *token, *arguments;
	size_t i, numtokens = 1;

	/* duplicates string so we can manipulate it*/
	arguments = _strdup(string);
	if (arguments == NULL)
		return (NULL);
	/*go through string and count the delimiters*/
	for(i = 0; arguments[i]; i++)
		if (arguments[i] == *delimiter)
			numtokens++;
	/*allocate space in char *array  to hold tokens from string*/
	tokens = malloc(sizeof(char *) * (numtokens + 1));
	if (tokens == NULL)
		return (NULL);
	/*get each token and store it in char *array*/
	token = strtok(arguments, delimiter);
	for(i = 0; token; i++)
	{
		tokens[i] = token;
		token = strtok(NULL, delimiter);
	}
	tokens[i] = NULL;

	return (tokens);

}

int cmdchk(char **line)
{
	extern char **environ;
	int i = 0;
	char **paths, *path = _getenv("PATH"), *cmd;

	if (!path)
		return(-1);
	paths = tokenize(path, ":");
	if (!paths)
		return (-1);
	cmd = _strdup(line[0]);
	while (paths[i])
	{
		line[0] = _addpath(paths[i], cmd);
		if(!access(line[0], F_OK))
			return (1);
		i++;
	}
	return (0);
}

/**
 * _addpath - adds path to filname
 * @first: pointer to path
 * @second: pointer to filename
 * Return: pointer to merged string or NULL if fails
 */
char *_addpath(char *first,char *second)
{
        int i, j, k;
        char *new;

        for (i = 0; first[i]; i++)
                ;
        for (j = 0; second[j]; j++)
		;
        k = i + j;
        new = (char *) malloc(k * sizeof(char));
        if (!new)
                return(NULL);
        for (i = 0; first[i]; i++)
		new[i] = first[i];
        new[i] = '/';
        i++;
        for (j = 0; i < k; j++)
	{
		new[i] = second[j];
		i++;
	}
        new[i] = '\0';
	return (new);
}

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
		token = strdup(str);/*duplicate string*/

		for(i = 0; token[i]; i++)/*loop through token*/
		{
			for (j = 0; delim[j]; j++)/*loop through delim*/
			{
				if (token[i] == delim[j])/*if match*/
				{
					i++;/*duplicate remainder of token for latter access*/
					statictok = strdup(&token[i]);
					if (statictok == NULL)
						return (NULL);
					i--;/*replace delim with null*/
					token[i] = '\0';
					/*realloc to required amount*/
					token = realloc(token, i);
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
