#include "shell.h"
#include <stdio.h>
/*compile with - gcc _getenv.c shell.h functions.c*/

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
			printf("%s\n", environ[i]); /*check here*/
			return (token);
                }
        }
        return (NULL);
}

int main(void)
{
	char *path;

	path = _getenv("PATH");
	printf("%s\n", path);/*check here*/
	return (0);
}
