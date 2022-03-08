#include "all.h"
#define __FILE start_program_c
char* start_program_c = "start_program.c";


object __const_noth = { NOTH, NULL, NULL, NULL, NULL, NULL };


void start_program() {
	SetConsoleOutputCP(65001);
	SetConsoleCP(1251);
	__flag = FALSE;
	create__noth = &__const_noth;
	return_self = __enlon(create__func(__return_self, FALSE, 1, NULL));

	Int = create__class_name(INT, "int", 0, 14, return_self,
		create__func(__to_bool__int, FALSE, 1, NULL), create__func(__to_string__int, FALSE, 1, NULL),
		create__func(__addout__int, FALSE, 2, NULL, NULL), create__func(__subtractout__int, FALSE, 2, NULL, NULL),
		create__func(__multiply__int, FALSE, 2, NULL, NULL), create__func(__divide__int, FALSE, 2, NULL, NULL),
		create__func(__rod__int, FALSE, 2, NULL, NULL), create__func(__equal__int, FALSE, 2, NULL, NULL),
		create__func(__more__int, FALSE, 2, NULL, NULL), create__func(__less__int, FALSE, 2, NULL, NULL),
		create__func(__module__int, FALSE, 2, NULL, NULL), create__func(__bin__int, FALSE, 1, NULL),
		create__func(__numsign__int, FALSE, 1, NULL));
	String = create__class_name(STRING, "string", 0, 13, return_self,
		create__func(__to_bool__string, FALSE, 1, NULL), create__func(__to_int__string, FALSE, 1, NULL),
		create__func(__to_array__string, FALSE, 1, NULL), create__func(__tabi__string, FALSE, 2, NULL, NULL),
		create__func(__slice__string, FALSE, 4, NULL, create__int(FALSE, 0), NULL, create__int(FALSE, 1)),
		create__func(__addout__string, FALSE, 2, NULL, NULL), create__func(__equal__string, FALSE, 2, NULL, NULL),
		create__func(__more__string, FALSE, 2, NULL, NULL), create__func(__less__string, FALSE, 2, NULL, NULL),
		create__func(__reverse__string, FALSE, 1, NULL), create__func(__to_utf8__string, FALSE, 1, NULL),
		create__func(__to_windows1251__string, FALSE, 1, NULL));
	Bool = create__class_name(BOOL, "bool", 0, 6, return_self,
		create__func(__to_int__bool, FALSE, 1, NULL), create__func(__to_string__bool, FALSE, 1, NULL),
		create__func(__equal__bool, FALSE, 2, NULL, NULL), create__func(__more__bool, FALSE, 2, NULL, NULL),
		create__func(__less__bool, FALSE, 2, NULL, NULL));
	Noth = create__class_name(NOTH, "noth", NULL, NULL);
	ClassName = create__class_name(CLASS_NAME, "class_name", 0, 2, return_self,
		create__func(__equal__class_name, FALSE, 2, NULL, NULL));
	Func = create__class_name(FUNC, "func", 0, 2, return_self,
		create__func(__change__func, FALSE, 2, NULL, NULL));
	Array = create__class_name(ARRAY, "array", 0, 7, return_self,
		create__func(__to_bool__string, FALSE, 1, NULL), create__func(__to_string__array, FALSE, 1, NULL),
		create__func(__reverse__array, FALSE, 1, NULL), create__func(__tabi__array, FALSE, 2, NULL, NULL),
		create__func(__pubi__array, FALSE, 2, NULL, NULL), create__func(__slice__array, FALSE, 4, NULL, create__int(FALSE, 0), NULL, create__int(FALSE, 1)));
	TypeIterator = create__class_name(TYPE_ITERATOR, "type_iterator", 0, 2, return_self, create__func(__next__type_iterator, FALSE, 1, NULL));
	Range = create__class_name(RANGE, "range", 4, 2, return_self, create__func(__next__range, FALSE, 1, NULL));

	range = __enlon(create__func(__range, TRUE, 4, create__func(__create__range, TRUE, 0), create__int(FALSE, 0), NULL, create__int(FALSE, 1)));
	print = __enlon(create__func(__print, FALSE, 4, create__array(0), create__string("", US_ASCII), create__string(" ", US_ASCII), create__string("\n", US_ASCII)));
	length = __enlon(create__func(__length, FALSE, 1, NULL));
	copy = __enlon(create__func(__copy, FALSE, 1, NULL));
	type_of = __enlon(create__func(__type_of, FALSE, 1, NULL));
	is_instance = __enlon(create__func(__is_instance, FALSE, 2, NULL, NULL));
	to_another_type = __enlon(create__func(__to_another_type, FALSE, 2, NULL, NULL));
	end_program = __enlon(create__func(__end_program, FALSE, 0));
	input = __enlon(create__func(__input, FALSE, 1, create__string("", US_ASCII)));

	Date_time = __enlon(create__class_name(DATE_TIME, "Date_time", 6, 5, create__array(12, create__int(FALSE, 31),  create__int(FALSE, 28),  create__int(FALSE, 31),  create__int(FALSE, 30),  create__int(FALSE, 31),  create__int(FALSE, 30),  create__int(FALSE, 31),  create__int(FALSE, 31),  create__int(FALSE, 30),  create__int(FALSE, 31),  create__int(FALSE, 30),  create__int(FALSE, 31)), create__func(__today__date_time, FALSE, 1,NULL), create__func(__now__date_time, FALSE, 1,NULL), create__func(__to_string__date_time, FALSE, 1,NULL), create__func(__addout__date_time, FALSE, 2, NULL, NULL)));
	Dt_delta = __enlon(create__class_name(DT_DELTA, "Dt_delta", 1, 1, create__func(__addout__dt_delta, FALSE, 2, NULL, NULL)));


	is_leap = __enlon(create__func(__is_leap, FALSE, 2,NULL, NULL));
	add_0 = __enlon(create__func(__add_0, FALSE, 1,NULL));
	date_time = __enlon(create__func(__date_time, FALSE, 7,create__func(__create__date_time, TRUE, 0), create__int(FALSE, 1970), create__int(FALSE, 1), create__int(FALSE, 1), create__int(FALSE, 0), create__int(FALSE, 0), create__int(FALSE, 0)));
	dt_delta = __enlon(create__func(__dt_delta, FALSE, 5,create__func(__create__dt_delta, TRUE, 0), create__int(FALSE, 0), create__int(FALSE, 0), create__int(FALSE, 0), create__int(FALSE, 0)));
}


