#include "all.h"
#define __FILE hidden_c
char* hidden_c = "hidden.c";


object* __create_class(object* self) {
	object* sth = (object*)calloc(1, sizeof(object));
	sth->name = self->nop;
	ushort len = sth->n = self->flag;
	if (len > 0) {
		object** some = sth->start = malloc((uint)len * lenptr);
		for (ushort i = 0; i < len; i++)
			some[i] = create__noth;
	}
	return sth;
}


void __destroy(object* sth) {
	size_t len = sth->n;
	object** memory = sth->start;
	switch (sth->name) {
	case TYPE_ITERATOR:
		break;
	case STRING:
		if (!sth->flag)
			break;
	case INT:
		break;
	case ARRAY:
		len = sth->len;
	default:
		for (size_t i = 0; i < len; i++)
			__dop(memory[i]);
		free(memory);
		break;
	}
	free(sth);
}


object* __empty_arg() {
	return NULL;
}


void __to_one_type(object** self, object** self2) {
	ushort type = max((*self)->n, (*self2)->n);
	if (type == UTF_8) {
		__asn(self, do_method(*self, to_utf8, 0, 0));
		__asn(self2, do_method(*self2, to_utf8, 0, 0));
	}
	else if (type == WINDOWS_1251) {
		__asn(self, do_method(*self, to_windows1251, 0, 0));
		__asn(self2, do_method(*self2, to_windows1251, 0, 0));
	}
}

object* __create_distribution(object* self, object* self2, uint* class_names, object* (**functions) (object * self, object * self2), object* (*cur) (object* self, object* self2)) {
	size_t index = __universal_recursion(class_names, 1, self2->name);
	if (index == NULL)
		return cur(self, __enlon(do_func(to_another_type, 2, 0, self2, __classes[self->name])));
	return functions[(index - (size_t)class_names) / 4](self, self2);
}


void __start_func_0() {
	if (__pos != 0)\
		__error(__file, __line, __TOO_MANY_ARGS_ERROR, __pos); \
	if (__nam != 0)\
		__error(__file, __line, __TOO_MANY_NAMED_ARGS_ERROR, __nam);
}


void __open_access(object* self, object* class, class_name it) {
	if (self->name != it || class->name != CLASS_NAME || class->nop != it)
		__error(__file, __line, __ANOTHER_ERROR, "Access denied");
}


object* __free_arr(object* ret, object** sth) {
	free(sth);
	return ret;
}


object* (*__pf(object* func, ushort pos, ushort nam))() {
	__pos = pos;
	__nam = nam;
	__boofer = func;
	return func->len;
}


ull* __recursia_from2(ull* start, ushort len, uint num) {
	ushort l1 = len / 2, l2 = len - l1;
	uint n = *((uint*)(start + l1));
	if (n == num)
		return start + l1;
	if (len == 1)
		return NULL;
	if (num < n)
		return __recursia_from2(start, l1, num);
	if (num > n)
		return __recursia_from2(start + l1, l2, num);
}


object* (*__pm(object* self, uint* name, ushort pos, ushort nam))() {
	__pos = pos + 1;
	__nam = nam;
	__boofer2 = self;
	if (self->name == CLASS_NAME)
		__fast_error(__ANOTHER_ERROR, "You can't apply the method to the class_name");
	uint* index = __recursia_from2(name + 1, *name, self->name);
	if (index == NULL)
		__fast_error(__NAME_ARG_ERROR_2, self->name);
	uint i = *(index + 1);
	__boofer = *((object**)__classes[self->name]->start + (i >> 16) - 1);
	return __boofer->len;
}


uint* __universal_recursion(uint* start, ushort len, uint num) {
	ushort l1 = len / 2, l2 = len - l1;
	uint n = *(start + l1);
	if (n == num)
		return start + l1;
	if (len == 1)
		return NULL;
	if (num < n)
		return __universal_recursion(start, l1, num);
	if (num > n)
		return __universal_recursion(start + l1, l2, num);
}


object** __from2(object* self, uint* name) {
	uint* index;
	if (self->name == CLASS_NAME) {
		index = __recursia_from2(name + 1, *name, self->nop);
		if (index == NULL)
			__fast_error(__NAME_ARG_ERROR_2, self->nop);
		return (object**)__classes[self->name]->start + (*(index + 1) >> 16) - 1;
	}
	else {
		index = __recursia_from2(name + 1, *name, self->name);
		if (index == NULL)
			__fast_error(__NAME_ARG_ERROR_2, self->name);
		uint i = *(index + 1);
		object** sth;
		if (i >> 16 > 0)
			sth = (object**)__classes[self->name]->start + (i >> 16) - 1;
		else
			sth = (object**)self->start + i - 1;
		__(self);
		return sth;
	}
}


