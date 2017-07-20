
/**
 * _alloc - remembers allocated memory so can free all if needed memory.
 * @memory: address of memory thats was malloced
 * @controller: action to take with the given memory
 * Return: number of pointers in storage
 */
int _alloc(char *memory, int controller)
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
		oldsize = sizeof(char *) * count;
		newsize = sizeof(char *) * count + 1;
		memStorage = _realloc(memStorage, oldsize, newsize);
		/*memStorage[count] = malloc(sizeof(char *));*/
		memStorage[count] = memory;/*add pointer*/
		count++;/*storage count*/
	}
	else/*free given pointer and memory storage*/
	{
		//if (controller == -2)/*if given memory is a double pointer*/
		//	for (i = 0; memory[i]; i++)/*free internal pointers*/
		//		free(memory[i]);
		free(memory);/*free pointer*/
		for (i = 0; i < count && memStorage[i]; i++)/*free storage individual pointers*/
			free(memStorage[i]);
		free(memStorage);/*free strorage itself*/
	}
	return (count);/*return number of pointers in storage*/
}

