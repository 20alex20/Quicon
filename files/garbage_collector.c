#include "all.h"
#define __FILE garbage_collector_c
char* garbage_collector_c = "garbage_collector.c";


object* __asn(object** old_sth, object* new_sth) {
	object* obj = __enlon(new_sth);
	__dop(*old_sth);
	*old_sth = obj;
	return obj;
}


void __(object* sth) {
	if (sth != NULL && sth->name >= 3 && sth->n == 0)
		__destroy(sth);
}


object* __returnfm(object* ret, ...) {  // output value
	if (ret != NULL && ret->name >= 3)
		ret->nop -= 1;
	return ret;
}


object* __enlon_func(object* sth) {
	if (sth == NULL)
		__fast_error(__ANOTHER_ERROR, "An empty argument was passed");
	__enlon(sth);
	if (sth->name == FUNC && sth->flag)
		assign(sth, do_func(sth, 0, 0));
	return sth;
}


object* __enlon(object* sth) {  // enlarge one nop
	if (sth != NULL && sth->name >= 3)
		sth->nop += 1;
	return sth;
}


object* __dop_and_do(object* self, object* sth) {
	__dop(self);
	return sth;
}

object* __dop_and_do_2(object* self, object* self2,  object* sth) {
	__dtp(self, self2);
	return sth;
}


object* __dop(object* sth) {  // dell one pointer
	if (sth != NULL && sth->name >= 3) {
		sth->nop -= 1;
		if (sth->nop == 0)
			__destroy(sth);
	}
	return sth;
}

object* __dtp(object* sth1, object* sth2) {  // dell two pointers
	__dop(sth1);
	__dop(sth2);
	return NULL;
}

object* __dap(object** sth, ushort numargs) {  // dell all pointers in method
	for (ushort i = 0; i < numargs; i++)
		__dop(sth[i]);
	return NULL;
}


object* __clear(size_t n, ...) {
	object** nextarg = &n + 1;
	for (size_t i = 0; i < n; i++)
		__dop(nextarg[i]);
	return NULL;
}
