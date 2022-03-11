#include "all.h"
#define __FILE to_ctype_c
char* to_ctype_c = "to_ctype.c";


ull to_ctype(object* sth, uchar len, bool flag) {
	__enlon(sth);
	if (sth->name != INT)
		__fast_error(__TYPE_ARG_ERROR, sth->name);
	size_t sth_len = sth->len;
	if (sth_len > len)
		__fast_error(__LONG_INT_ERROR, len);
	ull ans = 0;
	char* ansch = &ans, * st = sth->start;
	for (char i = 0; i < sth_len; i++)
		ansch[i] = st[i];
	if (sth->flag) {
		if (!flag)
			__fast_error(__ANOTHER_ERROR, "An attempt was made to assign a negative value to an unsigned type");
		if (ansch[len - 1] >> 7)
			__fast_error(__LONG_INT_ERROR, len);
		ans = ~ans + 1;
	}
	__dop(sth);
	return ans;
}

size_t to_c_size_t(object* sth) {
	return to_ctype(sth, lenptr, FALSE);
}

int to_c_int(object* sth) {
	return to_ctype(sth, 4, TRUE);
}

uint to_c_uint(object* sth) {
	return to_ctype(sth, 4, FALSE);
}

long long to_c_long_long(object* sth) {
	return to_ctype(sth, 8, TRUE);
}

ull to_ull(object* sth) {
	return to_ctype(sth, 8, FALSE);
}