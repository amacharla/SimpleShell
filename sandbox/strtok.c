#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * tested getline and strtok
 */
int main(void) 
{
	char *token, *buffer = NULL;
	ssize_t j;
	size_t len = 0;

	/*stores stream in buffer, and its length*/
	j = getline(&buffer, &len, stdin);

	/*take first argument and space as delimiter*/	
	token = strtok(buffer, " ");

	while(token != NULL) /*strtok returns NULL if no tokens left*/
	{
		printf(" %s\n", token);
		token = strtok(NULL, " ");/*global pointer points to next word address*/
	}
	return (0);
}
