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
	for (j = 0; j < i; j++)
		a[j] = str[j];
	return (a);
}

char *_getenv(char *name)
{
        extern char **environ;
        char *token, *env;
        unsigned int i;

        for(i = 0; environ[i]; i++)
        {
		if (_strncmp(environ[i], name, _strlen(name)))
		{
			token = malloc(sizeof(char) * _strlen(environ[i]) - _strlen(name) + 1);
			if (!token)
				return (NULL);
			_strcpy(token, environ[i]);
			token = strtok(token, "=");
			token = strtok(NULL, "\0");
			return (token);
                }
        }
        return (NULL);
}


char **tokenize(char *string, const char *delimiter)
{
	char **tokens, *token, *arguments;
	size_t i, numtokens = 0;

	/* duplicates string so we can manipulate it*/
	arguments = _strdup(string);
	if (arguments == NULL)
		return (NULL);

	for(i = 0; arguments[i]; i++)
		if (arguments[i] == *delimiter)
			numtokens++;

	tokens = malloc(sizeof(char *) * numtokens);
	if (tokens == NULL)
		return (NULL);

	token = strtok(arguments, delimiter);
	for(i = 0; i < numtokens, token ;i++)
	{
		tokens[i] = token;
		token = strtok(NULL, delimiter);
	}

	return (tokens);

}

int cmdchk(char **line)
{
	extern char **environ;
	int i = 0 , j;
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
