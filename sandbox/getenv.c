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
/*go through all the char pointers*/
	for(i = 0; environ[i]; i++)
	{
		printf("%s\n", environ[i]);/*check here - MINAS*/
		token = strtok(environ[i], "="); /*get first section*/
		printf("%s\n", environ[i]);/*check here - MINAS*/
		if (token == NULL)
			return (NULL);
		if (strcmp(token, name) == 0) /*match name with section*/
		{
			token = strtok(NULL, "\0");/*get rest of string*/
			return (token);
		}
	}
	return (NULL);
}
