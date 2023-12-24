#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct big_int{
	unsigned char *digits;
	int size;
	unsigned char sign;
} big_int;

big_int *big_int_create(char *line) {
	big_int *number = (big_int*)malloc(sizeof(big_int));
	int length = strlen(line);
	number->size = (length >> 3) + ((length & 7) != 0);
	number->digits = (unsigned char*)malloc(number->size);
	if (line[0] == '-') {
		number->sign = 1;
		line[0] = '0';
	}
	else number->sign = 0;
	int k = 0;
	for (int i = length - 1; i >= 0; i -= 8, ++k) {
			int q = 0, j = i - 7;
			if (j < 0) j = 0;
			for (; j <= i; j++) {
				q <<= 1;
				q += (line[j] - '0');
			}
			number->digits[k] = q;
		}
	return number;
}

void big_int_free(big_int *number) {
	free(number->digits);
	free(number);
}

int big_int_assign(big_int *new_number_1, big_int *number_1) {
	new_number_1-> sign = number_1->sign;
	new_number_1->size = number_1->size;
	free(new_number_1->digits);
	new_number_1->digits = (unsigned char*)malloc(new_number_1->size);
	memcpy(new_number_1->digits, number_1->digits, number_1->size);
	return EXIT_SUCCESS;
}

void big_int_print(big_int *number) {
	if (number->sign == 1) printf("-");
	for (int i = number->size - 1; i >= 0; i--) {
		for(unsigned char digit = 0x80; digit; digit >>=1)
			printf("%d", (((number->digits[i]) & digit) != 0));
		printf(" ");
	}
	printf("\n");
}

// number_1 <= number_2
int big_int_comparison(big_int *number_1, big_int *number_2) {
	if (number_1->size > number_2->size) return 1;
	else if (number_1->size < number_2->size) return 0;
	else {
		int i = number_1->size - 1;
		while(number_1->digits[i] == number_2->digits[i]) {
			i--;
			if (i) break;
		}
		if (i == 0 || (number_1->digits[i] > number_2->digits[i])) return 1;
		else return 0;
	}
}

void swap(big_int *number_1, big_int *number_2) {
	big_int flag;
	flag = *number_1;
	*number_1 = *number_2;
	*number_2 = flag;
}

int big_int_sum(big_int *number_1, big_int *number_2) {
	if(number_2->size > number_1->size) {
		number_1->digits = realloc(number_1->digits, number_2->size); 
		memset((number_1->digits)+number_1->size, 0, number_2->size - number_1->size);
		number_1->size = number_2->size;
	}
	unsigned char carry = 0; 
	for (int i = 0; i < number_1->size; i++) {
		unsigned char digit_2 = (i < number_2->size) ? number_2->digits[i] : 0;
		int sum = number_1->digits[i] + digit_2 + carry;
		number_1->digits[i] = sum;
		carry = sum >>= 8;
	}
	if(carry) {
		number_1->digits = realloc(number_1->digits, ++number_1->size);
		number_1->digits[number_1->size - 1] = carry;
	}
	return 0;
}

int big_int_subtract(big_int *number_1, big_int *number_2) {
	unsigned char borrow = 0; 	
	for (int i = number_1->size; i >= 0; i--) {
			int digit_1 = (number_1->size - i < number_1->size) ? number_1->digits[number_1->size - i] : 0;
			int digit_2 = (number_1->size - i < number_2->size) ? number_2->digits[number_1->size - i] : 0;
			int sub = digit_1 - digit_2 - borrow;
			number_1->digits[number_1->size - i] = sub;
			borrow = (sub < 0) ? 1 : 0;
		}
	int i = 1;
	while (number_1->digits[number_1->size - i] == 0 && number_1->size - i != 0) number_1->size--;
	number_1->digits = realloc(number_1->digits, number_1->size);
	return EXIT_SUCCESS;
}

int big_int_sign_sum(big_int *number_1, big_int *number_2) {
	if (big_int_comparison(number_1, number_2) == 0) {
		swap(number_1, number_2);
	}
	
	if (number_1->sign != number_2->sign) big_int_subtract(number_1, number_2);
	else big_int_sum(number_1, number_2);
	return EXIT_SUCCESS;
}

