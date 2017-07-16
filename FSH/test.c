#include "shellHeader.h"

int main(void)
{
	char *testmem;
	int count = 0;

	testmem = malloc(sizeof(char*));
	count = _alloc(&testmem, 1);
	printf("alloc count: %d\n", count);

	printf("old size: %d", (unsigned int) sizeof(testmem));

	testmem = _realloc(testmem, (unsigned int) sizeof(char *), (unsigned int) sizeof(char *) * 2);

	printf("Realloc size: %d\n", (unsigned int) sizeof(testmem));

	count = _alloc(NULL,-1);
	printf("free alloc count: %i\n", count);

	return (0);

}
