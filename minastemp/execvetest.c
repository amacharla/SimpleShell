#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	//extern char **environ;
	//char *args[] = { "/bin/ls", "-l", NULL };
	char *path = "/bin        ";
	char *command = "ls";
	char *test;

	path = strcat(path, "/");
	printf("%s\n", path);
	//execve(args[0], args, environ);
	//fprintf(stderr, "Oops!\n");
	return -1;
}
