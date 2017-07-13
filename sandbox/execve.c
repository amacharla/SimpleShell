#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *argv[] = {"st", NULL};

	printf("before execve\n");
	/*runs the script ls, sends*/
	execve(argv[0], argv, NULL);
	printf("after execve\n");
	return (0);
}
