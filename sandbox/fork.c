#include <stdio.h>
#include <unistd.h>

int main(void)
{
	/**PARENT STARTS HERE**/
	pid_t my_pid;
	pid_t pid;
	
	puts("Before FORK");
	
	/**DEVATION INSTANCE STARTS HERE**/
	/* PARENTs INSTANCE: fork returns childs pid
	 * CHILDs INSTANCE: fork returns 0 */
	pid = fork();
	if (pid == -1)
		return (-1);

	puts("After FORK");
	
	my_pid = getpid();/*current pid*/
	if (pid == 0)/*child indicator because fork returns 0 to child*/
	{
		puts("THIS IS CHILD");
		printf("Child PID: %u\n", my_pid);
		printf("forks returned PID: %u\n", pid);
	}
	else
	{
		puts("THIS IS PARENT");	
		printf("Parent PID: %u\n", my_pid);
		printf("forks returned  PID: %u\n", pid);
	}
	return (0);
}
