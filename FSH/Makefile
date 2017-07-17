#var
#FLAGS = -Wall -Werror -Wextra -pedantic -g 

#default
all: test

main:
	gcc $(FLAGS) shellHeader.h memoryFunc.c stringFunc.c customFunc.c main.c
alloc:
	gcc -g shellHeader.h memoryFunc.c stringFunc.c customFunc.c test.c
test:
	gcc -g shellHeader.h memoryFunc.c stringFunc.c customFunc.c printFunc.c helperFunc.c test.c
