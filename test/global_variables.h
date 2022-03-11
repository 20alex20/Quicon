bool __only_usascii, __flag; uint __line, __pos, __nam; char* __file;
extern uint* __to_another_type_arr[];

typedef struct {
	ushort name, nop, flag, n;  // number of pointers
	void* start;
	size_t len;
} object;

object* __boofer, * __boofer2, * create__noth, * __classes[14], * __variables;


struct Int {
	object* to_int, * to_bool, * addout, * subtractout;
};

struct String {
	object* to_string, * to_bool, * to_int, * to_array, * reverse, * tabi, * slice, * addout;
};

struct Bool {
	object* to_bool, * to_int, * to_string;
};

struct Func {
	object* to_func, * change;
};

struct Array {
	object* to_array, * to_bool, * to_string, * reverse, * tabi, * pubi, * slice;
};

struct TypeIterator {
	object* to_type_iterator, * next;
};

struct Range {
	object* to_range, * my, * next;
};
struct RANGE {
	object* current, * step, * stop, * numsign;
};

struct Date_time {
	object* arr_days, * today, * now, * to_string, * addout;
};
struct DATE_TIME {
	object* second, * minute, * hour, * day, * month, * year;
};

struct Dt_delta {
	object* addout;
};
struct DT_DELTA {
	object* seconds;
};


extern uint var(next)[], var(reverse)[], var(to_int)[], var(to_range)[], var(my)[], var(to_bool)[], var(divide)[], var(year)[], var(addout)[], var(step)[], var(bin)[], var(to_type_iterator)[], var(change)[], var(more)[], var(today)[], var(now)[], var(to_utf8)[], var(stop)[], var(second)[], var(current)[], var(month)[], var(to_string)[], var(multiply)[], var(arr_days)[], var(seconds)[], var(minute)[], var(to_func)[], var(to_windows1251)[], var(day)[], var(subtractout)[], var(hour)[], var(slice)[], var(pubi)[], var(tabi)[], var(to_array)[], var(module)[], var(less)[], var(numsign)[], var(equal)[], var(rod)[];

object* Noth, * Bool, * ClassName, * Array, * Date_time, * Dt_delta, * Func, * Int, * List, * Range, * String, * TypeIterator;
object* range, * print, * length, * copy, * type_of, * is_instance, * to_another_type, * end_program, * return_self, * input, * Int, * String, * Bool, * Noth, * ClassName, * Func, * Array, * TypeIterator, * Range, * is_leap, * add_0, * date_time, * date_time, * Date_time, * dt_delta, * dt_delta, * Dt_delta;
