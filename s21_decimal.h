/* Copyright (c) 2025 Tolstenev Gleb */

/*
 * s21_decimal.h | The library to work with s21_decimal numbers
 */

#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdbool.h>

#include "../print_decimal/src/print_decimal.h"

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
  unsigned int scale;
} s21_big_decimal;

unsigned s21_get_bit(s21_decimal value, int index);
unsigned s21_get_bit_big(s21_big_decimal value, int index);
void s21_set_bit(s21_decimal* ptr_decimal, unsigned index, unsigned bit);
void s21_set_bit_big(s21_big_decimal* ptr_big_decimal, unsigned index,
                     unsigned bit);

void s21_bitwise_add(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal* result);

#endif  // S21_DECIMAL_H
