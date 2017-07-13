#include "shell.h"

/**
 * _strcat - appends a string to another
 * @dest: string to append to
 * @src: string to be appended
 * Return: merged string
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i]; i++)
		;
	for (j = 0; src[j]; j++, i++)
		dest[i] = src[j];
	dest[i] = '\0';

	return (dest);
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
		i++;
	diff = s1[i] - s2[i];

	return (diff);
}

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
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: number of chars printed
 */
int _putchar(char c)
{
	return(write(STDOUT_FILENO, &c, 1));
}

/**
 * *_strcpy - copies array
 * @dest: pointer array type char
 * @src: string to be copied into array
 * Return: dest array type car
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}


int _strlen(char *s)
{
        int i = 0;

	if(!s)
		return (-1);
	while(s[i])
                i++;
	return (i);
}

int _strncmp(char *s1, char *s2, int n)
{
	int i;

	if (!((s1 || s2) || n))
		return (-1);
	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (0);
	}
        return (1);
}
