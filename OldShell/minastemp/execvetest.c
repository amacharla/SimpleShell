#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(void)
{
	extern char **environ;
	char *args[] = { "/bin/ls", "-l", NULL };
	pid_t pid;
	int status;
	//While(1)
	//{
	printf("%s\n", args[0]);
	printf("access returned %d\n", access(args[0], F_OK));
	pid = fork();
	if (pid == -1)
		printf("error\n");
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		execve(args[0], args, environ);
		
	}
	return (0);
}
