#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * _strdup - a function that returns a pointer to a
 *  newly allocated space in memory,
 *  which contains a copy of the string given as a
 *  parameter. We create our own buffer!
 * @str: char pointer to string litreal
 * Return: pointer to newly allocated space in memory of the duplicate string.
 */
char *_strdup(char *str)
{
	char *a;
	int i, j;

	if (str == NULL)
		return (NULL);

	/* length of str */
	for (i = 0; str[i]; i++)
		;
	i++; /*include null character*/
	/*allocating memory for a*/
	a = malloc(i * sizeof(char));

	/*checks if memory is allocated and if str is null*/
	if (a == NULL)
		return (NULL);

	/*coping string*/
	for (j = 0; j < i; j++)
		a[j] = str[j];
	return (a);
}

char **tokenize(char *string, const char *delimiter)
{
	char **tokens, *token, *arguments;
	size_t i, numtokens = 0;

	/* duplicates string so we can manipulate it*/
	arguments = _strdup(string);
	if (arguments == NULL)
		return (NULL);

	for(i = 0; arguments[i]; i++)
		if (arguments[i] == *delimiter)
			numtokens++;

	tokens = malloc(sizeof(char *) * numtokens);
	if (tokens == NULL)
		return (NULL);

	token = strtok(arguments, delimiter);
	for(i = 0; i < numtokens, token ;i++)
	{
		tokens[i] = token;
		token = strtok(NULL, delimiter);
	}

	return (tokens);

}

int main(void)
{
	int i;
	char **result;
	char *arguments = "hi,my,name is,anoop.";

	result = tokenize(arguments, ",");


	printf("arguments: %s\n", arguments);

	for (i = 0; result[i]; i++)
		printf("Results: %s\n", result[i]);

	return (0);

}