char __lenbit(uchar n) {
	char i = 1;
	while (1 << i <= n)
		i++;
	return i;
}


size_t __strlen(char* s) {
	register size_t i = 0;
	while (s[i]) i++;
	return i;
}

size_t __strlen8(uchar* s) {  // string length with utf-8
	register size_t i = 0, j = 0;
	uchar next;
	while (next = s[i + j]) {
		if (next >= 128) {
			__only_usascii = FALSE;
			if (next < 224)
				j += 1;
			else if (next < 240)
				j += 2;
			else
				j += 3;
		}
		i++;
	}
	return i;
}

size_t __module_index2(object* num, size_t len) {
	size_t n = to_c_size_t(num);
	if (num->flag) {
		if (len < n)
			__error(__file, __line, __INDEX_ERROR, ~n + 1, len);
		return len - n;
	}
	else {
		if (len <= n)
			__error(__file, __line, __INDEX_ERROR, n, len);
		return n;
	}
}

size_t __module_index(object* num, size_t len) {
	size_t n = to_c_size_t(num);
	if (num->flag)
		return n < len ? len - n : 0;
	else
		return n < len ? n : len - 1;
}

long long __index_in_utf8(uchar* s, long long n, bool flag) {
	long long i = 0, j = 0;
	if (flag)
		while (-1 * i < n) {
			i--;
			while (s[i + j] >= 128 && s[i + j] < 192)
				j--;
		}
	else {
		uchar next;
		while (i < n) {
			next = s[i + j];
			if (next >= 128)
				if (next < 224)
					j += 1;
				else if (next < 240)
					j += 2;
				else
					j += 3;
			i++;
		}
	}
	return i + j;
}

object* __fm(object* sth, bool flag, bool f, object* sth1) {
	if (sth->name != INT)
		__fast_error(__TYPE_ARG_ERROR, sth->name);
	sth->flag = flag;
	return sth1;
}


void __finarg(ushort len, uint* names, ushort have_arr, object** oldargs, object** newargs) {  // fill in arg
	if (__nam > len)
		__error(__file, __line, __TOO_MANY_NAMED_ARGS_ERROR, __nam, len);
	bool* flags = calloc(len, 1);
	uint* names_named = NULL, i = 0;
	object** named = NULL, ** newargs_named = NULL;
	if (__nam > 0) {
		named = malloc(__nam * lenptr);
		newargs_named = newargs + __pos;
		names_named = malloc(__nam * 4);
		while (i < __nam) {
			names_named[i] = newargs_named[i * 2];
			named[i] = newargs_named[i * 2 + 1];
			i++;
		}
		i = 0;
	}
	if (have_arr != 0) {
		have_arr -= 1;
		size_t m = min(__pos, have_arr);
		while (i < m) {
			if (newargs[i] != NULL) {
				newargs[i] = __enlon_func(newargs[i]);
				flags[i] = TRUE;
			}
			i++;
		}
		if (__pos > have_arr) {
			m = __pos - have_arr;
			object** sth = malloc(m * lenptr);
			for (size_t j = 0; j < m; j++) {
				object* it = newargs[i + j];
				if (it == NULL)
					__error(__file, __line, __NO_ELEMENT_ARRAY_ERROR, j);
				sth[j] = __enlon_func(it);
			}
			object* self = (object*)calloc(1, sizeof(object));
			self->name = ARRAY;
			self->len = m;
			self->start = sth;
			newargs[have_arr] = __enlon(self);
			flags[have_arr] = TRUE;
		}
	}
	else {
		if (__pos > len)
			__error(__file, __line, __TOO_MANY_ARGS_ERROR, __pos, len);
		while (i < __pos) {
			if (newargs[i]) {
				newargs[i] = __enlon_func(newargs[i]);
				flags[i] = TRUE;
			}
			i++;
		}
	}
	i = 0;
	while (i < __nam) {
		if (named[i]) {
			uint* index_null = __recursia_from2(names, len, names_named[i]);
			if (index_null == NULL)
				__error(__file, __line, __NAME_ARG_ERROR, names_named[i]);
			uint index = *(index_null + 1) - 1;
			if (flags[index])
				__error(__file, __line, __MANY_VALUES_ARG_ERROR, index);
			newargs[index] = __enlon_func(named[i]);
			flags[index] = TRUE;
		}
		i++;
	}
	i = 0;
	while (i < len) {
		if (!flags[i]) {
			if (!oldargs[i])
				__error(__file, __line, __NO_ARG_ERROR, i);
			newargs[i] = __enlon_func(oldargs[i]);
		}
		i++;
	}
	free(flags);
	if (__nam > 0) {
		free(named);
		free(names_named);
	}
}

