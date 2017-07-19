#var
FLAGS = -Wall -Werror -Wextra -pedantic -g 

#default
all: tr 

main:
	gcc $(FLAGS) shellHeader.h memoryFunc.c stringFunc.c stringFunc2.c customFunc.c printFunc.c helperFunc.c specialFunc.c history.c main.c
cp:
	gcc $(FLAGS) cp.c -o cp
test: 
	gcc -g shellHeader.h memoryFunc.c stringFunc.c stringFunc2.c customFunc.c printFunc.c helperFunc.c specialFunc.c history.c main.c
tr: main
	./a.out
tb: test
	gdb ./a.out
