/************************************************************************
*file: argz.c
*synopsis: The argz functions use malloc/realloc/free to allocate/grow/release argz vectors, and so any argz
* vector creating using these functions may be freed by using free; conversely, any argz
* function that may grow a string expects that string to have been allocated using malloc
* (those argz functions that only examine their arguments or modify them in place will work
* on any sort of memory). All argz functions that do memory allocation have a return type
* of error_t, and return 0 for success, and ENOMEM if an allocation error occurs.
* These functions are declared in the include file "argz.h".
*related files: none
*author: Lyubchich I. D.
*written: 25/09/2019
*last modified: 5/10/2019
************************************************************************/
#include "argz.h"

// function that finds the 1st element of 
//  the word we want to find in vector 
int word_find(char* argz, size_t argz_len, char const* entry) {
	char* tmp = argz;
	int i = 0, count, j;
	if ((!entry) || !strlen(entry))
		return -1;
	count = argz_count(argz, argz_len);
	for (j = 0; j < count; j++) {
		if (strcmp(tmp, entry) == 0)
			return i;
		i += strlen(tmp) + 1;
		tmp = argz + i;
	}
	return -1;
}
/*
The argz_create_sep function converts the null-terminated string string into an
argz vector (returned in argz and argz len) by splitting it into elements at every
occurrence of the character sep.
*/
error_t argz_create_sep(const char* string, int sep, char** argz, size_t* argz_len) {
	int i;
	if (NULL == string) return ERROR;
	*argz_len = strlen(string) + 1;
	*argz = (char*)malloc(*argz_len);
	for (i = 0; i < *argz_len - 1; i++) {
		if (sep == string[i]) (*argz)[i] = '\0'; 
		else (*argz)[i] = string[i];
	}
	(*argz)[*argz_len-1] = '\0';
	return OK;
}

//Returns the number of elements in the argz vector.
size_t argz_count(const char* argz, size_t arg_len) {
	int elem_number = 0, flag = 1; // flag is 1 when we got to '\0'
	if (NULL == argz) return 0;
	for (int i = 0; i < arg_len; i++) {
		if ('\0' == argz[i]) {
			flag = 1;
			continue;
		}
		if (1 == flag) {
			elem_number += 1;
			flag = 0;
		}
	}
	return elem_number;
}

//The argz_add function adds the string str to the end of the argz vector 
// *argz, and updates *argz and *argz_len accordingly.
error_t argz_add(char** argz, size_t* argz_len, const char* str) {
	char* temp;
	int i;
	if ((NULL  == argz)||!strlen(str)) return ERROR;
	temp = (char*)malloc(*argz_len + strlen(str) + 1);
	for (i = 0; i < *argz_len; i++)		   temp[i] = (*argz)[i];
	for (i = 0; i < strlen(str) + 1;  i++) temp[*argz_len + i] = str[i];
	*argz_len += strlen(str) + 1;
	free(*argz);
	*argz = temp;
	return OK;
}

/*If entry points to the beginning of one of the elements in the argz vector *argz,
the argz_delete function will remove this entry and reallocate *argz, modifying *argz and
*argz_len accordingly. Note that as destructive argz functions usually reallocate their
argz argument, pointers into argz vectors such as entry will then become invalid.
*/
void argz_delete(char** argz, size_t* argz_len, char* entry) {
	char* temp;
	int entry_pos, i; 
	if ((NULL  == argz) || !strlen(entry)) {
		printf("\n ---ERROR---");
		return;
	}
	entry_pos = word_find(*argz, *argz_len, entry);
	if (-1 == entry_pos) return;
	for (i = entry_pos; i < *argz_len - strlen(entry) - 1; i++)
		(*argz)[i] = (*argz)[i + strlen(entry) + 1];
	*argz_len -= strlen(entry) + 1;
	temp = (char*)malloc(*argz_len);
	for (i = 0; i < *argz_len; i++) temp[i] = (*argz)[i];
	free(*argz);
	*argz = temp;
}

