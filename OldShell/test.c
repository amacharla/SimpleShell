//#include "shellHeader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int _alloc(char **memory, int controller)
{
	static char **memStorage;
	static int count;
	int i;

	if (memory == NULL)/*inilizie memorystorage free all memory*/
	{
		if (controller == 0)/*inilitize*/
		{
			memStorage = malloc(sizeof(char *));
			count = 0;
		}
		if (controller == -1) /*free all memory in storage*/
		{
			for (i = 0; i < count; i++)/*free storage individual pointers*/
				free(memStorage[i]);
			free(memStorage);/*free strorage itself*/
		}
		return (count);
	}

	if (controller == 1)/*add memory location*/
	{	/*make space for 1 pointer*/
		memStorage[count] = malloc(sizeof(char *));
		memStorage[count] = *memory;/*add pointer*/
		count++;/*storage count*/
	}
	else/*free given pointer and memory storage*/
	{
		//if (controller == -2)/*if given memory is a double pointer*/
		//	for (i = 0; memory[i]; i++)/*free internal pointers*/
		//		free(memory[i]);
		free(*memory);/*free pointer*/
		free(memory);
		for (i = 0; i < count && memStorage[i]; i++)/*free storage individual pointers*/
			free(memStorage[i]);
		free(*memStorage);/*free strorage itself*/
		free(memStorage);/*free strorage itself*/
	}
	return (count);/*return number of pointers in storage*/
}
int main(void)
{
	char *content = strdup("test");

	_alloc(NULL, 0);

	_alloc(&content,1);
	printf("Content: %s\n", content);

	_alloc(NULL, -1);
	printf("Content after: %s\n", content);
	free(content);
	return (0);

}
