#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	char *token;
	int j;

	if (ac != 2)
		return (-1);

	/*take first argument and , as delimiter*/	
	token = strtok(av[1], ",");

	while(token) /*returns NULL if no tokens left*/
	{
		printf(" %s\n", token);
		token = strtok(NULL, ",");/*global pointer points next token*/
	}
	return (0);
}
