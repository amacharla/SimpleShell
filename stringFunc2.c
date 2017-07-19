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
 * _strncpy - copies array
 * @dest: pointer array type char
 * @src: string to be copied into array
 * @n: index to start
 * Return: dest array type car
 */
char *_strncpy(char *dest, char *src, int n)
{
        int i;

        for (i = n; src[i]; i++)
                dest[i] = src[i];
        dest[i] = '\0';
        return (dest);
}
