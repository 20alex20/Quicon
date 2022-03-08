#include "all.h"
#define __FILE main_c
char* main_c = "main.c";

int main() { start_program(); object* dt = NULL, * num = NULL, * date = NULL;
    assign(dt, do_func(date_time, 0, 0));
    __(do_func(print, 1, 0, do_method(dt, now, 0, 0)));
    
    assign(num, do_method(do_func(input, 0, 0), to_int, 0, 0));
    assign(date, do_method(dt, today, 0, 0));
    while (do_method(do_method(from(date, year), less, 1, 0, create__int(FALSE, 2030)), to_bool, 0, 0)->flag) {
        __(do_func(print, 6, 1, create__string("year: ", UTF_8),  from(date, year),  create__string(",\tmonth: ", UTF_8),  from(date, month),  create__string(",\tday: ", UTF_8),  from(date, day),  named_arg(between, create__string("", UTF_8))));
        assign(date, do_method(date, addout, 1, 0, do_func(dt_delta, 2, 0,  empty_arg,  num)));
    }
	printf("\n"); system("pause"); return END;
} 
