#include "all.h"
#define __FILE string_c
char* string_c = "string.c";


object* create__string(ptrdiff_t sth, ...) {
	object* self = (object*)calloc(1, sizeof(object));
	self->name = STRING;
	self->nop = 0;
	ptrdiff_t* nextarg = &sth;
	if (nextarg[0] == NULL) {
		self->flag = TRUE;
		self->start = nextarg[1];
		self->n = nextarg[2];
		if (self->n == UTF_8)
			self->len = __strlen8(self->start);
		else
			self->len = nextarg[3];
	}
	else {
		char* string = nextarg[0];
		ushort encoding = nextarg[1];
		__only_usascii = TRUE;
		size_t len;
		if (encoding == US_ASCII)
			len = __strlen(string);
		else
			len = __strlen8(string);
		self->len = len;
		if (__only_usascii) {
			self->flag = FALSE;
			self->start = string;
			self->n = US_ASCII;
		}
		else if (encoding == WINDOWS_1251) {
			self->flag = TRUE;
			self->start = __from_utf8_to_w1251(string, len);
			self->n = WINDOWS_1251;
		}
		else {
			self->flag = FALSE;
			self->start = string;
			self->n = UTF_8;
		}
	}
	return self;
}



object* __to_int__string(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	return __fast_dop(create__int(TRUE, self->start));
}


object* __to_bool__string(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	return __fast_dop(create__bool(self->len > 0));
}


#define clear (3, iterator, symbol, arr)
object* __to_array__string(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	object* iterator = NULL, * symbol = NULL, * arr = NULL;
	assign(iterator, create__type_iterator(self));
	assign(arr, create__array(self->len, NULL));
	object** s = arr->start;
	while (assign(symbol, do_method(iterator, next, 0, 0)))
		*s++ = __enlon(symbol);
	returnf(arr);
}


#define clear (0)
object* __to_utf8__string(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	if (self->n % 2 == 0)
		return __returnfm(self);
	returnf(create__string(NULL, __from_w1251_to_utf8(self->start, self->len), UTF_8, self->len));
}

#define clear (0)
object* __to_windows1251__string(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	if (self->n < 2)
		return __returnfm(self);
	returnf(create__string(NULL, __from_utf8_to_w1251(self->start, self->len), WINDOWS_1251, self->len));
}



#define clear (0)
object* __tabi__string(object* __func, object* self, object* num, ...) {
	start_func(NULL, arg(num), 2, arg(self), 1);
	if (num->name != INT)
		__fast_error(__TYPE_ARG_ERROR, num->name);
	__fl();
	size_t len = self->len, n = __module_index2(num, len);
	uchar* string = self->start, * symbol;
	if (self->n == UTF_8) {
		n = __index_in_utf8(string, n, FALSE);
		uchar mode = string[n];
		if (mode < 128)
			mode = 1;
		else if (mode < 224)
			mode = 2;
		else if (mode < 240)
			mode = 3;
		else
			mode = 4;
		symbol = (char*)malloc(mode + 1);
		for (char j = 0; j < mode; j++)
			symbol[j] = string[n + j];
		symbol[mode] = END;
		self->len += mode;
		returnf(create__string(NULL, symbol, mode == 1 ? US_ASCII : UTF_8, 1));
	}
	else {
		symbol = (uchar*)malloc(2);
		symbol[0] = string[n];
		symbol[1] = END;
		self->len += 1;
		returnf(create__string(NULL, symbol, symbol[0] < 128 ? US_ASCII : WINDOWS_1251, 1));
	}
}


#define clear (0)
object* __slice__string(object* __func, object* self, object* start, object* stop, object* step, ...) {
	start_func(NULL, arg(self), 1, arg(start), 2, arg(step), 4, arg(stop), 3);
	long long len = self->len, a = __module_index(start, len), o = __module_index(stop, len), e = to_c_size_t(step), len8;
	bool flag = step->flag;
	uchar mode, encoding = US_ASCII;
	if (a == o || (a > o) ^ flag)
		return create__string("", US_ASCII);
	len8 = abs(o - a);
	len8 = len8 / e + (len8 % e != 0);
	uchar* string = self->start, * newstring, * newstring_start;
	if (self->n == UTF_8) {
		newstring = (uchar*)malloc(len8 + min(3 * len8, __strlen(string) - len) + 1);
		newstring_start = newstring;
		len = 1 - 2 * flag;
		string += __index_in_utf8(string, a, FALSE);
		while (TRUE) {
			mode = *string;
			if (mode < 128)
				mode = 1;
			else if (mode < 224)
				mode = 2;
			else if (mode < 240)
				mode = 3;
			else
				mode = 4;
			if (mode > 1)
				encoding = UTF_8;
			for (uchar h = 0; h < mode; h++)
				*newstring++ = string[h];
			a += e * len;
			if ((a >= o) ^ flag || a == o || a < 0)
				break;
			string += __index_in_utf8(string, e, flag);
		}
		*newstring = END;
		len = newstring - newstring_start;
		newstring_start = realloc(newstring_start, len + 1);
		returnf(create__string(NULL, newstring_start, encoding, len));
	}
	else {
		newstring = (uchar*)malloc(len8 + 1);
		newstring_start = newstring;
		e *= 1 - 2 * flag;
		while ((a < o) ^ flag && a != o && a >= 0) {
			*newstring++ = mode = string[a];
			if (mode >= 128)
				encoding = WINDOWS_1251;
			a += e;
		}
		*newstring = END;
		returnf(create__string(NULL, newstring_start, encoding, newstring - newstring_start));
	}
}



