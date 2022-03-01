#include "all.h"
#define __FILE type_iterator_c
char* type_iterator_c = "type_iterator.c";


object* create__type_iterator(object* sth) {
	class_name name = sth->name;
	if (name != INT && name != ARRAY && name != STRING)
		__fast_error(__TYPE_ARG_ERROR, sth->name);
	object* self = (object*)calloc(1, sizeof(object));
	self->name = TYPE_ITERATOR;
	self->start = __enlon(sth);
	return self;
}



object* __next__type_iterator(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	size_t i;
	object* sth = self->start;
	switch (sth->name) {
	case INT: {
		i = self->len;
		if (i == sth->len) {
			__dop(sth);
			return StopIteration;
		}
		char numbit = self->n;
		bool bit = *((uchar*)sth->start + i) >> numbit;
		if (i + 1 == sth->len && bit == 0) {
			__dop(sth);
			return StopIteration;
		}
		bit &= 1;
		numbit++;
		if (numbit == 8) {
			self->n = 0;
			self->len++;
		}
		else
			self->n = numbit;
		__dop(self);
		return create__bool(bit);
	}
	case STRING: {
		i = self->len;
		char* part_ptr = (char*)sth->start + i, * symbol;
		if (*part_ptr == END) {
			__dop(sth);
			return StopIteration;
		}
		if (sth->n == UTF_8) {
			uchar mode = *part_ptr;
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
				symbol[j] = part_ptr[j];
			symbol[mode] = END;
			self->len += mode;
			__dop(self);
			return create__string(NULL, symbol, mode == 1 ? US_ASCII : UTF_8, 1);
		}
		else {
			symbol = (uchar*)malloc(2);
			symbol[0] = *part_ptr;
			symbol[1] = END;
			self->len += 1;
			__dop(self);
			return create__string(NULL, symbol, symbol[0] < 128 ? US_ASCII : WINDOWS_1251, 1);
		}
	}
	case ARRAY: {
		i = self->len;
		if (i == sth->len) {
			__dop(sth);
			return END;
		}
		self->len += 1;
		__dop(self);
		return *((object**)sth->start + i);
	}
	default:
		__fast_error(__TYPE_METHOD_ERROR, self->name);
	}
}