object** __finarg2(ushort len, uint* names, object** oldargs, object** newargs) {
	if (__nam > len)
		__error(__file, __line, __TOO_MANY_NAMED_ARGS_ERROR, __nam, len);
	object** answer = malloc(len * lenptr), ** named = newargs + __pos, * boofer;
	bool* flags = calloc(len, 1);
	uint i = 0;
	if (__pos > len)
		__error(__file, __line, __TOO_MANY_ARGS_ERROR, __pos, len);
	while (i < __pos) {
		answer[i] = __enlon(newargs[i]);
		flags[i] = TRUE;
		i++;
	}
	i = 0;
	while (i < __nam) {
		uint* index_null = __recursia_from2(names, len, named[i * 2]);
		if (index_null == NULL)
			__error(__file, __line, __NAME_ARG_ERROR, named[i * 2]);
		uint index = *(index_null + 1) - 1;
		if (flags[index])
			__error(__file, __line, __MANY_VALUES_ARG_ERROR, index);
		answer[index] = __enlon(named[i * 2 + 1]);
		flags[index] = TRUE;
		i++;
	}
	i = 0;
	while (i < len) {
		if (!flags[i])
			answer[i] = __enlon(oldargs[i]);
		i++;
	}
	free(flags);
	return answer;
}


object* __getarg(bool flag, ...) {
	static object** newargs, ** oldargs;
	object** nextarg = (object**)&flag + 1;
	if (flag) {
		oldargs = nextarg[0];
		newargs = nextarg[1];
		return NULL;
	}
	ushort i = *((ushort*)nextarg);
	object* arg = newargs[i];
	if (!arg) {
		arg = oldargs[i];
		if (!arg)
			__error(__file, __line, __NO_ARG_ERROR, i);
	}
	return __enlon_func(arg);
}


char* __decimal_addition(char* first, char* second, char notfr) {
	char remainder = 0, n;
	size_t len1 = __strlen(first), len2 = __strlen(second), max_len = max(len1, len2), i = 0;
	char* third = (char*)malloc(max_len + 2);
	while (i < max_len) {
		n = (i < len1 ? first[i] - '0' : 0) + (i < len2 ? second[i] - '0' : 0) + remainder;
		if (n >= 10) {
			third[i] = n - 10 + '0';
			remainder = 1;
		}
		else {
			third[i] = n + '0';
			remainder = 0;
		}
		i++;
	}
	if (remainder)
		third[i++] = remainder + '0';
	third[i] = END;
	if (*first != notfr)
		free(first);
	return third;
}

char __decnot_to_binnot(bool flag_start, ...) {  // decimal notation to binary notation
	static bool flag_mode;
	static char flag_i;
	static char* curnum_start;
	static int num;
	if (flag_start) {
		ptrdiff_t* nextarg = &flag_start;
		flag_mode = nextarg[1];
		flag_i = 0;  // flag_i = FALSE;
		if (flag_mode)
			curnum_start = nextarg[2];
		else
			num = nextarg[2];
		return NULL;
	}
	if (flag_mode) {
		if (*curnum_start == END) {
			if (flag_i)
				free(curnum_start);
			return END;
		}
		char* curnum = curnum_start;
		char rotd;  // remainder of the division
		if (*curnum == '1') {
			rotd = 1;
			curnum++;
		}
		else
			rotd = 0;
		char* newnum_start = (char*)malloc(__strlen(curnum) + 1);  // new number
		char* newnum = newnum_start;
		while (*curnum) {
			char number = rotd * 10 + *curnum++ - '0';
			*newnum++ = number / 2 + '0';
			rotd = number % 2;
		}
		*newnum = END;
		if (flag_i)
			free(curnum_start);
		else
			flag_i = TRUE;
		curnum_start = newnum_start;
		return rotd + '0';
	}
	else {
		if (num >> flag_i == 0)
			return END;
		char bit = (num >> flag_i) & 1;
		flag_i++;
		return bit + '0';
	}
}


