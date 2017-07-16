#include "shellHeader.h"

/**
 * _putstring - prints a string
 * @str: string to print
 * Return: number of chars printed
 */
int _putstring(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (write(STDOUT_FILENO, str, i));
}

/**
 * _strtok - splits string based of delimiter
 * Uses Static var to remember string.
 * @str: input string thats duplicated and modified
 * @delim: delimiter used to break the duplicated string
 * Return: individual tokens or NULL if fails
 */
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
		token = _strdup(str);/*duplicate string*/

		for(i = 0; token[i]; i++)/*loop through token*/
		{
			for (j = 0; delim[j]; j++)/*loop through delim*/
			{
				if (token[i] == delim[j])/*if match*/
				{
					i++;/*duplicate remainder of token for latter access*/
					statictok = _strdup(&token[i]);
					if (statictok == NULL)
						return (NULL);
					i--;/*replace delim with null*/
					token[i] = '\0';
					/*realloc to required amount*/
					token = _realloc(token, i);
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
