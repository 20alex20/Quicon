#include "all.h"
#define __FILE main_c
char* main_c = "main.c";

int main() { start_program(); object* print2 = NULL, * __iter = NULL, * i = NULL;
    assign(print2, do_func(copy, 1, 0, do_func(print, 0, 0)));
    __(do_method(print2, change, 2, 2,  empty_arg,  create__array(0, NULL),  named_arg(start, create__string("{", UTF_8)),  named_arg(end, create__string("}\n", UTF_8))));
    assign(__iter, do_func(range, 0, 0)); while (assign(i, do_method(__iter, next, 0, 0))) {
        __(do_func(print2, 1, 0, i));
    }; i = create__noth;
	printf("\n"); system("pause"); return END;
} 
