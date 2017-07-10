#include <stdio.h>
#include <stdlib.h>
/* Prints all the arguments*/
/*used to test EXECVE function*/
int main(int argc, char **argv)
{
	int j;

	for (j = 0; j < argc; j++)
		printf("argv[%d]: %s\n", j, argv[j]);
	return (0);
}
