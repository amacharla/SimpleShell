#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	size_t bytes = 3;
	ssize_t readcount;
	char *buffer;

	buffer = malloc(sizeof(char) * bytes);

	readcount = read(STDIN_FILENO, buffer, bytes);
	printf("%s | %jd;", buffer, readcount);

	readcount = read(STDIN_FILENO, buffer, bytes);
	printf("%s", buffer);
	putchar(10);
	return (0);
}