int big_int_sign_sub(big_int *number_1, big_int *number_2) {
	if (big_int_comparison(number_1, number_2) == 0) {
		swap(number_1, number_2);
	}
	if (number_1->sign != number_2->sign) big_int_sum(number_1, number_2);
	else big_int_subtract(number_1, number_2);
	return EXIT_SUCCESS;
}

big_int *big_int_simple_multiplication(big_int *number_1, big_int *number_2) {
	int flag = 0;
	if (big_int_comparison(number_1, number_2) == 0) {
		swap(number_1, number_2);
		flag++;
	}
	big_int *result = (big_int*)malloc(sizeof(big_int));
	result->size = number_1->size;
	result->digits = (unsigned char*)malloc(result->size); 
	result->sign = (number_1->sign == number_2->sign) ? 0 : 1;
	for (int i = number_2->size - 1; i >= 0; i--) {
		int carry = 0;
		int k = 0;
		for (int j = 0; j < number_1->size; j++) {
			int multiplication = number_1->digits[j] * number_2->digits[i] + carry + result->digits[k];
			carry = multiplication >> 8;
			result->digits[k] = multiplication;
			k++;
		}
		if (carry) {
			if (k != result->size - 1) result->digits = realloc(result->digits, result->size++);
			result->digits[k] += carry;
		}
		if (i) {
			result->digits = realloc(result->digits, result->size++);
			for (int m = result->size - 1; m > 0; m--) {
				result->digits[m] = result->digits[m - 1];
			}
			result->digits[0] = 0;
		}
	}
	if (flag) swap(number_1, number_2);
	return result;
}

big_int *big_int_karatsuba_multiplication(big_int *number_1, big_int *number_2) {
	int flag = 0;
	if (big_int_comparison(number_1, number_2) == 0) {
		swap(number_1, number_2);
		flag++;
	}
	big_int *result = (big_int*)malloc(sizeof(big_int));
	result->size = number_1->size + number_2->size;
	result->digits = (unsigned char*)malloc(result->size); 
	result->sign = (number_1->sign == number_2->sign) ? 0 : 1;
	
	if (number_1->size == 1) result = big_int_simple_multiplication(number_1, number_2);
	else {
		big_int *number_1_part_1 = (big_int*)malloc(sizeof(big_int));
		number_1_part_1->size = (number_1->size + 1) / 2;
		number_1_part_1->digits = (unsigned char*)malloc(number_1_part_1->size); 
		number_1_part_1->digits = number_1->digits;
		big_int *number_1_part_2 = (big_int*)malloc(sizeof(big_int));
		number_1_part_2->size = number_1->size / 2;
		number_1_part_2->digits = (unsigned char*)malloc(number_1_part_1->size); 
		number_1_part_2->digits = number_1->digits + number_1_part_1->size; 
		
		big_int *number_2_part_1 = (big_int*)malloc(sizeof(big_int));
		number_2_part_1->size = (number_2->size + 1) / 2;
		number_2_part_1->digits = (unsigned char*)malloc(number_2_part_1->size); 
		number_2_part_1->digits = number_2->digits;
		big_int *number_2_part_2 = (big_int*)malloc(sizeof(big_int));
		number_2_part_2->size = number_2->size / 2;
		number_2_part_2->digits = (unsigned char*)malloc(number_2_part_2->size); 
		number_2_part_2->digits = number_2->digits + number_2_part_2->size; 
		
		big_int *sum_number_1;
		sum_number_1 = (big_int*)malloc(sizeof(big_int));
		big_int_assign(sum_number_1, number_1_part_1);
		big_int_sum(sum_number_1, number_1_part_2);
		
		big_int *sum_number_2;
		sum_number_2 = (big_int*)malloc(sizeof(big_int));
		big_int_assign(sum_number_2, number_2_part_1);
		big_int_sum(sum_number_2, number_2_part_2);
		
		big_int *product_sum = big_int_karatsuba_multiplication(sum_number_1, sum_number_2);
		big_int *product_part_1 = big_int_karatsuba_multiplication(number_1_part_1, number_2_part_1);
		big_int *product_part_2 = big_int_karatsuba_multiplication(number_1_part_2, number_2_part_2);
		
		big_int *subtract;
		subtract = (big_int*)malloc(sizeof(big_int));
		big_int_assign(subtract, product_sum);
		big_int_subtract(subtract, product_part_1);
		big_int_subtract(subtract, product_part_2);
		
		memcpy(result->digits, product_part_1->digits, product_part_1->size);
		memcpy(result->digits + product_part_1->size, product_part_2->digits, product_part_2->size);
		for (int i = 0; i < subtract->size; i++) {
			result->digits[number_1_part_1->size + i] += subtract->digits[i];
		}
		big_int_free(subtract);
		big_int_free(sum_number_1);
		big_int_free(sum_number_2);
		big_int_free(product_sum);
		big_int_free(product_part_1);
		big_int_free(product_part_2);
		big_int_free(number_1_part_1);
		//big_int_free(number_1_part_2);
		big_int_free(number_2_part_1);
		//big_int_free(number_2_part_2);

	}
	int i = 1;
	while (result->digits[result->size - i] == 0 && result->size - i != 0) result->size--;
	result->digits = realloc(result->digits, result->size);
	if (flag) swap(number_1, number_2);
	return result;
}