object* __addout_string__string(object* self, object* self2) {
	__to_one_type(&self, &self2);
	char* s1 = self->start;
	char* s2 = self2->start;
	size_t i = 0, len = (self->n == UTF_8 ? __strlen(s1) : self->len) + (self2->n == UTF_8 ? __strlen(s2) : self2->len);
	char* s3 = (char*)malloc(len + 1);
	while (*s1)
		s3[i++] = *s1++;
	while (*s2)
		s3[i++] = *s2++;
	s3[i] = END;
	__dtp(self, self2);
	return create__string(NULL, s3, max(self->n, self2->n), len);
}

object* __addout__string(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { STRING };
	static object* (*functions[]) (object * self, object * self2) = { __addout_string__string };
	return __create_distribution(self, self2, class_names, functions, __addout_string__string);
}



object* __equal_string__string(object* self, object* self2) {
	__to_one_type(&self, &self2);
	if (self->len != self2->len)
		return __fast_dop_2(create__bool(FALSE));
	uchar* str1 = self->start, * str2 = self2->start;
	while (*str1 && *str2) {
		uchar s1 = *str1++, s2 = *str2++;
		if (s1 != s2)
			return __fast_dop_2(create__bool(FALSE));
	}
	if (!*str1 && !*str2)
		return __fast_dop_2(create__bool(TRUE));
	return __fast_dop_2(create__bool(FALSE));
}

object* __equal__string(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { STRING };
	static object* (*functions[]) (object * self, object * self2) = { __equal_string__string };
	return __create_distribution(self, self2, class_names, functions, __equal_string__string);
}


object* __more_string__string(object* self, object* self2) {
	__to_one_type(&self, &self2);
	if (self->len != self2->len)
		return __fast_dop_2(create__bool(self->len > self2->len));
	uchar* str1 = self->start, * str2 = self2->start;
	while (*str1 && *str2) {
		uchar s1 = *str1++, s2 = *str2++;
		if (s1 != s2)
			return __fast_dop_2(create__bool(s1 > s2));
	}
	if (!*str1 && !*str2)
		return __fast_dop_2(create__bool(FALSE));
	return __fast_dop_2(create__bool(*str1 != END));
}

object* __more__string(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { STRING };
	static object* (*functions[]) (object * self, object * self2) = { __more_string__string };
	return __create_distribution(self, self2, class_names, functions, __more_string__string);
}


object* __less_string__string(object* self, object* self2) {
	__to_one_type(&self, &self2);
	if (self->len != self2->len)
		return __fast_dop_2(create__bool(self->len < self2->len));
	uchar* str1 = self->start, * str2 = self2->start;
	while (*str1 && *str2) {
		uchar s1 = *str1++, s2 = *str2++;
		if (s1 != s2)
			return __fast_dop_2(create__bool(s1 < s2));
	}
	if (!*str1 && !*str2)
		return __fast_dop_2(create__bool(FALSE));
	return __fast_dop_2(create__bool(*str2 != END));
}

object* __less__string(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { STRING };
	static object* (*functions[]) (object * self, object * self2) = { __less_string__string };
	return __create_distribution(self, self2, class_names, functions, __less_string__string);
}



#define clear (2, iterator, symbol)
object* __reverse__string(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	object* iterator = NULL, * symbol = NULL;
	size_t len = __strlen(self->start);
	size_t i = len;
	char* string = (char*)malloc(i + 1);
	string[i] = END;
	assign(iterator, create__type_iterator(self));
	while (assign(symbol, do_method(iterator, next, 0, 0))) {
		char* curstring = symbol->start;
		char curlen = __strlen(curstring);
		i -= curlen;
		for (char j = 0; j < curlen; j++)
			string[i + j] = curstring[j];
	}
	returnf(create__string(NULL, string, self->n, len));
}
