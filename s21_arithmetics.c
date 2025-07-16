/* Copyright (c) 2025 Tolstenev Gleb */

/*
 * s21_arithmetics.c |
 */

#include "s21_decimal.h"


void s21_bitwise_add(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int res = 0, carry = 0;
  int bit_1 = 0, bit_2 = 0;
  for (int i = 0; i < 256; i++) {
    bit_1 = s21_get_big_bit(value_1, i);
    bit_2 = s21_get_big_bit(value_2, i);
    res = bit_1 + bit_2 + carry;
    carry = res / 2;
    s21_set_big_bit(result, i, res % 2);
  }
}