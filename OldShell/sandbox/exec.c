#include <stdio.h>
#include <unistd.h>
/**
 * Testing execve
 * used with myecho.c
 */
int main(int argc, char **argv)
{	/* argument array MUST end with NULL*/
	char *newargv[] = {NULL, "hello", "world", NULL};
	
	if (argc != 2)
		return (-1);
	/* sends executalbe (a.out) into 0 index*/
	newargv[0] = argv[1];
	/*calls executable, sends char *array, NULL envp[]*/
	execve(argv[1], newargv, NULL);
	
	/*never runs*/
	puts("After execve");
}
