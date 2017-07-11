#include <stdio.h>

extern char **environ;

int main(int ac, char **av)
{
	char *result;

	if (ac != 2)
		return (-1);

	result = _getenv(av[1]);
	printf("%s\n", result);
}

char *_getenv(const char *name)
{

}
