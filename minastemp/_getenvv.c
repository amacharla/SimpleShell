#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/**
 * _getenv - returns a double dim pointer with PATH seperated
 * @varname: enviromental variable's value to return
 * Return: paths for success, NULL if failed
 */

char **_getenv(char *varname)
{
	extern char **environ;
	char **paths, *path, *temp;
	int i = 0, j = 0, size = 20;

	paths = malloc(sizeof(char *) * size + 1);
	if (!paths)
		return (NULL);
	while(environ[i])
	{
		temp = environ[i];
		path = strtok(temp, "=");
		printf("%s here testing\n", environ[i]);
		if (!_strcmp(path, varname))
		{
			while(path)
			{
				path = strtok(NULL, ":");
				paths[j] = path;
				j++;
				if (j >= size)
				{
					size += 10;
					paths = realloc(paths, size * sizeof(char *) + 1);
				        if (!paths)
						return (NULL);
				}
			}
			paths[i] = NULL;
			return (paths);
		}
		i++;
	}
	return (NULL);
}
/**
 * _strcmp - compares two strings
 * @s1: pointer string type char
 * @s2: pointer string type char
 * Return: 15 if s1 > s2, -15 vice versa, 0 if same
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int diff = 0;

	while ((s1[i] == s2[i]) && (s1[i] != '\0' && s2[i] != '\0'))
		i++; /* so it doesnt increment after null character */
	diff = s1[i] - s2[i];

	return (diff);
}
int main(void)
{
	char **paths;
	int i = 0;

	paths = _getenv("PATH");
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
}
