#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *argv[] = {"cp", "test.c", "test1.c", NULL};

	printf("before execve\n");
	/*runs the script ls, sends*/
	execve(argv[0], argv, NULL);
	printf("after execve\n");
	return (0);
}
