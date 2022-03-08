#include "all.h"
#define __FILE bool_c
char* bool_c = "bool.c";


object __const_true = { BOOL, NULL, TRUE, NULL, NULL, NULL };
object __const_false = { BOOL, NULL, FALSE, NULL, NULL, NULL };
object* create__bool(bool flag) {
	return flag ? &__const_true : &__const_false;
}



char* __true_str = "TRUE";
char* __false_str = "FALSE";

object* __to_string__bool(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	return __fast_dop(create__string(self->flag ? __true_str : __false_str, US_ASCII));
}


object* __to_int__bool(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	return __fast_dop(create__int(FALSE, self->flag));
}



object* __equal_bool__bool(object* self, object* self2) {
	return __fast_dop_2(create__bool(self->flag == self2->flag));
}

object* __equal__bool(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { BOOL };
	static object* (*functions[]) (object * self, object * self2) = { __equal_bool__bool };
	return __create_distribution(self, self2, class_names, functions, __equal_bool__bool);
}


object* __more_bool__bool(object* self, object* self2) {
	return __fast_dop_2(create__bool(self->flag > self2->flag));
}

object* __more__bool(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { BOOL };
	static object* (*functions[]) (object * self, object * self2) = { __more_bool__bool };
	return __create_distribution(self, self2, class_names, functions, __more_bool__bool);
}



object* __less_bool__bool(object* self, object* self2) {
	return __fast_dop_2(create__bool(self->flag < self2->flag));
}

object* __less__bool(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { BOOL };
	static object* (*functions[]) (object * self, object * self2) = { __less_bool__bool };
	return __create_distribution(self, self2, class_names, functions, __less_bool__bool);
}
