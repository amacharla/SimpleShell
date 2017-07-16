#include "shellHeader.h"

/**
 * _alloc - remembers allocated memory so can free all if needed memory.
 * @memory: address of memory thats was malloced
 * @controller: action to take with the given memory
 * Return: number of pointers in storage
 */
int _alloc(char **memory, int controller)
{
	static char **memStorage;
	static int count;
	size_t oldsize;
	size_t newsize;
	int i;

	count = 0;
	oldsize = sizeof(char *) * count, newsize = sizeof(char *) * (count + 1);
	if (memory == NULL)/*free all memory*/
	{
		if (controller <= -2)/*acceptable controller wasnt given*/
			return (-1);

		for (i = 0; i < count; i++)/*free storage individual pointers*/
			free(memStorage[i]);
		free(memStorage);/*free strorage itself*/
		return (count);
	}

	if (memory == NULL && controller <= -2)
		return (-1);

	memStorage = malloc(sizeof(char *));
	if (controller == 1)/*add memory location*/
	{	/*make space for 1 pointer*/
		memStorage = _realloc(memStorage, oldsize, newsize);
		memStorage[count] = *memory;/*add pointer*/
		count++;/*storage count*/
	}
	else/*free given pointer and memory storage*/
	{
		if (controller == -2)/*if given memory is a double pointer*/
			for (i = 0; memory[i]; i++)/*free internal pointers*/
				free(memory[i]);
		free(memory);/*free pointer*/
		for (i = 0; i < count; i++)/*free storage individual pointers*/
			free(memStorage[i]);
		free(memStorage);/*free strorage itself*/
	}
	return (count);/*return number of pointers in storage*/
}

/**
 * _strdup - allocates and copies string
 * @str: string thats being duplicated
 * Return: duplicated string
 */
char *_strdup(char *str)
{
	char *a;
	int i, j;

	if (str == NULL)
		return (NULL);
	/* length of str */
	for (i = 0; str[i]; i++)
		;
	i++; /*include null character*/
	/*allocating memory for a*/
	a = malloc(i * sizeof(char));
	/*checks if memory is allocated and if str is null*/
	if (a == NULL)
		return (NULL);
	/*coping string*/
	for (j = 0; j < i && str[j] != '\n'; j++)
		a[j] = str[j];
	a = _realloc(a, sizeof(char), sizeof(char) * j);
	if (a == NULL)
		return (NULL);
	return (a);
}
/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: a pointer to the memory previously allocated with a call to
 * malloc: malloc(old_size)
 * @old_size: the size, in bytes, of the allocated space for ptr
 * @new_size: the new size, in bytes of the new memory block
 * Return: ptr | NULL if malloc faile or newsize is 0 or ptr null|
 * newpointer with more space
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	/*casting the void ptr to become char * so i can do pointer arithmetic*/
	char *oldptr = ptr;
	char *newptr;
	size_t i, size = old_size;

	if (old_size > new_size)
		size = new_size;

	/*dont new to reallocate space cause size is same*/
	if (new_size == size)
		return (ptr);
	/*creating new memory*/
	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		return (ptr);
	}
	/* freeing ptr*/
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	/*expanding memory*/
	if (new_size > size)
	{
		newptr = malloc(new_size);
		if (newptr == NULL)
			return (NULL);
		/*transfer old content into new*/
		for (i = 0; i < size; i++)
			newptr[i] = oldptr[i];
		free(ptr);
	}
	return (newptr);
}
