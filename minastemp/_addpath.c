#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * _addpath - adds path to filname
 * @first: pointer to path
 * @second: pointer to filename
 * Return: pointer to merged string or NULL if fails
 */

char *_addpath(char *first, char *second)
{
        int i, j, k, t = 0;
        char *new;

        for (i = 0; first[i]; i++)
                ;
        for (j = 0; second[j]; j++)
                ;
        k = i + j + 2;
        new = malloc(sizeof(char) * k);
        if (!new)
                return(NULL);
        for (j = 0; j < k; j++)
        {
                if (j <= i)
                        new[j] = first[j];
                if (j = i + 1)
                        new[j] = '/';
                if (j > i + 1)
                {
                        new[j] = second[t];
                        t++;
                }
        }
        new[k] = '\0';
        return (new);
}

int _plenght(char *first, char *second)
{
	int i, j, k;

	for (i = 0; first[i]; i++)
                ;
        for (j = 0; second[j]; j++)
                ;
	k = i + j + 2;
	return (k);
}
int main(void)
{
	char *test;
	char *path;

	path = _addpath("/bin", "ls");
	//path = malloc(sizeof(char) * _plenght("/bin", "ls"));
	//strcpy(path, "/bin");
	//strcat(path, "/");
	//strcat(path, "ls");
	//test = _addpath("/bin", "ls");
	printf("%s\n", path);
	return(0);
}
