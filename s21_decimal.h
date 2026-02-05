/* Copyright (c) 2026 Tolstenev Gleb */

/*
 * s21_decimal.h | Заголовочный файл библиотеки по работе с числами s21_decimal
 */

#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdbool.h>

#include "../print_decimal/src/print_decimal.h"

#define SIZE_BIG_DECIMAL 6  // см. README.md
#define COUNT_BITS_BIG_DECIMAL 192

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[SIZE_BIG_DECIMAL];
  unsigned int scale;
} s21_big_decimal;

unsigned s21_get_bit(s21_decimal value, int index);
unsigned s21_get_bit_big(s21_big_decimal value, int index);
void s21_set_bit(s21_decimal* ptr_decimal, unsigned index, unsigned bit);
void s21_set_bit_big(s21_big_decimal* ptr_big_decimal, unsigned index,
                     unsigned bit);

void s21_bitwise_add(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal* result);
void s21_bitwise_sub(s21_big_decimal big_1, s21_big_decimal big_2,
                     s21_big_decimal* ptr_result);
int s21_compare_big_decimals(s21_big_decimal big_1, s21_big_decimal big_2);

unsigned int s21_is_zero_decimal(s21_decimal value);
void s21_clear_decimal_big(s21_big_decimal* ptr_big);
void s21_decimal_to_big(s21_decimal value, s21_big_decimal* ptr_big);

#endif  // S21_DECIMAL_H
