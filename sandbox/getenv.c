#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_getenv(char *);

int main(void)
{
	char *result = "NONE FOUND";

/** CAN NOT RUN BOTH getenv() = cause segfault **/
	result = _getenv("USER");
	//result = getenv("user");

	printf("%s\n", result);
	return (0);
}

char *_getenv(char *name)
{
	extern char **environ;
	char *token;
	unsigned int i;

	for(i = 0; environ[i]; i++)
	{
		token = strtok(environ[i], "=");
		if (token == NULL)
			return (NULL);
		if (strcmp(token, name) == 0)
		{
			token = strtok(NULL, "\0");
			return (token);
		}
	}
	return (NULL);
}
