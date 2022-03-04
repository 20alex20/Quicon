#ifndef CONSTANTS_H
#define CONSTANTS_H


#define NULL 0
#define END 0
#define TRUE 1
#define FALSE 0
#define lenptr sizeof(object*)
#define StopIteration END

#define US_ASCII 0
#define WINDOWS_1251 1
#define UTF_8 2


#define start_func_0()\
	if (__flag)\
		return NULL;\
	__fl(); __start_func_0();
#define returnf_0(sth) __boofer2 = __enlon(sth); return __returnfm(__boofer2, __clear clear)
#define start_func(arr_index, ...)\
	static uint names[] = { __VA_ARGS__ };\
	if (__flag)\
		return names;\
	object** __nextarg = (object **)&__func + 1; __fl();\
	__finarg(__func->n, names, arr_index, __func->start, __nextarg)
#define returnf(sth) __boofer2 = __enlon(sth); return __returnfm(__boofer2, __dap(__nextarg, __func->n), __clear clear)
#define returnf2(sth) __boofer2 = __enlon(sth); return __returnfm(__boofer2, __dtp(self, self2), __clear clear)
#define do_func(func, pos, nam, ...) __pf(func, pos, nam)(__boofer, __VA_ARGS__)
#define start_method() __open_access(self, __class_name, __class)
#define do_method(sth, i, pos, nam, ...) __pm(sth, __##i##_var, pos, nam)(__boofer, __boofer2, __VA_ARGS__)

#define if_bool(sth) if (do_method(sth, to_bool, 0, 0)->flag)
#define not(self) create__bool(do_method(self, to_bool, 0, 0)->flag ^ 1)
#define and(self, self2) create__bool(do_method(self, to_bool, 0, 0)->flag && do_method(self2, to_bool, 0, 0)->flag)
#define or(self, self2) create__bool(do_method(self, to_bool, 0, 0)->flag || do_method(self2, to_bool, 0, 0)->flag)
#define is(self, self2) create__bool(self == self2)

#define fast_module(sth, func) __fm(sth, sth->flag, sth->flag = 0, func)  // !

#define __fl() __file = __FILE; __line = __LINE__
#define __fast_error(...) __error(__FILE, __LINE__, __VA_ARGS__)
#define __fast_dop(sth) __dop_and_do(self, sth)
#define __fast_dop_2(sth) __dop_and_do_2(self, self2, sth)

#define from(sth, i) (*__from2(sth, __##i##_var))  // !
#define from_this(i) ((struct __class*)(*__nextarg)->start)->i  // !
#define from_self(i) ((struct __class*)self->start)->i  // !
#define from_self_class(i) ((struct __class_name*)__class_name->start)->i
#define from_self2(i) ((struct __class2*)self2->start)->i  // !
#define from_self2_class(i) ((struct __class_name_2*)__class_name_2->start)->i  // !

#define var(name) __##name##_var
#define arg(name) __##name##_arg
#define create_var(name, len, ...) uint var(name)[] = {len, __VA_ARGS__}
#define named_arg(name, sth) arg(name), sth

#define empty_arg __empty_arg()
#define create__noth() create__noth
#define assign(sth, sth2) __asn(&sth, sth2)
#define type_arg_error(sth) __error(__FILE, __LINE__, __TYPE_ARG_ERROR, sth->name)  // !


typedef unsigned long long ull;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef uchar bool;


typedef enum {
	__ANOTHER_ERROR, __TYPE_METHOD_ERROR, __TYPE_ARG_ERROR, __NAME_ARG_ERROR_2, __NAME_ARG_ERROR, __NO_ARG_ERROR, __MANY_VALUES_ARG_ERROR, __NO_ELEMENT_ARRAY_ERROR, __TOO_MANY_NAMED_ARGS_ERROR, __TOO_MANY_ARGS_ERROR, __INDEX_ERROR, __LONG_INT_ERROR, __W1251_ERROR
} errors;

typedef enum {
	 NOTH, BOOL, CLASS_NAME, ARRAY, FUNC, INT, LIST, MY, RANGE, STRING, TYPE_ITERATOR
} class_name;

enum named_args {
	__ self2_arg, __after_arg, __arr_arg, __before_arg, __between_arg, __name_arg, __num_arg, __self2_arg, __self_arg, __start_arg, __start_str_arg, __step_arg, __sth_arg, __stop_arg, __str_arg
};

#endif
