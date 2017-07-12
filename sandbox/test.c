#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
	char *result;
	int i;
	const char *search = "USER";

	result = getenv(search);

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);

	return (0);
}
