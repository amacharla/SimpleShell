#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

ssize_t _getline(char **lineptr, size_t *n);
int main(void)
{
	ssize_t linelen;
	char *buffer = NULL;
	size_t len = 0;

	linelen = _getline(&buffer, &len);
	printf("Line: %s\n Length: %jd\n", buffer, len);
	free(buffer);
	return (0);
}

ssize_t _getline(char **lineptr, size_t *n)
{
	ssize_t readcount;
	size_t bytes = 100, maxbytes = 1024;
	char *buffer;
	unsigned int i;

	if (*n > 1)
		bytes = *n;
	if (*lineptr == NULL)
		buffer = malloc(sizeof(char) * maxbytes);
	else
		buffer = *lineptr;

	do {
		readcount = read(STDIN_FILENO, buffer, bytes);
		if (readcount == -1)
			return (-1);
		for (i = 0; buffer[i]; i++)
		{
			if (buffer[i] == '\n' || buffer[i] == '\t')
				buffer[i] = '\0';
		}
		if (buffer[i] == '\0')
		{
			buffer = realloc(buffer, i);
			break;
		}
		i++;
	} while (1);

	*lineptr = buffer;
	n = &i;
	return ((ssize_t) bytes);

}

