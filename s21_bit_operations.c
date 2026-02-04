/* Copyright (c) 2026 Tolstenev Gleb */

/*
 * s21_bit_operations.c |
 */

#include "s21_decimal.h"

/**
 * @brief Проверяет бит по индексу index в переменной value типа unsigned int
 * @param value значение переменной
 * @param index индекс проверяемого бита (от 0 до 31)
 * @return 1 - бит установлен; 0 - бит не установлен
 */
unsigned s21_get_bit_int(unsigned value, unsigned index) {
  unsigned bit = 0;
  unsigned mask = 1 << index;

  if ((value & mask) != 0) {
    bit = 1;
  }
  return bit;
}

/**
 * @brief Проверяет бит по индексу в переменной value типа s21_decimal
 * @param value значение переменной
 * @param index индекс проверяемого бита (от 0 до 127)
 * @return 1 - бит установлен; 0 - бит не установлен
 */
unsigned s21_get_bit(s21_decimal value, int index) {
  unsigned bit = 0;
  unsigned shift = index % 32;
  unsigned mask = 1u << shift;
  unsigned i = index / 32;

  if ((value.bits[i] & mask) != 0) {
    bit = 1;
  }
  return bit;
}

/**
 * @brief Проверяет бит по индексу index в переменной value типа s21_big_decimal
 * @param value значение переменной
 * @param index индекс проверяемого бита (от 0 до 255)
 * @return 1 - бит установлен; 0 - бит не установлен
 */
unsigned s21_get_bit_big(s21_big_decimal value, int index) {
  unsigned bit = 0;
  unsigned shift = index % 32;
  unsigned mask = 1u << shift;
  unsigned i = index / 32;

  if ((value.bits[i] & mask) != 0) {
    bit = 1;
  }
  return bit;
}

/**
 * Устанавливает bit 0 или 1 по индексу index в unsigned int по указателю
 * @param ptr_int указатель на unsigned int
 * @param index индекс по которому нужно установить бит (от 0 до 31)
 * @param bit значение бита, которое нужно установить (0 или 1)
 */
void s21_set_bit_int(unsigned* ptr_int, unsigned index, unsigned bit) {
  unsigned mask = 1u << index;
  unsigned value = *ptr_int;
  unsigned new_value = 0;

  if (bit == 1) {
    new_value = value | mask;
  } else if (bit == 0) {
    mask = ~mask;
    new_value = value & mask;
  }
  *ptr_int = new_value;
}

/**
 * Устанавливает bit 0 или 1 по индексу index в s21_decimal по указателю
 * @param ptr_decimal указатель на s21_decimal
 * @param index индекс по которому нужно установить бит (от 0 до 127)
 * @param bit значение бита, которое нужно установить (0 или 1)
 */
void s21_set_bit(s21_decimal* ptr_decimal, unsigned index, unsigned bit) {
  unsigned mask = 1u << index;
  unsigned i = index / 32;
  unsigned value = ptr_decimal->bits[i];
  unsigned new_value = 0;

  if (bit == 1) {
    new_value = value | mask;
  } else if (bit == 0) {
    mask = ~mask;
    new_value = value & mask;
  }
  ptr_decimal->bits[i] = new_value;
}

/**
 * Устанавливает bit 0 или 1 по индексу index в s21_big_decimal по указателю
 * @param ptr_big_decimal указатель на s21_big_decimal
 * @param index индекс по которому нужно установить бит (от 0 до 255)
 * @param bit значение бита, которое нужно установить (0 или 1)
 */
void s21_set_bit_big(s21_big_decimal* ptr_big_decimal, unsigned index,
                     unsigned bit) {
  unsigned mask = 1u << index;
  unsigned i = index / 32;
  unsigned value = ptr_big_decimal->bits[i];
  unsigned new_value = 0;

  if (bit == 1) {
    new_value = value | mask;
  } else if (bit == 0) {
    mask = ~mask;
    new_value = value & mask;
  }
  ptr_big_decimal->bits[i] = new_value;
}
