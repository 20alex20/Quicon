bool __only_usascii, __flag; uint __line, __pos, __nam; char* __file;
extern uint* __to_another_type_arr[];

typedef struct {
	ushort name, nop, flag, n;  // number of pointers
	void* start;
	size_t len;
} object;

object* __boofer, * __boofer2, * create__noth, * __classes[13], * __variables;


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

struct My {
	object* k, * next, * addout;
};
struct MY {
	object* er;
};


extern uint var(to_int)[], var(rod)[], var(module)[], var(er)[], var(k)[], var(addout)[], var(equal)[], var(to_bool)[], var(more)[], var(to_type_iterator)[], var(reverse)[], var(bin)[], var(slice)[], var(current)[], var(tabi)[], var(to_func)[], var(stop)[], var(subtractout)[], var(to_range)[], var(multiply)[], var(change)[], var(step)[], var(to_string)[], var(to_array)[], var(to_utf8)[], var(less)[], var(to_windows1251)[], var(my)[], var(pubi)[], var(next)[], var(numsign)[], var(divide)[];

object* Noth, * Bool, * ClassName, * Array, * Func, * Int, * List, * My, * Range, * String, * TypeIterator;
object* range, * print, * length, * copy, * type_of, * is_instance, * to_another_type, * end_program, * return_self, * input, * my, * my;
