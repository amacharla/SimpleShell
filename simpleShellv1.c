/*HEADER*/
#include <stdio.h>/*printf,puts*/
#include <string.h>/*getline, strtok*/
#include <stdlib.h>/*getline*/
#include <unistd.h>/*exec,fork,wait*/
#include <sys/types.h>/*wait*/
#include <sys/wait.h>/*wait*/

typedef struct get_command {
	char *command;
	int (*function)();
} get_command;

/*PROTOTYPE*/
int _ls(void);
int _pid(void);

/*MAIN*/
int main(void)
{
	char *token, *buffer = NULL;
	ssize_t lineLen;
	size_t len = 0;
	int i, match, status, trigger = 1;
	pid_t pid;

	get_command cmd[] = {
			{"ls\n", _ls},
		 	{"ppid\n", _pid},
			{NULL, NULL}	
	};
while (trigger) {
	printf("--> ");
	lineLen = getline(&buffer, &len, stdin);
	if (lineLen == -1)
		return (-2);
	
	token = strtok(buffer, " ");
	if (token == NULL)
	{
		free(buffer);
	       	return (-3);
	}
	
	for (i = 0; cmd[i].command != NULL; i++)
	{
		match = strcmp(cmd[i].command, token);
		if (match == 0)
		{	pid = fork();
			if (pid == -1)
				return (-5);
			if (pid == 0)
				cmd[i].function();
			else
				wait(&status);
			break;
		}
	}

	if (cmd[i].command == NULL)
	{
		puts("command not found");
		trigger = 0;
	}
}
	free(buffer);
	
	return (0);
}

/*FUNCTIONS*/
int _ls(void)
{
	int check;
	char *argv[] = {"/bin/ls", "-l", ".", NULL};
	
	check = execve(argv[0], argv, NULL);
	if (check == -1)
		return (-4);
	return (0);
}

int _pid(void)
{
	pid_t pid = getpid();
	printf("%u\n", pid);
	return (0);
}
