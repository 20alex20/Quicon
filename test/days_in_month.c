#include "all.h"
#define __FILE days_in_month_c
char* days_in_month_c = "days_in_month.c";


object* __create__days_in_month(object* __func) {
    start_func_0();
    return __create_class(Days_in_month);
}


#define __class DAYS_IN_MONTH
#define __class_name Days_in_month
#define clear (0)
object* __days_in_month (object* __func, object* self, object* year, ...) { start_func(NULL, arg(self), 1, arg(year), 2); 
    assign(from_self(cur_year), year);
    assign(from_self(iterator), create__type_iterator(from_self_class(arr_days)));
}

#define __class DAYS_IN_MONTH
#define __class_name Days_in_month
#define clear (2, ans, year)
object* __next__days_in_month (object* __func, object* self, ...) { start_func(NULL, arg(self), 1); start_method(); object* ans = NULL, * year = NULL;
    assign(ans, do_method(from_self(iterator), next, 0, 0));
    if_bool (is(ans, StopIteration)) {
        assign(year, do_method(year, addout, 1, 0, create__int(FALSE, 1)));
        assign(from_self(iterator), create__type_iterator(from_self_class(arr_days)));
        returnf(do_method(from_self(iterator), next, 0, 0));
    }
    if_bool (do_method(ans, equal, 1, 0, create__int(FALSE, 28))) {
        assign(ans, do_method(ans, addout, 1, 0, do_func(is_leap, 1, 0, from_self(year))));
    }
    returnf(ans);
}




