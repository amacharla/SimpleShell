#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	printf("before execve\n");
	/*runs the script ls, sends*/
	execve(argv[0], argv, NULL);
	printf("after execve\n");
	return (0);
}
