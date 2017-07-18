#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int ac, char**av)
{
	unsigned int i = 1;
	struct stat st; /* stat returns address of struct stat that contains info of the file*/

	while (av[i])
	{
		printf("%s: ", av[i]);
		if (stat(av[i], &st) == 0)/* returns  0 if found else -1*/
		{
			puts(" FOUND");
			printf("%jd\n", st.st_size);/*prints the size of the file in bites*/
		}
		else
			puts(" NOT FOUND");
		i++;
	}
}
