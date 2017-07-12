#ifndef _SHELL_H_
#define _SHELL_H_

#include<stdlib.h>
#include<unistd.h>
#include<string.h>

/*STRING*/
char *_strcat(char *dest, char *src);
int _plenght(char *first, char *second);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
int _strncmp(char *s1, char *s2, int n);
int _strlen(char *s);
/*PRINT*/
int _putstring(char *str);
int _putchar(char c);

#endif
