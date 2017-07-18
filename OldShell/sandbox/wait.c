#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t child_pid;
	int status;
	
	puts("I am PARENT PROCESS");

	/** DEVIATION STARTS**/
	child_pid = fork();
	if (child_pid == -1)
		return (-1);

	if (child_pid == 0)/*only true in Child instance*/
		puts("I am the CHILD PROCESS"), sleep(3);
	else /*Its a parent process*/
	{
		wait(&status);/*toggle this to see its function and compare outputs*/
		puts("I am the PARENT PROCESS again.");
		printf("Wait Status: %d\n", status);
	}
	return (0);
}