big_int *big_int_shift_right (big_int *number, int shift) {
	if (shift % 8 == 0) {
		for (int k = 0; k < shift / 8; k++) {
			number->digits = realloc(number->digits, ++number->size);
			for (int i = number->size - 1; i > 0; i--) {
				number->digits[i] = number->digits[i - 1];
			}	
			number->digits[0] = 0;
		}
	}
	else {
		for (int k = 0; k < shift; k++) {
			int carry = 0;
			for (int i = number->size - 1; i >= 0; i--) {
				int flag = (number->digits[i] & 1) << 7;
				number->digits[i] = (number->digits[i] >> 1) + carry;
				carry = flag;
			}
			int i = 1;
			while (number->digits[number->size - i] == 0 && number->size - i != 0) number->size--;
			number->digits = realloc(number->digits, number->size);
		}
	}
	return number;
}

big_int *big_int_shift_left (big_int *number, int shift) {
	if (shift % 8 == 0) {
		for (int k = 0; k < shift / 8; k++) {
			for (int i = number->size - 1; i > 0; i--) {
				number->digits[i - 1] = number->digits[i];
			}
			number->digits = realloc(number->digits, --number->size);
		}
	}
	else {
			for (int k = 0; k < shift; k++) {
				int carry = 0;
				for (int i = 0; i < number->size; i++) {
					int flag = number->digits[i] >> 7;
					number->digits[i] = (number->digits[i] << 1) + carry;
					carry = flag;
				}
				if(carry) {
					number->digits = realloc(number->digits, ++number->size);
					number->digits[number->size - 1] = carry;
				}
		}
	}
	return number;
} 

big_int *big_int_binary_euclid (big_int *number_1, big_int *number_2) {
	int shift;
	if (number_1->size == 1 && number_1->digits[0] == 0) {
		return number_2;
	}	
	if (number_2->size == 1 && number_2->digits[0] == 0) {
		return number_1;
	}	
	//m, n - чётные gcd(m, n) = 2 * gcd(m / 2, n / 2)
	for (shift = 0; ((number_1->digits[0] | number_2->digits[0]) & 1) == 0; shift++) {
		big_int_shift_right(number_1, 1);
		big_int_shift_right(number_2, 1);
	}
	// m - чётное, тогда gcd(m, n) = gcd(m / 2, n)
	while ((number_1->digits[0] & 1) == 0) big_int_shift_right(number_1, 1);
	do {
		while ((number_2->digits[0] & 1) == 0) big_int_shift_right(number_2, 1);
		//m, n - нечётные и m < n gcd(m, n) = gcd(n - m, m)
		if (big_int_comparison(number_1, number_2) == 0) big_int_subtract(number_2, number_1);
		else {
			big_int *sub;
			sub = (big_int*)malloc(sizeof(big_int));
			big_int_assign(sub, number_1);
			big_int_subtract(sub, number_2);
			*number_1 = *number_2;
			*number_2 = *sub;
		}
		big_int_shift_right(number_2, 1);
	}
	while (number_2->size != 1 && number_2->digits[0] != 0);
	return big_int_shift_left(number_1, shift);
}

