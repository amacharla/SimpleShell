#include "shellHeader.h"

int main(int ac, char **av, char **env)
{
	(void)(ac);
	(void)(av);
	int result;
	char *token = "a";
	char *tokens[1];

	tokens[0] = token;

	result = cmdchk(tokens, env);
	_printf("ls: %d\n", result);

	return (0);

}
int _printf_main(void)
{
	_printf("This is test1\n%s\n%d\n", "This is test2", 3);
	return (0);
}
int _alloc_main(void)
{
	char *testmem;
	int count = 0;

	testmem = malloc(sizeof(char*));
	count = _alloc(&testmem, 1);
	printf("alloc count: %d\n", count);

	printf("old size: %d\n", (unsigned int) sizeof(testmem));

	testmem = _realloc(testmem, (unsigned int) sizeof(char *), (unsigned int) sizeof(char *) * 2);

	printf("Realloc size: %d\n", (unsigned int) sizeof(testmem));

	count = _alloc(NULL,-1);
	printf("free alloc count: %i\n", count);

	return (0);

}
