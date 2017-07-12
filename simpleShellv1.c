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
	extern char **environ;
	char *token, *buffer = NULL;
	ssize_t lineLen;
	size_t len = 0;
	int i, match, status;
	pid_t pid;

	get_command cmd[] =
	{
			{"ls", _ls},
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
	char *token = strtok(NULL, " ");/*get first option*/
	char *argv[] = {"/bin/ls", NULL, NULL, NULL, NULL};/*ls command + 4 options*/
	char *argv2[] = {"./sh", NULL};/*simple shell arguments*/
	int check, status, i, j = 1;
	pid_t pid;

	while (token)/*go through multiple options*/
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
		argv[j] = token;/*add option into argv*/
		j = (j != 5) ? j + 1 : j; /*to prevent segfault and transverse through argv to save options*/
		token = strtok(NULL, " ");/*get next option*/
	}
	pid = fork(); /*forked so parent process doesnt terminate after execve*/
	if (pid == -1)/*fork fail check*/
		return (-4);
	if (pid == 0)/*is child*/
	{
		check = execve(argv[0], argv, NULL);/* $ls -options(x4) .*/
		if (check == -1)/*execve error check*/
			return (-4);
	}
	else
	{
		wait(&status);/*wait for child to finish*/
		/** NOT FREEING BUFFER **/
		check = execve(argv2[0], argv2, NULL);/*reexecute simpleshell*/
		if (check == -1)
			return(-4);
	}
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
