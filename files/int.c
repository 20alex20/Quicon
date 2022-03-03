#include "all.h"
#define __FILE int_c
char* int_c = "int.c";


object* create__int(bool flag, intptr_t decnum) {
	object* self = (object*)calloc(1, sizeof(object));
	self->name = INT;
	size_t lennum = 0, j = 0;
	if (flag) {
		char* cnum = decnum;
		while (*cnum == '0')
			cnum++;
		if (*cnum == END) {
			self->start = calloc(1, 1);
			self->len = 1;
			return self;
		}
		if (*cnum == '-') {
			self->flag = 1;
			cnum++;
		}
		__decnot_to_binnot(TRUE, TRUE, cnum);
		lennum = __strlen(cnum);
		lennum = (lennum / 3 + (lennum % 3 != 0)) * 10;
		lennum = lennum / 8 + (lennum % 8 != 0);
	}
	else {
		int inum = decnum;
		if (inum == 0) {
			self->start = calloc(1, 1);
			self->len = 1;
			return self;
		}
		self->flag = ((uint)inum) >> 31;
		if (inum >> 31) {
			inum = ~(inum - 1);
		}
		__decnot_to_binnot(TRUE, FALSE, inum);
		for (uchar i = 1; i <= 4; i++)
			if (inum >> (8 * i) == 0) {
				lennum = i;
				break;
			}
	}
	uchar* num = (uchar*)calloc(lennum, 1);
	self->start = num;
	uchar bit;
	while (TRUE) {
		for (uchar i = 0; i < 8; i++) {
			bit = __decnot_to_binnot(FALSE);
			// printf("%c", bit);
			if (bit == END)
				break;
			*num |= (bit - '0') << i;
			j++;
		}
		if (bit == END)
			break;
		num++;
	}
	self->len = j / 8 + (j % 8 != 0);
	// printf("\n");
	return self;
}



object* __to_string__int(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	if (self->len == 1 && *((uchar*)self->start) == 0) {
		__dop(self);
		return create__string("0", US_ASCII);
	}
	char* summa = "0", * factor = "1";
	object* iterator = NULL, * bit = NULL;
	assign(iterator, create__type_iterator(self));
	while (assign(bit, do_method(iterator, next, 0, 0))) {
		if (bit->flag)
			summa = __decimal_addition(summa, factor, '0');
		factor = __decimal_addition(factor, factor, '1');
	}
	__dop(iterator);
	// __dop(bit);
	object* modnum = do_method(create__string(NULL, summa, US_ASCII, __strlen(summa)), reverse, 0, 0);  // module number
	if (self->flag)
		return do_method(create__string("-", US_ASCII), addout, 1, 0, modnum);
	__dop(self);
	return modnum;
}


object* __to_bool__int(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	return __fast_dop(create__bool(self->len != 1 || *((uchar*)self->start) != 0));
}



object* __subtractout_int__int(object* self, object* self2);

object* __addout_int__int(object* self, object* self2) {
	if (self->flag != self2->flag) {
		self2->flag ^= 1;
		object* obj = __subtractout_int__int(__enlon(self), __enlon(self2));
		self2->flag ^= 1;
		__dtp(self, self2);
		return obj;
	}
	object* obj = (object*)malloc(sizeof(object));
	obj->name = INT;
	obj->nop = 0;
	obj->flag = self->flag;
	size_t len1 = self->len, len2 = self2->len, max_len = max(len1, len2), i = 0;
	uchar* num = (uchar*)malloc(max_len + 1), * num1 = self->start, * num2 = self2->start;
	ushort summa;
	uchar remainder = 0;
	while (i < max_len) {
		summa = (i < len1 ? num1[i] : 0) + (i < len2 ? num2[i] : 0) + remainder;
		num[i] = summa;
		remainder = summa >> 8;
		i++;
	}
	num[i] = remainder;
	if (remainder)
		i++;
	obj->len = i;
	obj->start = num;
	__dtp(self, self2);
	return obj;
}

object* __addout__int(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { INT };
	static object* (*functions[]) (object * self, object * self2) = { __addout_int__int };
	return __create_distribution(self, self2, class_names, functions, __addout_int__int);
}


