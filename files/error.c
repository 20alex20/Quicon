#include "all.h"
#define __FILE error_c
char* error_c = "error.c";


void __error(char* name, uint line, errors nomer, intptr_t sth, ...) {
	system("color 4");
	printf("\nError in file %s in line %d:\n", name, line);
	switch (nomer) {
	case __TYPE_METHOD_ERROR:
		printf("This method is not defined for %s", __classes[sth]->len);
		break;
	case __TYPE_ARG_ERROR:
		printf("The argument passed must not be of %s", __classes[sth]->len);
		break;
	case __NAME_ARG_ERROR:
		printf("No named variable numbered %u", sth);
		break;
	case __NAME_ARG_ERROR_2:
		printf("This name is not implemented ", __classes[sth]->len);
		break;
	case __INDEX_ERROR:
		printf("Index %d of variable of length %u out of the range", sth, *(&sth + 1));
		break;
	case __NO_ARG_ERROR:
		printf("Argument numbered %u was not passed to this function/method", sth + 1);
		break;
	case __MANY_VALUES_ARG_ERROR:
		printf("Many values were passed to one argument numbered %u", sth + 1);
		break;
	case __NO_ELEMENT_ARRAY_ERROR:
		printf("Element of array at number %u was skipped", sth);
		break;
	case __TOO_MANY_ARGS_ERROR:
		printf("%u positional arguments were passed to the function with %u arguments", sth, *(&sth + 1));
		break;
	case __TOO_MANY_NAMED_ARGS_ERROR:
		printf("%u named arguments were passed to the function with %u arguments", sth, *(&sth + 1));
		break;
	case __LONG_INT_ERROR:
		printf("Numeric variable %u bytes long takes up more memory than this C-type can fit", sth);
		break;
	case __W1251_ERROR:
		system("chcp 65001");
		printf("Unable to use Windows 1251 encoding due to the presence of utf-8 characters in the string: %s", (char*)sth);
		break;
	case __ANOTHER_ERROR:
		printf(sth);
		break;
	default:
		printf("Unrecognized error");
		break;
	}
	printf("\n");
	system("pause");
	exit(EXIT_FAILURE);
}