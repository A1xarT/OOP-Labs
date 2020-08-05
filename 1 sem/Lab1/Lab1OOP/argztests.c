/************************************************************************
*file: argztests.c
*purpose: this file is created to ensure that functions work correctly
*related files: none
*author: Lyubchich I. D.
*written: 25/09/2019
*last modified: 5/10/2019
************************************************************************/
#include "argz.h"

int main() {
	char const *str, *with, *string;
	char *A, *entry, *before;
	size_t length;
	int number;
	// argz_create_sep test
	printf("\n argz_create_sep test \n\n ");
	string = "SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";
	length = strlen(string);
	A = NULL;
	argz_print(string, strlen(string));
	printf("\n Old length: %d", strlen(string));
	printf("\n Result: %d", argz_create_sep(string, 58 /*ASCII code for ':' */, &A, &length));
	printf("\n New string: ");
	argz_print(A, length);							  
	printf("\n New length = %d", length);			  
		
	// argz_count test
	printf("\n\n argz_count test\n\n ");
	argz_print(A, length);
	printf("\n Number of elements: %d", argz_count(A, length));

	// argz_add test
	printf("\n\n argz_add test\n ");
	str = "month=October";
	printf("\n Old string: "); argz_print(A, length);
	printf("\n string to add: %s", str);
	printf("\n Result: %d", argz_add(&A, &length, str));
	printf("\n New string: "); argz_print(A, length);
	printf("\n Length = %d", length);

	// argz_delete test
	printf("\n\n argz_delete test\n ");
	entry = "usr=monty";
	printf("\n Old string: "); argz_print(A, length);
	printf("\n string to delete: %s", entry);
	argz_delete(&A, &length, entry);
	printf("\n New string: "); argz_print(A, length);
	printf("\n Length = %d", length);

	// argz_insert test
	printf("\n\n argz_insert test\n ");
	entry = "TIME=6AM";
	before = "PWD=/bin/monty";
	printf("\n Old string: "); argz_print(A, length);
	printf("\n string to insert: %s before: %s", entry, before);
	printf("\n Result: %d", argz_insert(&A, &length, before, entry));
	printf("\n New string: "); argz_print(A, length);
	printf("\n Length = %d", length);

	// argz_next test
	printf("\n\n argz_next test\n\n ");
	number = 1; 
	entry = 0;
	argz_print(A, length);
	while ((entry = argz_next(A, length, entry)))
		printf("\n Element #%d: %s", number++, entry);

	// argz_replace test
	printf("\n\n argz_replace test\n ");
	str = "month=October";
	with = "OS=Windows";
	printf("\n Old string: "); argz_print(A, length);
	printf("\n string to replace: %s with: %s", str, with);
	printf("\n Result: %d", argz_replace(&A, &length, str, with));
	printf("\n New string: "); argz_print(A, length);
	printf("\n Length = %d", length);

	// argz_print test
	printf("\n\n argz_print test \n\n ");
	argz_print(A, length);
	printf("\n");
	free(A); 
	return 0;
}