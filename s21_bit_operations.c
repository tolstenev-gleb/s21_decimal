/* Copyright (c) 2025 Tolstenev Gleb */

/*
 * s21_bit_operations.c |
 */

#include "s21_decimal.h"

unsigned s21_get_bit(s21_decimal value, int index) {
  unsigned mask = 0;
  unsigned i = index / 32;
  unsigned shift = index % 32;

  mask = 1u << shift;
  return (value.bits[i] & mask) != 0;
}

unsigned s21_get_bit_big(s21_big_decimal value, int index) {
  unsigned mask = 0;
  unsigned i = index / 32;
  unsigned shift = index % 32;

  mask = 1u << shift;
  return (value.bits[i] & mask) != 0;
}

void s21_set_bit(s21_decimal *ptr_decimal, unsigned index, unsigned bit) {
  unsigned mask = 0;
  unsigned i = index / 32;
  unsigned bit_index = index % 32;

  if (bit == 1) {
    mask = 1u << bit_index;
    ptr_decimal->bits[i] |= mask;
  } else if (bit == 0) {
    mask = ~(1u << bit_index);
    ptr_decimal->bits[i] &= mask;
  }
}

void s21_set_bit_big(s21_big_decimal *ptr_big_decimal, unsigned index,
                     unsigned bit) {
  unsigned mask = 0;
  unsigned i = index / 32;
  unsigned bit_index = index % 32;

  if (bit == 1) {
    mask = 1u << bit_index;
    ptr_big_decimal->bits[i] |= mask;
  } else if (bit == 0) {
    mask = ~(1u << bit_index);
    ptr_big_decimal->bits[i] &= mask;
  }
}

