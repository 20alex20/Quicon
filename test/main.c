#include "all.h"
#define __FILE main_c
char* main_c = "main.c";

int main() { start_program(); object* __iter = NULL, * i = NULL;
    assign(__iter, do_func(range, 0, 3, named_arg(start, create__int(FALSE, 3)),  named_arg(stop, create__int(FALSE, 1000)),  named_arg(step, create__int(FALSE, 2)))); while (assign(i, do_method(__iter, next, 0, 0))) {
        if_bool (do_func(is_sample, 1, 0, i)) {
            __(do_func(print, 2, 0, i,  create__string(" - простое число", WINDOWS_1251)));
        }
    }; i = create__noth;
	printf("\n"); system("pause"); return END;
} 
