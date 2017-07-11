/*HEADER*/
#include <stdio.h>/*printf, puts*/
#include <string.h>/*getline, strtok, strcmp*/
#include <stdlib.h>/*getline, NULL*/
#include <unistd.h>/*exec, fork, wait, stat*/
#include <sys/types.h>/*wait, stat*/
#include <sys/wait.h>/*wait*/
#include <sys/stat.h>/*stat*/

typedef struct get_command {
	char *command;
	int (*function)();
} get_command;

/*PROTOTYPE*/
int _ls(void);
int _pid(void);
int _stat(void);

/*MAIN*/
int main(void)
{
	char *token, *buffer = NULL;
	ssize_t lineLen;
	size_t len = 0;
	int i, match, status;
	pid_t pid;

	get_command cmd[] =
       	{
			{"ls\n", _ls},
		 	{"ppid\n", _pid},
			{"which", _stat},
			{NULL, NULL}
	};

while (1)
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
		if (match == 0)/*token matched command*/
		{
			pid = fork();/*create process*/
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
		free(buffer);/*malloced from getline()*/
		break;
	}
}

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

int _stat(void)
{
	char *token = strtok(NULL, " ");/*get first argument*/
	struct stat st;/*stat returns struct stat*/
	int i;

	while (token)/*go through multiple arguments*/
	{
		/*used to strip token of newline*/
		for (i = 0; token[i]; i++)
		{
 			if(token[i] == '\n')
	       		{
  				token[i] = '\0';
    				break;
  			}
		}

		if (stat(token, &st) == 0)/*if found*/
			printf("Valid path: %s\n", token);
		else
			printf("Invalid path: %s\n", token);
		token = strtok(NULL, " ");/*get next argument*/
	}
	return (0);
}
