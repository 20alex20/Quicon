#include "all.h"
#define __FILE dt_delta_c
char* dt_delta_c = "dt_delta.c";


object* __create__dt_delta(object* __func) {
    start_func_0();
    return __create_class(Dt_delta);
}


#define __class DT_DELTA
#define __class_name Dt_delta
#define clear (0)
object* __dt_delta (object* __func, object* self, object* days, object* hours, object* minutes, object* seconds, ...) { start_func(NULL, arg(days), 2, arg(hours), 3, arg(minutes), 4, arg(seconds), 5, arg(self), 1); 
    assign(hours, do_method(do_method(days, multiply, 1, 0, create__int(FALSE, 24)), addout, 1, 0, hours));
    assign(minutes, do_method(do_method(hours, multiply, 1, 0, create__int(FALSE, 60)), addout, 1, 0, minutes));
    assign(from_self(seconds), do_method(do_method(minutes, multiply, 1, 0, create__int(FALSE, 60)), addout, 1, 0, seconds));
    returnf(self);
}





#define __class DT_DELTA
#define __class_name Dt_delta
#define __class_2 DT_DELTA
#define __class_name_2 Dt_delta
#define clear (0)
object* __addout_dt_delta__dt_delta (object* self, object* self2, ...) {start_method2(); 
    returnf2(do_func(dt_delta, 1, 0, do_method(from_self(seconds), addout, 1, 0, from_self_2(seconds))));
}

#define __class DT_DELTA
#define __class_name Dt_delta
#define __class_2 DATE_TIME
#define __class_name_2 Date_time
#define clear (0)
object* __addout_date_time__dt_delta (object* self, object* self2, ...) {start_method2(); 
    returnf2(do_func(date_time, 0, 6, named_arg(year, from_self_2(year)),  named_arg(month, from_self_2(month)),  named_arg(day, from_self_2(day)),  named_arg(hour, from_self_2(hour)),  named_arg(minute, from_self_2(minute)),  named_arg(second, do_method(from_self_2(second), addout, 1, 0, from_self(seconds)))));
}

object* __addout__dt_delta (object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { DT_DELTA, DATE_TIME };
	static object* (*functions[]) (object * self, object * self2) = { __addout_dt_delta__dt_delta, __addout_date_time__dt_delta };
	return __create_distribution(self, self2, class_names, functions, __addout_dt_delta__dt_delta);
}
