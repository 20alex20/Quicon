#include "all.h"
#define __FILE class_name_c
char* class_name_c = "class_name.c";


object* create__class_name(uint name, char* string, ushort len1, ushort len, ...) {
	object* self = (object*)calloc(1, sizeof(object));
	self->name = CLASS_NAME;
	self->nop = name;
	self->len = string;
	self->flag = len1;
	self->n = len;
	ptrdiff_t* nextarg = (ptrdiff_t*)&len + 1;
	if (len > 0) {
		object** sth = self->start = malloc(len * lenptr);
		for (ushort i = 0; i < len; i++)
			sth[i] = __enlon(*nextarg++);
	}
	__classes[self->nop] = self;
	return self;
}



object* __equal_class_name__class_name(object* self, object* self2) {
	return __fast_dop_2(create__bool(self->nop == self2->nop));
}

object* __equal__class_name(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { CLASS_NAME };
	static object* (*functions[]) (object * self, object * self2) = { __equal_class_name__class_name };
	return __create_distribution(self, self2, class_names, functions, __equal_class_name__class_name);
}