create_var(addout, 4, DATE_TIME, 5 << 16, DT_DELTA, 1 << 16, INT, 4 << 16, STRING, 7 << 16);
create_var(bin, 1, INT, 13 << 16);
create_var(change, 1, FUNC, 2 << 16);
create_var(current, 1, RANGE, 1);
create_var(divide, 1, INT, 7 << 16);
create_var(equal, 3, BOOL, 4 << 16, INT, 9 << 16, STRING, 8 << 16);
create_var(less, 3, BOOL, 6 << 16, INT, 11 << 16, STRING, 10 << 16);
create_var(module, 1, INT, 12 << 16);
create_var(more, 3, BOOL, 5 << 16, INT, 10 << 16, STRING, 9 << 16);
create_var(multiply, 1, INT, 6 << 16);
create_var(next, 2, RANGE, 2 << 16, TYPE_ITERATOR, 2 << 16);
create_var(numsign, 1, INT, 14 << 16);
create_var(pubi, 1, ARRAY, 6 << 16);
create_var(reverse, 2, ARRAY, 4 << 16, STRING, 11 << 16);
create_var(rod, 1, INT, 8 << 16);
create_var(slice, 2, ARRAY, 7 << 16, STRING, 6 << 16);
create_var(step, 1, RANGE, 2);
create_var(stop, 1, RANGE, 3);
create_var(subtractout, 1, INT, 5 << 16);
create_var(tabi, 2, ARRAY, 5 << 16, STRING, 5 << 16);
create_var(to_array, 2, ARRAY, 1 << 16, STRING, 4 << 16);
create_var(to_bool, 4, BOOL, 1 << 16, ARRAY, 2 << 16, INT, 2 << 16, STRING, 2 << 16);
create_var(to_func, 1, FUNC, 1 << 16);
create_var(to_int, 3, BOOL, 2 << 16, INT, 1 << 16, STRING, 3 << 16);
create_var(to_range, 1, RANGE, 1 << 16);
create_var(to_string, 5, BOOL, 3 << 16, ARRAY, 3 << 16, DATE_TIME, 4 << 16, INT, 3 << 16, STRING, 1 << 16);
create_var(to_type_iterator, 1, TYPE_ITERATOR, 1 << 16);
create_var(to_utf8, 1, STRING, 12 << 16);
create_var(to_windows1251, 1, STRING, 13 << 16);
create_var(arr_days, 1, DATE_TIME, 1 << 16);
create_var(today, 1, DATE_TIME, 2 << 16);
create_var(now, 1, DATE_TIME, 3 << 16);
create_var(second, 1, DATE_TIME, 1);
create_var(minute, 1, DATE_TIME, 2);
create_var(hour, 1, DATE_TIME, 3);
create_var(day, 1, DATE_TIME, 4);
create_var(month, 1, DATE_TIME, 5);
create_var(year, 1, DATE_TIME, 6);
create_var(seconds, 1, DT_DELTA, 1);

uint * __to_another_type_arr[] = {NULL, var(to_bool), NULL, var(to_array), NULL, NULL, var(to_func), var(to_int), NULL, var(to_range), var(to_string), var(to_type_iterator)};
