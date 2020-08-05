/************************************************************************
*file: argz.h
*purpose: declarations for argz functions, types, constants
*author: Lyubchich I. D.
*written: 25/09/2019
*last modified: 5/10/2019
*************************************************************************/
#ifndef ARGZ_H
#define ARGZ_H
#include <stdio.h>  // for printf, scanf
#include <string.h> // for strlen, strcpy, strcmp
#include <stdlib.h> // for malloc, calloc, size_t

typedef enum { OK, ERROR } error_t; // type that define did program finished successful or no
		/* function prototypes */
int word_find(char** argz, size_t* argz_len, const char* str);
error_t argz_create_sep(const char* string, int sep, char** argz, size_t* argz_len);
size_t argz_count(const char* argz, size_t arg_len);
error_t argz_add(char** argz, size_t* argz_len, const char* str);
void argz_delete(char** argz, size_t* argz_len, char* entry);
error_t argz_insert(char** argz, size_t* argz_len, char* before, const char* entry);
char* argz_next(char* argz, size_t argz_len, const char* entry);
error_t argz_replace(char** argz, size_t* argz_len, const char* str, const char* with);
void argz_print(const char* argz, size_t argz_len);
#endif /* ARGZ_H*/
