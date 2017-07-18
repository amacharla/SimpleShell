#include <stdio.h>/*printf,puts*/
#include <unistd.h>/*exec,fork,wait*/
#include <sys/types.h>/*wait*/
#include <sys/wait.h>/*wait*/
/**
 * Program that executes the command ls -l /usr/ 5 times.
 * practice using: getpid, fork, wait, execve
 */
int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};
	pid_t pid, cpid;
	int i, status;

	pid = getpid();
	printf("---Parent PID: %u---\n", pid);
	
	for(i = 1; i <= 5; i++)/*executes 5 times*/
	{
		pid = fork();/*returns 0 if child*/
		if (pid == -1)/*if fork fails*/
			return (-1);
		if (pid == 0)/*if child*/
		{
			cpid = getpid();/*gets current pid*/
			printf("---Child Process: %d | PID: %u---\n", i, cpid);
			execve(argv[0], argv, NULL);/*executes ls -l /tmp*/
		}
		else/*if parent*/
		{
			wait(&status);/*waits for child to finish*/ 
			puts("---Back to PARENT---");
		}
	}

}
