#include "all.h"
#define __FILE range_c
char* range_c = "range.c";



object* __create__range(object* __func) {
	start_func_0();
	return __create_class(Range);
}


#define __class RANGE
#define __class_name Range
#define clear (0)
object* __range(object* __func, object* self, object* start, object* stop, object* step, ...) {
	start_func(NULL, arg(self), 1, arg(start), 2, arg(step), 4, arg(stop), 3);
	start_method();
	assign(from_self(current), start);
	assign(from_self(stop), stop);
	assign(from_self(step), step);
	assign(from_self(numsign), do_method(step, numsign, 0, 0));
	returnf(self);
}



#define __class RANGE
#define __class_name Range
#define clear (1, num)
object* __next__range(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	start_method();
	object* num = NULL;
	assign(num, from_self(current));
	if (from_self(numsign)->flag) {
		if (not(do_method(num, more, 1, 0, from_self(stop)))->flag) {
			returnf(StopIteration);
		}
	}
	else {
		if (not(do_method(num, less, 1, 0, from_self(stop)))->flag) {
			returnf(StopIteration);
		}
	}
	assign(from_self(current), do_method(from_self(current), addout, 1, 0, from_self(step)));
	returnf(num);
}
