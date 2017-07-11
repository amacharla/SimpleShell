#include <stdio.h>

int main(int ac, char **av, char **env)
{
	unsigned int i = 0;

	while (env[i])
	{
		puts(env[i]);/*prints all the enviroment strings*/
		i++;
	}
	return (0);
}
