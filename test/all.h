#ifndef ALL_H
#define ALL_H

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "global_variables.h"


void __destroy(object* sth);
object* __create_class(object* self);
void __to_one_type(object** self, object** self2);
object* __empty_arg();
object* __create_distribution(object* self, object* self2, uint* class_names, object* (**functions) (object* self, object* self2), object* (*cur) (object* self, object* self2));
object* (*__pm(object* self, uint* name, ushort pos, ushort nam))();
void __start_func_0();
uint* __universal_recursion(uint* start, ushort len, uint num);
object** __from2(object* self, uint* name);
void __open_access(object* self, object* class, class_name it);
object* __free_arr(object* ret, object** sth);
object* (*__pf(object* func, ushort pos, ushort nam))();
char __lenbit(uchar n);
size_t __strlen(char* s);
size_t __strlen8(uchar* s);
size_t __module_index2(object* num, size_t len);
size_t __module_index(object* num, size_t len);
long long __index_in_utf8(uchar* s, long long n, bool flag);
object* __fm(object* sth, bool flag, bool f, object* sth1);
void __finarg(ushort len, uint* names, ushort have_arr, object** oldargs, object** newargs);
object** __finarg2(ushort len, uint* names, object** oldargs, object** newargs);
object* __getarg(bool flag, ...);
char* __decimal_addition(char* first, char* second, char notfr);
char __decnot_to_binnot(char* curnum_start);
char* __from_utf8_to_w1251(uchar* utf_8, size_t len);
char* __from_w1251_to_utf8(uchar* windows1251, size_t len);

void start_program();

void __error(char* name, uint line, errors nomer, intptr_t sth, ...);

object* __asn(object** old_obj, object* new_obj);  // !
void __(object* sth);
object* __returnfm(object* ret, ...);
object* __enlon_func(object* sth);
object* __enlon(object* sth);
object* __dop(object* sth);
object* __dop_and_do(object* self, object* sth);
object* __dop_and_do_2(object* self, object* self2, object* sth);
object* __dtp(object* sth1, object* sth2);
object* __dap(object** sth, ushort numargs);
object* __clear(size_t n, ...);


object* __return_self(object* __func, object* self, ...);
object* __end_program(object* __func, ...);
object* __copy(object* __func, object* self, ...);
object* __length(object* __func, object* self, ...);
object* __type_of(object* __func, object* self, ...);
object* __is_instance(object* __func, object* self, object* name, ...);
object* __to_another_type(object* __func, object* self, object* name, ...);
object* __print(object* __func, object* arr, object* before, object* between, object* after, ...);
object* __input(object* __func, object* start_str, ...);

object* create__int(bool flag, intptr_t decnum);
object* __to_string__int(object* __func, object* self, ...);
object* __to_bool__int(object* __func, object* self, ...);
object* __addout__int(object* __func, object* self, object* self2, ...);
object* __subtractout__int(object* __func, object* self, object* self2, ...);
object* __multiply__int(object* __func, object* self, object* self2, ...);
object* __divide__int(object* __func, object* self, object* self2, ...);
object* __rod__int(object* __func, object* self, object* self2, ...);
object* __equal__int(object* __func, object* self, object* self2, ...);
object* __more__int(object* __func, object* self, object* self2, ...);
object* __less__int(object* __func, object* self, object* self2, ...);
object* __module__int(object* __func, object* self, ...);
object* __bin__int(object* __func, object* self, ...);
object* __numsign__int(object* __func, object* self, ...);

object* create__string(ptrdiff_t sth, ...);
object* __to_int__string(object* __func, object* self, ...);
object* __to_bool__string(object* __func, object* self, ...);
object* __to_array__string(object* __func, object* self, ...);
object* __to_utf8__string(object* __func, object* self, ...);
object* __to_windows1251__string(object* __func, object* self, ...);
object* __tabi__string(object* __func, object* self, object* num, ...);
object* __slice__string(object* __func, object* self, object* start, object* stop, object* step, ...);
object* __addout__string(object* __func, object* self, object* self2, ...);
object* __equal__string(object* __func, object* self, object* self2, ...);
object* __more__string(object* __func, object* self, object* self2, ...);
object* __less__string(object* __func, object* self, object* self2, ...);
object* __reverse__string(object* __func, object* self, ...);

object* create__func(object* (*func) (), bool flag, ushort len, ...);
object* __change__func(object** __func, object* self, object* flag, ...);

object* create__array(size_t len, ...);
object* __to_string__array(object* __func, object* self, ...);
object* __tabi__array(object* __func, object* self, object* num, ...);
object* __pubi__array(object* __func, object* self, object* num, object* sth, ...);
object* __slice__array(object* __func, object* self, object* start, object* stop, object* step, ...);
object* __reverse__array(object* __func, object* self, ...);

object* create__class_name(uint name, char* string, ushort len1, ushort len, ...);
object* __equal__class_name(object* __func, object* self, object* self2, ...);

object* create__type_iterator(object* sth);
object* __next__type_iterator(object* __func, object* self, ...);

object* create__bool(bool flag);
object* __to_string__bool(object* __func, object* self, ...);
object* __to_int__bool(object* __func, object* self, ...);
object* __equal__bool(object* __func, object* self, object* self2, ...);
object* __more__bool(object* __func, object* self, object* self2, ...);
object* __less__bool(object* __func, object* self, object* self2, ...);

object* __create__range(object* __func);
object* __range(object* __func, object* self, object* start, object* stop, object* step, ...);
object* __next__range(object* __func, object* self, ...);


object* __is_sample (object* __func, object* num, ...);

#endif
