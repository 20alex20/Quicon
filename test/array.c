#include "all.h"
#define __FILE array_c
char* array_c = "array.c";


object* create__array(size_t len, ...) {
	object* self = (object*)calloc(1, sizeof(object));
	self->name = ARRAY;
	self->len = len;
	if (len == 0)
		return self;
	object** ar = self->start = malloc(len * lenptr), **nextarg = &len + 1;
	if (!*nextarg)
		for (size_t i = 0; i < len; i++)
			ar[i] = create__noth;
	else
		for (size_t i = 0; i < len; i++)
			ar[i] = __enlon(nextarg[i]);
	return self;
}



#define __class_name String
#define clear (4, iterator, element, string, flag)
object* __to_string__array(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	object* iterator = NULL, * element = NULL, * string = NULL, * flag = NULL;
	assign(flag, create__bool(FALSE));
	assign(string, create__string("array[", US_ASCII));
	assign(iterator, create__type_iterator(self));
	while (assign(element, do_method(iterator, next, 0, 0))) {
		if (flag->flag) {
			assign(string, create__string(", ", US_ASCII));
		}
		else {
			assign(flag, create__bool(TRUE));
		}
		assign(string, do_func(from_self_class(addout), 2, 0, string, do_method(element, to_string, 0, 0)));
	}
	returnf(do_func(from_self_class(addout), 2, 0, string, create__string("]", US_ASCII)));
}



#define clear (0)
object* __tabi__array(object* __func, object* self, object* num, ...) {
	start_func(NULL, arg(num), 2, arg(self), 1);
	size_t n = __module_index2(num, self->len);
	returnf(*((object**)self->start + n));
}


#define clear (0)
object* __pubi__array(object* __func, object* self, object* num, object* sth, ...) {
	start_func(NULL, arg(num), 2, arg(self), 1, arg(sth), 3);
	object** n = (object**)self->start + __module_index2(num, self->len);
	__dop(*n);
	*n = __enlon(sth);
	returnf(sth);
}


#define clear (0)
object* __slice__array(object* __func, object* self, object* start, object* stop, object* step, ...) {
	start_func(NULL, arg(self), 1, arg(start), 2, arg(step), 4, arg(stop), 3);
	long long len = self->len, a = __module_index(start, len), o = __module_index(stop, len), e = to_c_size_t(step);
	bool flag = step->flag;
	if (a == o || (a > o) ^ flag)
		return create__array(0);
	object** arr = self->start;
	len = abs(o - a);
	len = len / e + (len % e != 0);
	object** newarray = (object**)malloc(len * lenptr);
	e *= 1 - 2 * self->flag;
	while ((a < o) ^ flag && a != o && a >= 0) {
		*newarray++ = __enlon(arr[a]);
		a += e;
	}
	object* sth = (object*)calloc(1, sizeof(object));
	sth->name = ARRAY;
	sth->len = len;
	sth->start = newarray;
	returnf(sth);
}



#define clear (0)
object* __reverse__array(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	size_t len = self->len;
	object** arr = (object**)malloc(len * lenptr), ** arrstart = arr, ** old = self->start;
	for (size_t i = 1; i <= len; i++)
		*arr++ = __enlon(old[len - i]);
	object* sth = (object*)calloc(1, sizeof(object));
	sth->name = ARRAY;
	sth->len = len;
	sth->start = arrstart;
	returnf(sth);
}