object* __subtractout_int__int(object* self, object* self2) {
	if (self->flag != self2->flag) {
		self2->flag ^= 1;
		object* obj = __addout_int__int(__enlon(self), __enlon(self2));
		self2->flag ^= 1;
		__dtp(self, self2);
		return obj;
	}
	if (do_method(self, equal, 1, 0, self2)->flag)
		return __fast_dop_2(create__int(FALSE, 0));
	object* obj = (object*)malloc(sizeof(object));
	obj->name = INT;
	obj->nop = 0;
	size_t len1, len2, i = 0;
	uchar* num1, * num2, * num;
	bool znak = self->flag;
	self->flag = 0; self2->flag = 0;
	if (do_method(self, more, 1, 0, self2)->flag) {
		len1 = self->len, len2 = self2->len;
		num1 = self->start, num2 = self2->start;
		obj->flag = znak;
	}
	else {
		len1 = self2->len, len2 = self->len;
		num1 = self2->start, num2 = self->start;
		obj->flag = znak ^ 1;
	}
	self->flag = znak; self2->flag = znak;
	num = (uchar*)malloc(len1);
	ushort difference;
	uchar remainder = 0;
	while (i < len1) {
		difference = 256 + num1[i] - (i < len2 ? num2[i] : 0) - remainder;
		num[i] = difference;
		remainder = difference >> 8 == 0;
		i++;
	}
	while (!num[i - 1])
		i--;
	obj->len = i;
	obj->start = num;
	__dtp(self, self2);
	return obj;
}

object* __subtractout__int(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { INT };
	static object* (*functions[]) (object * self, object * self2) = { __subtractout_int__int };
	return __create_distribution(self, self2, class_names, functions, __subtractout_int__int);
}


object* __multiply_int__int(object* self, object* self2) {
	object* obj = (object*)malloc(sizeof(object)), * iterator = NULL, * bit = NULL;
	obj->name = INT;
	obj->nop = 0;
	size_t len1 = self->len, len = len1 + self2->len, i = 0, k = 0, ik;
	uchar* num = (uchar*)calloc(len, 1), * num1 = self->start;
	ushort summa;
	uchar remainder, j = 0, boofer;
	assign(iterator, create__type_iterator(self2));
	while (assign(bit, do_method(iterator, next, 0, 0))) {
		if (bit->flag) {
			remainder = 0; i = k;
			while (i < len) {
				ik = i - k;
				if (ik == 0)
					boofer = num1[ik] << j;
				else if (ik < len1)
					boofer = num1[ik] << j | num1[ik - 1] >> (8 - j);
				else if (ik == len1)
					boofer = num1[ik - 1] >> (8 - j);
				else
					boofer = 0;
				summa = num[i] + boofer + remainder;
				num[i] = summa;
				remainder = summa >> 8;
				i++;
			}
		}
		j++;
		if (j == 8) {
			k++;
			j = 0;
		}
	}
	if (!num[len - 1])
		len--;
	obj->flag = self->flag != self2->flag;
	obj->len = len;
	obj->start = num;
	__dop(iterator);
	__dtp(self, self2);
	return obj;
}

object* __multiply__int(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { INT };
	static object* (*functions[]) (object * self, object * self2) = { __multiply_int__int };
	return __create_distribution(self, self2, class_names, functions, __multiply_int__int);
}


object* __less_int__int(object* self, object* self2);

