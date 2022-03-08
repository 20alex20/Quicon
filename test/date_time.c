#include "all.h"
#define __FILE date_time_c
char* date_time_c = "date_time.c";


object* __create__date_time(object* __func) {
    start_func_0();
    return __create_class(Date_time);
}


#define __class DATE_TIME
#define __class_name Date_time
#define clear (1, cur_days)
object* __date_time (object* __func, object* self, object* year, object* month, object* day, object* hour, object* minute, object* second, ...) { start_func(NULL, arg(day), 4, arg(hour), 5, arg(minute), 6, arg(month), 3, arg(second), 7, arg(self), 1, arg(year), 2); object* cur_days = NULL;
    assign(minute, do_method(minute, addout, 1, 0, do_method(second, divide, 1, 0, create__int(FALSE, 60))));
    assign(from_self(second), do_method(second, rod, 1, 0, create__int(FALSE, 60)));
    assign(hour, do_method(hour, addout, 1, 0, do_method(minute, divide, 1, 0, create__int(FALSE, 60))));
    assign(from_self(minute), do_method(minute, rod, 1, 0, create__int(FALSE, 60)));
    assign(day, do_method(day, addout, 1, 0, do_method(hour, divide, 1, 0, create__int(FALSE, 24))));
    assign(from_self(hour), do_method(day, rod, 1, 0, create__int(FALSE, 24)));
    assign(year, do_method(year, addout, 1, 0, do_method(do_method(month, subtractout, 1, 0, create__int(FALSE, 1)), divide, 1, 0, create__int(FALSE, 12))));
    assign(month, do_method(do_method(do_method(month, subtractout, 1, 0, create__int(FALSE, 1)), rod, 1, 0, create__int(FALSE, 12)), addout, 1, 0, create__int(FALSE, 1)));

    assign(cur_days, do_method(do_method(from_self_class(arr_days), tabi, 1, 0, do_method(month, subtractout, 1, 0, create__int(FALSE, 1))), addout, 1, 0, do_func(is_leap, 2, 0, year,  month)));
    while (do_method(do_method(day, more, 1, 0, cur_days), to_bool, 0, 0)->flag) {
        assign(day, do_method(day, subtractout, 1, 0, cur_days));
        assign(month, do_method(month, addout, 1, 0, create__int(FALSE, 1)));
        if_bool (do_method(month, equal, 1, 0, create__int(FALSE, 13))) {
            assign(year, do_method(year, addout, 1, 0, create__int(FALSE, 1)));
            assign(month, create__int(FALSE, 1));
        }
        assign(cur_days, do_method(do_method(from_self_class(arr_days), tabi, 1, 0, do_method(month, subtractout, 1, 0, create__int(FALSE, 1))), addout, 1, 0, do_func(is_leap, 2, 0, year,  month)));
    }
    assign(from_self(day), day);
    assign(from_self(month), month);
    assign(from_self(year), year);
    returnf(self);
}


#define __class DATE_TIME
#define __class_name Date_time
#define clear (0)
object* __today__date_time (object* __func, object* self) { start_func(NULL, arg(self), 1); start_method(); 
    returnf(do_func(date_time, 0, 3, named_arg(year, create__int(FALSE, 1970)),  named_arg(month, create__int(FALSE, 1)),  named_arg(day, create__int(FALSE, 1))));
}

#define __class DATE_TIME
#define __class_name Date_time
#define clear (0)
object* __now__date_time (object* __func, object* self) { start_func(NULL, arg(self), 1); start_method(); 
    returnf(do_func(date_time, 0, 6, named_arg(year, create__int(FALSE, 1970)),  named_arg(month, create__int(FALSE, 1)),  named_arg(day, create__int(FALSE, 1)),  named_arg(hour, create__int(FALSE, 0)),  named_arg(minute, create__int(FALSE, 0)),  named_arg(second, create__int(FALSE, 0))));
}

#define __class DATE_TIME
#define __class_name Date_time
#define clear (0)
object* __to_string__date_time (object* __func, object* self) { start_func(NULL, arg(self), 1); start_method(); 
    returnf(do_method(do_method(do_method(do_method(do_method(do_method(do_method(do_method(do_method(do_method(do_func(add_0, 1, 0, from_self(day)), addout, 1, 0, create__string(".", UTF_8)), addout, 1, 0, do_func(add_0, 1, 0, from_self(month))), addout, 1, 0, create__string(".", UTF_8)), addout, 1, 0, do_method(from_self(year), to_string, 0, 0)), addout, 1, 0, create__string(" ", UTF_8)), addout, 1, 0, do_func(add_0, 1, 0, from_self(hour))), addout, 1, 0, create__string(":", UTF_8)), addout, 1, 0, do_func(add_0, 1, 0, from_self(minute))), addout, 1, 0, create__string(":", UTF_8)), addout, 1, 0, do_func(add_0, 1, 0, from_self(second))));
}


#define __class DATE_TIME
#define __class_name Date_time
#define __class_2 DT_DELTA
#define __class_name_2 Dt_delta
#define clear (0)
object* __addout_dt_delta__date_time (object* self, object* self2, ...) {start_method2(); 
    returnf2(do_func(date_time, 0, 6, named_arg(year, from_self(year)),  named_arg(month, from_self(month)),  named_arg(day, from_self(day)),  named_arg(hour, from_self(hour)),  named_arg(minute, from_self(minute)),  named_arg(second, do_method(from_self(second), addout, 1, 0, from_self_2(seconds)))));
}

object* __addout__date_time (object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { DT_DELTA };
	static object* (*functions[]) (object * self, object * self2) = { __addout_dt_delta__date_time };
	return __create_distribution(self, self2, class_names, functions, NULL);
}
