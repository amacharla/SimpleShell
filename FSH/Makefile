#var
FLAGS = -Wall -Werror -Wextra -pedantic -g 

#default
all: main 

main: cp main.c
	gcc $(FLAGS) shellHeader.h memoryFunc.c stringFunc.c customFunc.c printFunc.c helperFunc.c specialFunc.c main.c
cp: cp.c
	gcc $(FLAGS) cp.c -o cp
test: test.c
	gcc -g shellHeader.h memoryFunc.c stringFunc.c customFunc.c printFunc.c helperFunc.c specialFunc.c test.c 
tr: test
	./a.out
tb: test
	gdb ./a.out
