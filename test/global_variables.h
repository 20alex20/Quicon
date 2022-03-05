bool __only_usascii, __flag; uint __line, __pos, __nam; char* __file;
extern uint* __to_another_type_arr[];

typedef struct {
	ushort name, nop, flag, n;  // number of pointers
	void* start;
	size_t len;
} object;

object* __boofer, * __boofer2, * create__noth, * __classes[12], * __variables;


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


extern uint var(multiply)[], var(subtractout)[], var(numsign)[], var(stop)[], var(my)[], var(reverse)[], var(next)[], var(change)[], var(to_string)[], var(equal)[], var(bin)[], var(to_bool)[], var(to_windows1251)[], var(step)[], var(current)[], var(to_func)[], var(module)[], var(tabi)[], var(rod)[], var(addout)[], var(to_range)[], var(pubi)[], var(more)[], var(slice)[], var(less)[], var(divide)[], var(to_utf8)[], var(to_array)[], var(to_int)[], var(to_type_iterator)[];

object* Noth, * Bool, * ClassName, * Array, * Func, * Int, * List, * Range, * String, * TypeIterator;
object* range, * print, * length, * copy, * type_of, * is_instance, * to_another_type, * end_program, * return_self, * input, * is_sample;