#define clear (0)
object* __divide_int__int(object* self, object* self2) {  // remainder of devision
	if (self2->len == 1 && *((uchar*)self2->start) == 0)
		__fast_error(__ANOTHER_ERROR, "An attempt was made to divide by zero");
	if (__less_int__int(__enlon(self), __enlon(self2))->flag) {
		returnf2(create__int(FALSE, 0));
	}
	object* obj = (object*)malloc(sizeof(object)), * iterator = NULL, * bit = NULL;
	obj->name = INT;
	obj->nop = 0;
	obj->flag = 0;
	self = assign(self, do_func(copy, 1, 0, self));
	self->flag = 0;
	size_t len1 = self->len, len2 = self2->len, len = 0, i, k = 1, ik;
	uchar* num = calloc(len1 - len2 + 1, 1), * num1 = self->start, * num2 = self2->start;
	ushort difference, summa;
	uchar remainder, boofer, shift = 1, lenbit1, lenbit2 = __lenbit(num2[len2 - 1]);
	lenbit1 = __lenbit(num1[len1 - 1]);
	while (len1 > len2 || (len1 == len2 && lenbit1 > lenbit2)) {
		if (lenbit1 > lenbit2) {
			shift = lenbit1 - lenbit2 - 1;
			k = len1 - len2;
		}
		else {
			shift = lenbit1 + 7 - lenbit2;
			k = len1 - len2 - 1;
		}
		remainder = 0; i = k;
		do {
			summa = num[i] + (i == k ? 1 << shift : 0) + remainder;
			num[i] = summa;
			remainder = summa >> 8;
			i++;
		} while (remainder == 1);
		if (i > len)
			len = i;
		remainder = 0; i = k;
		while (i < len1) {
			ik = i - k;
			if (ik == 0)
				boofer = num2[ik] << shift;
			else if (ik < len2)
				boofer = num2[ik] << shift | num2[ik - 1] >> (8 - shift);
			else if (ik == len2)
				boofer = num2[ik - 1] >> (8 - shift);
			else
				boofer = 0;
			difference = 256 + num1[i] - boofer - remainder;
			num1[i] = difference;
			remainder = difference >> 8 == 0;
			i++;
		}
		if (!num1[i - 1])
			i--;
		len1 = i;
		lenbit1 = __lenbit(num1[len1 - 1]);
	}
	self->len = len1;
	if (__less_int__int(__enlon(self), __enlon(self2))->flag ^ 1) {
		remainder = 1; i = 0;
		do {
			summa = num[i] + remainder;
			num[i] = summa;
			remainder = summa >> 8;
			i++;
		} while (remainder == 1);
		if (i > len)
			len = i;
	}
	obj->len = len;
	obj->start = num;
	returnf2(obj);
}

object* __divide__int(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { INT };
	static object* (*functions[]) (object * self, object * self2) = { __divide_int__int };
	return __create_distribution(self, self2, class_names, functions, __divide_int__int);
}


#define clear (0)
object* __rod_int__int(object* self, object* self2) {  // remainder of devision
	if (self2->len == 1 && *((uchar*)self2->start) == 0)
		__fast_error(__ANOTHER_ERROR, "An attempt was made to divide by zero");
	if (__less_int__int(__enlon(self), __enlon(self2))->flag) {
		returnf2(self);
	}
	self = assign(self, do_func(copy, 1, 0, self));
	self->flag = 0;
	size_t len = self->len, len2 = self2->len, i, k = 1, ik;
	uchar* num = self->start, * num2 = self2->start;
	ushort difference;
	uchar remainder, boofer, shift = 1, lenbit = __lenbit(num[len - 1]), lenbit2 = __lenbit(num2[len2 - 1]);
	while (len > len2 || (len == len2 && lenbit > lenbit2)) {
		if (lenbit > lenbit2) {
			shift = lenbit - lenbit2 - 1;
			k = len - len2;
		}
		else {
			shift = lenbit + 7 - lenbit2;
			k = len - len2 - 1;
		}
		remainder = 0; i = k;
		while (i < len) {
			ik = i - k;
			if (ik == 0)
				boofer = num2[ik] << shift;
			else if (ik < len2)
				boofer = num2[ik] << shift | num2[ik - 1] >> (8 - shift);
			else if (ik == len2)
				boofer = num2[ik - 1] >> (8 - shift);
			else
				boofer = 0;
			difference = 256 + num[i] - boofer - remainder;
			num[i] = difference;
			remainder = difference >> 8 == 0;
			i++;
		}
		if (!num[i - 1])
			i--;
		len = i;
		lenbit = __lenbit(num[len - 1]);
	}
	self->len = len;
	if (__less_int__int(__enlon(self), __enlon(self2))->flag ^ 1)
		return __subtractout_int__int(self, self2);
	self->start = realloc(num, len);
	__dop(self2);
	return __returnfm(self);
}

