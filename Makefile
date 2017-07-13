#var
FLAGS = -Wall -Werror -Wextra -pedantic -g

#default
all:
	gcc $(FLAGS) shell.h 0-func.c 1-func.c simpleV2.c -o hsh