big_int big_int_division (big_int *number_1, big_int *number_2) {
	big_int *result = (big_int*)malloc(sizeof(big_int));
	result->size = 0;
	result->digits = (unsigned char*)malloc(result->size); 
	result->sign = (number_1->sign == number_2->sign) ? 0 : 1;
	big_int *remainder = (big_int*)malloc(sizeof(big_int));
	printf("%d %d \n" , result , remainder);
	remainder->size = number_1->size;
	remainder->digits = (unsigned char*)malloc(remainder->size); 
	remainder->sign = 0;
	
	big_int *new_number_1;
	new_number_1 = (big_int*)malloc(sizeof(big_int));
	new_number_1->size = number_1->size;
	big_int *old_number_1;
	old_number_1 = (big_int*)malloc(sizeof(big_int));
	big_int_assign(old_number_1, number_1);
	
	//new = 00001001 00101011
	//old = 00001010 01010000 00000000
	//result = 1 0 
	int flag;
	int i = 0;
	int bit_result = 1;
	while (old_number_1 != 0) {
		int step = 0;
		while (big_int_comparison(number_2, new_number_1) == 1) {
			int last = old_number_1->digits[old_number_1->size - 1] >> 7;
			big_int_shift_left(new_number_1, 1);
			new_number_1->digits[0] += last;
			big_int_shift_right(new_number_1, 1);
			step++;
		}
		flag++;
		big_int_subtract(new_number_1, number_2);
		bit_result += 10 * step;
		int quantity = 0, new_bit_result = bit_result;
		while (new_bit_result != 0) {
			quantity++;
			new_bit_result /= 10;
		}
		if (quantity >= 8) {
			result->digits = realloc(result->digits, ++result->size);
			result->digits[i] = bit_result;
			bit_result %= (quantity - 8) * 10;
		}
		big_int_print(new_number_1);
		big_int_print(old_number_1);
		big_int_print(result);
	}
	return *result;
}
/*
// Проверка на равенство a и b
if (big_int_eq(a, b))
{
res->q = big_int_deep_copy(one), res->r = big_int_deep_copy(zero);
return res; // Возврат результата
}

// Проверка на то, что a меньше или равно b
if (big_int_leq(a, b))
{
res->q = big_int_deep_copy(zero);
res->r = big_int_deep_copy(b);
return res; // Возврат результата
}

// Сдвиг ri влево на 8*(длина le - длина ri + 1)
big_int_self_bit_left(ri, 8*(le->length - ri->length + 1));

// Цикл, выполняющий сдвиг ri вправо, пока le меньше или равно ri и они не равны
while (big_int_leq(le, ri) && !big_int_eq(le, ri))
big_int_self_bit_right(ri);

// Вычитание ri из le
le = big_int_sub(le, ri);
big_int_self_bit_right(ri);
res->q = big_int_deep_copy(one);

// Цикл, выполняющий деление le на b
while (big_int_leq(b, ri)) 
{
if (big_int_leq(le , ri) && !big_int_eq(le, ri))
{
big_int_self_bit_right(ri);
big_int_self_bit_left(res->q);
}
else
{
le = big_int_sub(le, ri);
big_int_self_bit_right(ri);
big_int_self_bit_left(res->q);
res->q->number[0] |= 1;
}
}
res->r = big_int_deep_copy(le); // Копирование значения le в r

big_int_free(le); // Освобождение памяти, выделенной под le
big_int_free(ri); // Освобождение памяти, выделенной под ri

return res; // Возврат результата
}*/

int main() {
	char *number_string_1;
	number_string_1 = (char*)malloc(1000);
	scanf("%999s", number_string_1);
	
	char *number_string_2;
	number_string_2 = (char*)malloc(1000);
	scanf("%999s", number_string_2);
	
	big_int *number_1 = big_int_create(number_string_1);
	big_int *number_2 = big_int_create(number_string_2);
	
	big_int *new_number_1;
	new_number_1 = (big_int*)malloc(sizeof(big_int));
	big_int_assign(new_number_1, number_1);
	
	//big_int *gcd = big_int_binary_euclid(number_1, number_2);
	//big_int_print(gcd);
	//printf("%d", gcd->digits[0]);
	
	big_int_division(number_1, number_2);
	
	big_int_free(new_number_1);
	big_int_free(number_1);
	big_int_free(number_2);
	//big_int_free(multiplication_karatsuba_result);
	return 0;
}