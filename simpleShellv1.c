/*HEADER*/
#include <stdio.h>/*printf, puts*/
#include <string.h>/*getline, strtok, strcmp*/
#include <stdlib.h>/*getline, NULL*/
#include <unistd.h>/*exec, fork, wait*/
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

	get_command cmd[] =
       	{
			{"ls\n", _ls},
		 	{"ppid\n", _pid},
			{NULL, NULL}	
	};

while (trigger) 
{ /*Loop so it can process multiple commands*/
	printf("--> ");
	lineLen = getline(&buffer, &len, stdin);
	if (lineLen == -1)/*getline error check*/
		return (-2);
	
	token = strtok(buffer, " "); /*get first argument*/
	if (token == NULL) /*strtok error check*/
	{
		free(buffer);
	       	return (-3);
	}
	/*loop to find match with avaliable commands and token*/
	for (i = 0; cmd[i].command != NULL; i++)
	{
		match = strcmp(cmd[i].command, token);
		if (match == 0)
		{	pid = fork();/*create process*/
			if (pid == -1)/*fork error check*/
				return (-5);
			if (pid == 0)/*if child process*/
				cmd[i].function();
			else/*if parent process*/
				wait(&status);
			break;
		}
	}

	if (cmd[i].command == NULL) /*no match was found*/
	{
		puts("command not found");
		trigger = 0;
	}
}
	free(buffer);/*malloced from getline()*/
	
	return (0);
}

/*FUNCTIONS*/
int _ls(void)
{
	int check;
	char *argv[] = {"/bin/ls", "-l", ".", NULL};
	
	check = execve(argv[0], argv, NULL);/* $ls -l .*/
	if (check == -1)/*execve error check*/
		return (-4);
	return (0);
}

int _pid(void)
{
	pid_t pid = getpid();
	printf("%u\n", pid);
	return (0);
}
