#ifndef _SHELLHEADER_H
#define _SHELLHEADER_H

/*lIBRARY*/
#include <stdio.h>/*getline,perror*/
#include <string.h>/*strtok*/
#include <stdlib.h>/*malloc,exit,getline*/
#include <sys/types.h>/*wait,closedir,opendir,stat*/
#include <sys/wait.h>/*wait*/
#include <sys/stat.h>/*stat*/
#include <dirent.h>/*closedir,opendir,readdir*/
#include <unistd.h>/*execve,fork,wait,close,access
,getcwd,chdir,read,write,exit,stat*/

/*STRINGFUNC*/
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);

/*HELPERFUNC*/
char **tokenize(char *string, const char *delimiter);
char *_addpath(char *first,char *second);
char *_getenv(char *name);
int cmdchk(char **line);

/*MEMORYFUNC*/
int _alloc(char **memory, int controller);
char *_strdup(char *str);
void *_realloc(void *ptr, size_t old_size, size_t new_size);

#endif /*_SHELLHEADER_H*/
