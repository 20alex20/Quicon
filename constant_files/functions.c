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


#define clear (2, __iter, i)
object* __is_sample(object* __func, object* num, ...) {
	start_func(NULL, arg(num), 1); object* __iter = NULL, * i = NULL;
	if_bool(do_method(num, equal, 1, 0, create__int(FALSE, 2))) {
		returnf(create__bool(TRUE));
	}
	if_bool(do_method(do_method(num, rod, 1, 0, create__int(FALSE, 2)), equal, 1, 0, create__int(FALSE, 0))) {
		returnf(create__bool(FALSE));
	}
	assign(i, create__int(FALSE, 2));
	while (do_method(do_method(do_method(i, multiply, 1, 0, i), less, 1, 0, num), to_bool, 0, 0)->flag) {
		do_func(print, 1, 0, do_method(num, rod, 1, 0, i));
		if_bool(do_method(do_method(num, rod, 1, 0, i), equal, 1, 0, create__int(FALSE, 0))) {
			returnf(create__bool(FALSE));
		}
		assign(i, do_method(i, addout, 1, 0, create__int(FALSE, 2)));
	}
	if_bool(do_method(do_method(num, rod, 1, 0, i), equal, 1, 0, create__int(FALSE, 0))) {
		returnf(create__bool(FALSE));
	}
	returnf(create__bool(TRUE));
}


/*
#define clear (0)
object* input(object* __func, object* start_str, object* stop_symbol, ...) {
	start_func(NULL, arg(start_str), 1, arg(stop_symbol), 2);
	object* ans = NULL;
	char symb, cur_len, symb2 = *((char*)stop_symbol->start);
	ull length = 0;
	uchar* current = malloc(lenptr * 2), * start = current, * next;

	if (not(do_method(start_str, equal, 1, 0, create__string("", US_ASCII))))
		do_func(print, 1, 1, start_str, named_arg(after, create__string("", US_ASCII)));
	symb = getchar();
	while (symb != symb2) {
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
	assign(ans, create__string(NULL, malloc(length * 8 + 1), WINDOWS_1251, length * 8));
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
*/

#define clear (0)
object* __input(object* __func, object* start_str, object* stop_symbol, ...) {
	start_func(NULL, arg(start_str), 1, arg(stop_symbol), 2);
	object* ans = NULL;
	char symb, cur_len, b;
	uint symb1, symb2 = 0;
	ull length = 0, real_length = 0;
	uchar* current = calloc(lenptr, 2), * start = current, * next, * st = stop_symbol->start;

	next = &symb2;
	symb2 = *st;
	if (symb2 < 128) cur_len = 1;
	else if (symb2 < 224) cur_len = 2;
	else if (symb2 < 240) cur_len = 3;
	else cur_len = 4;
	*next++ = symb2;
	for (char i = 1; i < cur_len; i++)
		*next++ = st[i];

	if (not(do_method(start_str, equal, 1, 0, create__string("", US_ASCII))))
		do_func(print, 1, 1, start_str, named_arg(after, create__string("", US_ASCII)));
	do {
		symb = getchar();
		if (symb < 128) cur_len = 1;
		else if (symb < 224) cur_len = 2;
		else if (symb < 240) cur_len = 3;
		else cur_len = 4;

		*current = getchar();
		for (char i = 1; i < cur_len; i++)
			current[i] = getchar();
		symb1 = *((uint*)current);
		current += 4;
		real_length += cur_len;
		length += 1;

		if (length % 2 == 0) {
			next = calloc(lenptr, 2);
			*((size_t*)current) = next;
			current = next;
		}
	} while (symb1 != symb2);

	assign(ans, create__string(NULL, malloc(real_length + 1), UTF_8, length * 2));
	next = ans->start;
	for (ull i = 0; i < length; i++) {
		symb = *start;
		if (symb < 128) cur_len = 1;
		else if (symb < 224) cur_len = 2;
		else if (symb < 240) cur_len = 3;
		else cur_len = 4;

		*next++ = symb;
		for (char i = 1; i < cur_len; i++)
			*next++ = start[i];
		start += 4;

		if (length % 2 == 0) {
			current = start - 8;
			start = *((size_t*)start);
			free(current);
		}
	}
	*next = END;
	free(start);
	returnf(ans);
}