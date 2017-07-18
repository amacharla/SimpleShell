#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * tested getline and strtok
 */

char *_strtok(char *str, const char *delim);

int main(void)
{
	char *token, *buffer;

	/*stores stream in buffer, and its length*/
	buffer = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games";

	/*take first argument and space as delimiter*/
	token = _strtok(buffer, "=");

	while(token != NULL) /*strtok returns NULL if no tokens left*/
	{
		printf(" %s\n", token);
		token = _strtok(NULL, ":");/*global pointer points to next word address*/
	}
	free(token);
	return (0);
}

char *_strtok(char *str, const char *delim)
{
	static char *statictok;
	static size_t i;
	char *token;
	size_t j;

	/*if str is null and never been run before*/
	if (str == NULL && i == 0)
		return (NULL);

	/*during the first run*/
	if (str != NULL)
	{
		token = strdup(str);/*duplicate string*/

		for(i = 0; token[i]; i++)/*loop through token*/
		{
			for (j = 0; delim[j]; j++)/*loop through delim*/
			{
				if (token[i] == delim[j])/*if match*/
				{
					i++;/*duplicate remainder of token for latter access*/
					statictok = strdup(&token[i]);
					if (statictok == NULL)
						return (NULL);
					i--;/*replace delim with null*/
					token[i] = '\0';
					/*realloc to required amount*/
					token = realloc(token, i);
					if (token == NULL)
						return (NULL);

					return (token);
				}
				if (token[i] == '\n')/*no match but when string ends in \n*/
				{
					free(statictok);/*free static token1 used to save remainder*/
					return (token);
				}
			}
		}
		if (token == NULL)/*no match return duplicate copy*/
		{
			free(statictok);
			return (token);
		}
	}
	if (str == NULL)/*strtok(NULL,delim); access rest of tokens*/
		return (_strtok(statictok, delim));/*use previously saved remainder*/

	return (NULL);
}