/*
The argz_insert function inserts the string entry into the argz vector *argz
at a point just before the existing element pointed to by before, reallocating
*argz and updating *argz and *argz_len. If before is 0, entry is added to the end
instead (as if by argz_add). Since the first element is in fact the same as *argz,
passing in *argz as the value of before will result in entry being inserted at the beginning.
*/
error_t argz_insert(char** argz, size_t* argz_len, char* before, const char* entry) {
	if ((NULL == argz) || !strlen(entry)) return ERROR;
	if (NULL == before) {					    // if before is 0 entry added in the end of argz vector
		argz_add(argz, argz_len, entry);
		return OK;
	}
	if (!word_find(*argz, *argz_len, before)) { // the occasion when before is the first element 
		char* temp;
		int i;
		temp = (char*)malloc(*argz_len + strlen(entry) + 1);
		for (i = 0; i <= strlen(entry); i++) 
			temp[i] = entry[i];
		for (i = 0; i < *argz_len; i++) 
			temp[i + strlen(entry) + 1] = (*argz)[i];
		*argz_len += strlen(entry) + 1;
		free(*argz);
		*argz = temp;
		return OK;
	}
	int before_pos, i;
	before_pos = word_find(*argz, *argz_len, before);
	if (-1 == before_pos) return ERROR;
	char* temp = (char*)malloc(*argz_len + strlen(entry) + 1);
	for (i = 0; i < before_pos; i++)
		temp[i] = (*argz)[i];
	for (i = 0; i <= strlen(entry); i++)
		temp[before_pos + i] = entry[i];
	for (i = before_pos; i < *argz_len; i++)
		temp[i + strlen(entry) + 1] = (*argz)[i];
	*argz_len += strlen(entry) + 1;
	free(*argz);
	*argz = temp;
	return OK;
}

/*
The argz_next function provides a convenient way of iterating over the elements in the argz vector argz.
It returns a pointer to the next element in argz after the element entry, or 0 if there are no elements following entry.
If entry is 0, the first element of argz is returned.
This behavior suggests two styles of iteration:
char *entry = 0;
while ((entry = argz_next (argz, argz_len, entry)))
					action;
(the double parentheses are necessary to make some C compilers shut up about what they consider a questionable while-test) and:
char *entry;
for (entry = argz; entry; entry = argz_next (argz, argz_len, entry))
				action;
Note that the latter depends on argz having a value of 0 if it is empty (rather than a pointer to an empty block of memory);
this invariant is maintained for argz vectors created by the functions here.
*/
char* argz_next(char* argz, size_t argz_len, const char* entry) {
	char* next;
	int nextpoint;								// nextpoint equals to the index of next element in argz vector
	if (NULL == argz) return 0;
	if (NULL == entry) {						// if entry is NULL the first element is returned
		next = (char*)malloc(strlen(argz) + 1);
		strcpy_s(next, strlen(argz) + 1	, argz);
		return next;
	}								
	nextpoint = word_find(argz, argz_len, entry) + strlen(entry) + 1;
	if (nextpoint == argz_len) return 0;		// if next is the last element of argz 0 is returned
	next = (char*)malloc(strlen(argz + nextpoint) + 1);
	strcpy_s(next, strlen(argz + nextpoint) + 1, argz + nextpoint);
	return next;
}

/*
Replace the string str in argz with string with, reallocating argz as
necessary.
*/
error_t argz_replace(char** argz, size_t* argz_len, const char* str, const char* with) {
	char* temp;
	int str_pos, i;
	if (NULL  == argz) return ERROR;
	if (!strlen(str) || !strlen(with)) return ERROR;
	str_pos = word_find(*argz, *argz_len, str);
	if (-1 == str_pos) return ERROR;
	argz_delete(argz, argz_len, str);				// deleting str 
	temp = (char*)malloc(*argz_len);
	for (i = 0; i < *argz_len; i++) temp[i] = (*argz)[i];
	if (str_pos == *argz_len)						// if str_pos equals to the length of argz
		argz_add(&temp, argz_len, with);			// we just have to add it in the end of argz
	else 
		argz_insert(&temp, argz_len, *argz + str_pos, with);
	free(*argz);
	*argz = temp;
	return OK;
}

/*prints argz vector */
void argz_print(const char* argz, size_t argz_len) {
	if ((NULL == argz)||(argz_len <= 0)) { 
		printf("\n ---ERROR--- \n "); 
		return; 
	}
	for (int i = 0; i < argz_len; i++) if(argz[i] != '\0') 
		printf("%c", argz[i]); else printf("'\\0'");
}