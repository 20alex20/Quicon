#include "all.h"
#define __FILE functions_c
char* functions_c = "functions.c";


object* __return_self(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	return __returnfm(self);
}


object* __end_program(object* __func, ...) {
	start_func_0();
	printf("\n");
	system("pause");
	exit(EXIT_SUCCESS);
}


object* __copy(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	if (self->name < 3)
		return self;
	__enlon(self);
	object* obj = (object*)malloc(sizeof(object));
	obj->name = self->name;
	obj->nop = 0;
	obj->len = self->len;
	obj->n = self->n;
	obj->flag = self->flag;
	size_t len = obj->n, i = 0;
	object** sthst, ** objst;
	switch (self->name) {
	case TYPE_ITERATOR:
		obj->start = __enlon(self->start);
		break;
	case STRING:
	case INT: {
		if (self->name == STRING && self->n == UTF_8)
			len = __strlen(self->start) + 1;
		else
			len = self->len + (self->name == STRING);
		obj->start = malloc(len);
		char* sthst = self->start, * objst = obj->start;
		while (i < len) {
			objst[i] = sthst[i];
			i++;
		}
		break;
	}
	case ARRAY:
		len = self->len;
	default:
		sthst = self->start;
		obj->start = objst = malloc(len * lenptr);
		while (i < len) {
			objst[i] = __enlon(sthst[i]);
			i++;
		}
		break;
	}
	__dop(self);
	return obj;
}


object* __length(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	size_t len;
	switch (__enlon(self)->name) {
	case TYPE_ITERATOR:
	case BOOL:
	case NOTH:
		return create__noth;
	case ARRAY:
	case STRING:
	case INT:
		len = self->len;
		break;
	default:
		len = self->n;
		break;
	}
	__dop(self);
	object* obj = calloc(1, sizeof(object));
	obj->name = INT;
	uchar lenlen, i;
	for (i = 1; i <= 8; i++)
		if (len >> (8 * i) == 0) {
			lenlen = i;
			break;
		}
	uchar* n = obj->start = malloc(lenlen);
	for (i = 0; i < lenlen; i++)
		n[i] = (len >> i) & 255;
	obj->len = lenlen;
	return obj;
}


object* __type_of(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	return __fast_dop(__classes[self->name]);
}


object* __is_instance(object* __func, object* self, object* name, ...) {
	start_func(NULL, arg(name), 2, arg(self), 1);
	if (name->name != CLASS_NAME)
		__fast_error(__TYPE_ARG_ERROR, name->name);
	return __fast_dop(create__bool(self->name == name->nop));
}


object* __to_another_type(object* __func, object* self, object* name, ...) {
	start_func(NULL, arg(name), 2, arg(self), 1);
	if (name->name != CLASS_NAME)
		__fast_error(__TYPE_ARG_ERROR, name->name);
	uint* arr = __to_another_type_arr[name->nop];
	if (arr == NULL)
		__fast_error(__TYPE_METHOD_ERROR, self->nop);
	return __pm(self, arr, 0, 0)(__boofer, __boofer2);
}


#define clear (4, iterator, element, string, flag)
object* __print(object* __func, object* arr, object* before, object* between, object* after, ...) {
	start_func(1, arg(after), 4, arg(arr), 1, arg(before), 2, arg(between), 3);
	object* iterator = NULL, * element = NULL, * string = NULL, * flag = NULL;
	if_bool(not(do_func(is_instance, 2, 0, after, String)))
		type_arg_error(after);
	if_bool(not(do_func(is_instance, 2, 0, arr, Array)))
		type_arg_error(arr);
	if_bool(not(do_func(is_instance, 2, 0, before, String)))
		type_arg_error(before);
	if_bool(not(do_func(is_instance, 2, 0, between, String)))
		type_arg_error(between);
	assign(flag, create__bool(FALSE));
	assign(string, before);
	assign(iterator, create__type_iterator(arr));
	while (assign(element, do_method(iterator, next, 0, 0))) {
		if (flag->flag) {
			assign(string, do_method(string, addout, 1, 0, between));
		}
		else {
			assign(flag, create__bool(TRUE));
		}
		assign(string, do_method(string, addout, 1, 0, do_method(element, to_string, 0, 0)));
	}
	assign(string, do_method(do_method(string, addout, 1, 0, after), to_utf8, 0, 0));
	printf(string->start);
	returnf(create__noth());
}


#define clear (0)
object* __input(object* __func, object* start_str, ...) {
	start_func(NULL, arg(start_str), 1);
	object* ans = NULL;
	char symb, cur_len = 0;
	ull length = 0;
	uchar* current = malloc(lenptr * 2), * start = current, * next;

	if (not(do_method(start_str, equal, 1, 0, create__string("", US_ASCII))))
		do_func(print, 1, 1, start_str, named_arg(after, create__string("", US_ASCII)));
	symb = getchar();
	while (symb != '\n') {
		current[cur_len] = symb;
		cur_len += 1;
		if (cur_len == 8) {
			next = malloc(lenptr * 2);
			*((size_t*)current + 1) = next;
			current = next;
			cur_len = 0;
			length += 1;
		}
		symb = getchar();
	}
	assign(ans, create__string(NULL, malloc(length * 8 + cur_len + 1), WINDOWS_1251, length * 8 + cur_len));
	next = ans->start;
	for (ull i = 0; i < length; i++) {
		for (char j = 0; j < 8; j++)
			*next++ = start[j];
		current = start;
		start = *((size_t*)start + 1);
		free(current);
	}
	for (char j = 0; j < cur_len; j++)
		*next++ = start[j];
	*next = END;
	free(start);
	returnf(ans);

}

#define clear (0)
object* __is_leap (object* __func, object* n, object* month, ...) { start_func(NULL, arg(month), 2, arg(n), 1); 
    if_bool (not(do_method(month, equal, 1, 0, create__int(FALSE, 2)))) {
        returnf(create__int(FALSE, 0));
    }
    if_bool (or(and(not(do_method(do_method(n, rod, 1, 0, create__int(FALSE, 100)), equal, 1, 0, create__int(FALSE, 0))), do_method(do_method(n, rod, 1, 0, create__int(FALSE, 4)), equal, 1, 0, create__int(FALSE, 0))), do_method(do_method(n, rod, 1, 0, create__int(FALSE, 400)), equal, 1, 0, create__int(FALSE, 0)))) {
       returnf(create__int(FALSE, 1));
    }
    returnf(create__int(FALSE, 0));
}

#define clear (0)
object* __add_0 (object* __func, object* n, ...) { start_func(NULL, arg(n), 1); 
    if_bool (do_method(n, less, 1, 0, create__int(FALSE, 10))) {
        returnf(do_method(create__string("0", UTF_8), addout, 1, 0, do_method(n, to_string, 0, 0)));
    }
    returnf(do_method(n, to_string, 0, 0));
}
