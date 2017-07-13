#ifndef _SHELL_H_
#define _SHELL_H_

#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*STRING*/
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
int _strncmp(char *s1, char *s2, int n);
int _strlen(char *s);
char *_strdup(char *name);
/*SUPPORT*/
char *_addpath(char *first,char *second);
char **tokenize(char *string, const char *delimeter);
char *_getenv(char *name);
int cmdchk(char **line);
/*PRINT*/
int _putstring(char *str);
int _putchar(char c);

#endif
