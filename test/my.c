#include "all.h"
#define __FILE my_c
char* my_c = "my.c";


object* __create__my(object* __func) {
    start_func_0();
    return __create_class(My);
}


#define __class MY
#define __class_name My
#define clear (0)
object* __my (object* __func, object* self, object* num, ...) { start_func(NULL, arg(num), 2, arg(self), 1); 
    assign(from_self(er), from_self_class(k));
}

#define __class MY
#define __class_name My
#define clear (1, ans)
object* __next__my (object* __func, object* self, ...) { start_func(NULL, arg(self), 1); start_method(); object* ans = NULL;
    assign(ans, do_method(from_self(er), next, 0, 0));
    if_bool (is(ans, StopIteration)) {
        returnf(StopIteration);
    }
    returnf(do_method(ans, multiply, 1, 0, create__int(FALSE, 789)));
}

#define __class MY
#define __class_name My
#define __class MY
#define __class_name My
#define clear (0)
object* __addout_my__my (object* __func, object* self, object*  self2, ...) { start_func(NULL, arg(self), 1, arg(self2), 2); start_method(); start_method2(); 
    __(do_func(print, 1, 0, create__string("0", UTF_8)));
}

object* __addout__my (object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { MY };
	static object* (*functions[]) (object * self, object * self2) = { __addout_my__my };
	return __create_distribution(self, self2, class_names, functions, NULL);
}
