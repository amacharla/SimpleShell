#var
#FLAGS = -Wall -Werror -Wextra -pedantic -g 

#default
all: r 

main:
	gcc $(FLAGS) shellHeader.h memoryFunc.c stringFunc.c customFunc.c printFunc.c helperFunc.c main.c
test:
	gcc -g shellHeader.h memoryFunc.c stringFunc.c customFunc.c printFunc.c helperFunc.c test.c
r: main
	./a.out
db: test
	gdb ./a.out
