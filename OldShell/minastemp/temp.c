#include "shell.h"
#include <stdio.h>
int _argcount(char *s);
char **tokenize(char *s)
{
	int i = _argcount(s);
	char **tokens, *token;

	tokens = malloc(i * sizeof(char *) + 1);
	token = strtok(s, " ");
	while (token)
	{
		tokens[i] = token;
		token = strtok(NULL, " ");
		printf("%s\n", tokens[i]);
		i++;
	}
}

int _argcount(char *s)
{
	int i = 0, j = 0;

	while (s[i])
	{
		if (s[i] == ' ')
			j++;
		i++;
	}
	return (j + 1);
}

/**
 * main - shell
 * Return: 0
 */

int main(void)
{
	extern char **environ;
	char *line, **linet, *argg, *linecp;
	size_t linesize = 64;
	int argc, i = 0;
	while(1)
	{
		write(STDOUT_FILENO, "$>", 2);
		getline(&line, &linesize, stdin);
		argc = _argcount(line);
		linet = tokenize(line);
		while (linet[i])
		{
			printf("%s\n", linet[i]);
			i++;
		}
		//_checkline(line);
		free(linet);
	}
	return (0);
}