ushort* __recursia_w1251(uint* start, size_t len, ushort num) {
	size_t l1 = len / 2, l2 = len - l1;
	ushort n = *((ushort*)(start + l1));
	if (n == num)
		return start + l1;
	if (len == 1)
		return NULL;
	if (num < n)
		return __recursia_w1251(start, l1, num);
	if (num > n)
		return __recursia_w1251(start + l1 , l2, num);
}

ushort __windows_1251[126] = { 160, 160, 164, 164, 166, 166, 167, 167, 169, 169, 171, 171, 172, 172, 173, 173, 174, 174, 176, 176, 177, 177, 181, 181, 182, 182, 183, 183, 187, 187, 1025, 168, 1026, 128, 1027, 129, 1028, 170, 1029, 189, 1030, 178, 1031, 175, 1032, 163, 1033, 138, 1034, 140, 1035, 142, 1036, 141, 1038, 161, 1039, 143, 1105, 184, 1106, 144, 1107, 131, 1108, 186, 1109, 190, 1110, 179, 1111, 191, 1112, 188, 1113, 154, 1114, 156, 1115, 158, 1116, 157, 1118, 162, 1119, 159, 1168, 165, 1169, 180, 8211, 150, 8212, 151, 8216, 145, 8217, 146, 8218, 130, 8220, 147, 8221, 148, 8222, 132, 8224, 134, 8225, 135, 8226, 149, 8230, 133, 8240, 137, 8249, 139, 8250, 155, 8364, 136, 8470, 185, 8482, 153 };

char* __from_utf8_to_w1251(uchar* utf_8, size_t len) {
	ushort buffer, * buffer2;
	uchar* answer = (uchar*)malloc(len + 1), * answer_start = answer, * utf_8_start = utf_8;
	while (*utf_8) {
		uchar mode = *utf_8++, rec;
		if (mode < 128)
			*answer++ = mode;
		else if (mode < 240) {
			if (mode < 224) {
				buffer = (mode & 31) << 6 | *utf_8++ & 63;
				if (buffer >= 1040 && buffer <= 1103) {
					*answer++ = buffer - 848;
					continue;
				}
			}
			else {
				rec = *utf_8++;
				buffer = (mode & 15) << 12 | (rec & 63) << 6 | *utf_8++ & 63;
			}
			buffer2 = __recursia_w1251(__windows_1251, 63, buffer);
			if (buffer2 == NULL)
				__fast_error(__W1251_ERROR, utf_8_start);
			*answer++ = *(buffer2 + 1);
		}
		else
			__fast_error(__W1251_ERROR, utf_8_start);
	}
	*answer = END;
	return answer_start;
}


ushort __utf_8[64] = { 1026, 1027, 8218, 1107, 8222, 8230, 8224, 8225, 8364, 8240, 1033, 8249, 1034, 1036, 1035, 1039, 1106, 8216, 8217, 8220, 8221, 8226, 8211, 8212, 8482, 1113, 8250, 1114, 1116, 1115, 1119, 160, 1038, 1118, 1032, 164, 1168, 166, 167, 1025, 169, 1028, 171, 172, 173, 174, 1031, 176, 177, 1030, 1110, 1169, 181, 182, 183, 1105, 8470, 1108, 187, 1112, 1029, 1109, 1111 };

char* __from_w1251_to_utf8(uchar* windows1251, size_t len) {
	uchar* answer = (uchar*)malloc(len * 3 + 1), * answer_start = answer;
	while (*windows1251) {
		uchar mode = *windows1251++;
		if (mode < 128) {
			*answer++ = mode;
		}
		else {
			ushort buffer;
			if (mode < 192)
				buffer = __utf_8[mode - 128];
			else
				buffer = mode + 848;
			if (buffer < 2048) {
				*answer++ = 192 | buffer >> 6;
				*answer++ = 128 | (buffer & 63);
			}
			else {
				*answer++ = 224 | buffer >> 12;
				*answer++ = 128 | ((buffer >> 6) & 63);
				*answer++ = 128 | (buffer & 63);
			}
		}
	}
	*answer = END;
	answer_start = realloc(answer_start, answer - answer_start + 1);
	return answer_start;
}