object* __rod__int(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { INT };
	static object* (*functions[]) (object * self, object * self2) = { __rod_int__int };
	return __create_distribution(self, self2, class_names, functions, __rod_int__int);
}



object* __equal_int__int(object* self, object* self2) {
	size_t len = self->len;
	if (len != self2->len || self->flag != self2->flag) {
		__dtp(self, self2);
		return create__bool(FALSE);
	}
	uchar* num1 = self->start, * num2 = self2->start;
	for (size_t i = 0; i < len; i++) {
		if (num1[i] != num2[i]) {
			__dtp(self, self2);
			return create__bool(FALSE);
		}
	}
	__dtp(self, self2);
	return create__bool(TRUE);
}

object* __equal__int(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { INT };
	static object* (*functions[]) (object * self, object * self2) = { __equal_int__int };
	return __create_distribution(self, self2, class_names, functions, __equal_int__int);
}


object* __less_int__int(object* self, object* self2);

object* __more_int__int(object* self, object* self2) {
	if (self->flag != self2->flag)
		return __fast_dop_2(create__bool(self2->flag));
	if (self->flag == 1 && self2->flag == 1) {
		self->flag = 0; self2->flag = 0;
		object* ans = __less_int__int(__enlon(self), __enlon(self2));
		self->flag = 1; self2->flag = 1;
		__dtp(self, self2);
		return ans;
	}
	if (self->len != self2->len)
		return __fast_dop_2(create__bool(self->len > self2->len));
	size_t i = self->len;
	uchar* num1 = self->start, * num2 = self2->start;
	while (i > 0) {
		i--;
		if (num1[i] != num2[i])
			return __fast_dop_2(create__bool((num1[i] > num2[i]) ^ self->flag));
	}
	__dtp(self, self2);
	return create__bool(FALSE);
}

object* __more__int(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { INT };
	static object* (*functions[]) (object * self, object * self2) = { __more_int__int };
	return __create_distribution(self, self2, class_names, functions, __more_int__int);
}


object* __less_int__int(object* self, object* self2) {
	if (self->flag != self2->flag)
		return __fast_dop_2(create__bool(self->flag));
	if (self->flag == 1 && self2->flag == 1) {
		self->flag = 0; self2->flag = 0;
		object* ans = __more_int__int(__enlon(self), __enlon(self2));
		self->flag = 1; self2->flag = 1;
		__dtp(self, self2);
		return ans;
	}
	if (self->len != self2->len)
		return create__bool(self->len < self2->len);
	size_t i = self->len;
	uchar* num1 = self->start, * num2 = self2->start;
	while (i > 0) {
		i--;
		if (num1[i] != num2[i])
			return __fast_dop_2(create__bool((num1[i] < num2[i]) ^ self->flag));
	}
	__dtp(self, self2);
	return create__bool(FALSE);
}

object* __less__int(object* __func, object* self, object* self2, ...) {
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = { INT };
	static object* (*functions[]) (object * self, object * self2) = { __less_int__int };
	return __create_distribution(self, self2, class_names, functions, __less_int__int);
}



#define clear (0)
object* __module__int(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	ushort old = self->flag;
	self->flag = 0;
	object* sth_new = do_func(copy, 1, 0, self);
	self->flag = old;
	__dop(self);
	return sth_new;
}


#define clear (2, iterator, bit)
object* __bin__int(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	object* iterator = NULL, * bit = NULL;
	size_t i = self->len - 1, len;
	len = i = i * 8 + __lenbit(((uchar*)self->start)[i]);
	char* string = (char*)malloc(i + 1);
	string[i--] = END;
	assign(iterator, create__type_iterator(self));
	while (assign(bit, do_method(iterator, next, 0, 0)))
		string[i--] = bit->flag + '0';
	returnf(create__string(NULL, string, US_ASCII, len));
}


#define clear (0)
object* __numsign__int(object* __func, object* self, ...) {
	start_func(NULL, arg(self), 1);
	return __dop_and_do(self, create__bool(self->flag));
}