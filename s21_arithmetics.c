/* Copyright (c) 2026 Tolstenev Gleb */

/*
 * s21_arithmetics.c | Файл с исходным кодом арифметических функций
 */

#include "s21_decimal.h"

/**
 * @brief Побитовое сложение s21_big_decimal
 * @param big_1 первое число
 * @param big_2 второе число
 * @param ptr_result указатель на s21_big_decimal,
 * в который будет записан результат
 */
void s21_bitwise_add(s21_big_decimal big_1, s21_big_decimal big_2,
                     s21_big_decimal* ptr_result) {
  int res = 0, carry = 0;  // carry - перенос. При 1 + 1 = 10
  int bit_1 = 0, bit_2 = 0;
  for (int i = 0; i < COUNT_BITS_BIG_DECIMAL; i++) {
    bit_1 = s21_get_big_bit(big_1, i);
    bit_2 = s21_get_big_bit(big_2, i);
    res = bit_1 + bit_2 + carry;
    carry = res / 2;
    s21_set_big_bit(ptr_result, i, res % 2);
  }
}

/**
 * @brief Побитовое вычитание s21_big_decimal. big_1 обязательно должен быть
 * больше или равен big_2
 * @param big_1 первое число
 * @param big_2 второе число
 * @param ptr_result указатель на s21_big_decimal,
 * в который будет записан результат
 */
void s21_bitwise_sub(s21_big_decimal big_1, s21_big_decimal big_2,
                     s21_big_decimal* ptr_result) {
  int res = 0, borrow = 0;  // borrow - займ. При 0 - 1
  int bit_1 = 0, bit_2 = 0;
  for (int i = 0; i < COUNT_BITS_BIG_DECIMAL; i++) {
    bit_1 = s21_get_big_bit(&big_1, i);
    bit_2 = s21_get_big_bit(&big_2, i);
    res = bit_1 - bit_2 - borrow;
    if (res < 0) {
      res += 2;
      borrow = 1;
    } else {
      borrow = 0;
    }
    s21_set_big_bit(ptr_result, i, res % 2);
  }
}

/**
 * @brief Побитовое сравнение s21_big_decimal
 * @param big_1 первое число
 * @param big_2 второе число
 * @return 1, если первое число больше второго.
 * @return -1, если второе число больше первого.
 * @return 0, если первое число равно второму.
 */
int s21_compare_big_decimals(s21_big_decimal big_1,
                             s21_big_decimal big_2) {
  int result = 0;
  int bit_1 = 0, bit_2 = 0;
  bool stop = false;
  for (int i = COUNT_BITS_BIG_DECIMAL - 1; i >= 0 && !stop; i--) {
    bit_1 = s21_get_big_bit(big_1, i);
    bit_2 = s21_get_big_bit(big_2, i);
    if (bit_1 > bit_2) {
      result = 1;
      stop = true;
    }
    if (bit_1 < bit_2) {
      result = -1;
      stop = true;
    }
  }
  return result;
}

/**
 * @brief Умножение s21_big_decimal на 10
 * @param ptr_big указатель на s21_big_decimal
 * Реализовано по формуле:
 * x * 10 = x * (2 + 8) = x * 2 + x * 8
 */
void s21_mul_ten_big(s21_big_decimal *ptr_big) {
  // Сдвигаем на 1 - это умножение на 2
  s21_shift_left_big(ptr_big, 1);
  s21_big_decimal temp = *ptr_big;  
  // Сдвигаем ещё на 2 (суммарно - 3) - это умножение на 8
  s21_shift_left_big(ptr_big, 2);  
  s21_bitwise_add(temp, *ptr_big, ptr_big);
}

/**
 * @brief Умножение s21_big_decimal на 10 несколько раз
 * @param ptr_big указатель на s21_big_decimal
 * @param n количество умножений
 */
void s21_mul_ten_n_times_big(s21_big_decimal *ptr_big, unsigned n) {
  while (n > 0) {
    s21_mul_ten_big(ptr_big);
    n--;
  }
}

/**
 * @brief Проверяет, является ли s21_decimal нулём.
 * Проверяется только значащая часть
 * без учёта знака и коэффициента масштабирования.
 * @param value значение s21_decimal
 */
unsigned int s21_is_zero_decimal(s21_decimal value) {
  bool answer = false;
  if (value.bits[2] == 0 && value.bits[1] == 0 && value.bits[0] == 0) {
    answer = true;
  }
  return answer;
}

/**
 * @brief Обнуляет s21_big_decimal по указателю
 * @param ptr_big указатель на s21_big_decimal
 */
void s21_clear_decimal_big(s21_big_decimal* ptr_big) {
  ptr_big->bits[0] = 0;
  ptr_big->bits[1] = 0;
  ptr_big->bits[2] = 0;
  ptr_big->bits[3] = 0;
  ptr_big->bits[4] = 0;
  ptr_big->bits[5] = 0;
}

/**
 * @brief Переводит значение s21_decimal в s21_big_decimal по указателю
 * @param value значение s21_decimal
 * @param ptr_big указатель на s21_big_decimal, в который будет записано
 * значение
 */
void s21_decimal_to_big(s21_decimal value, s21_big_decimal* ptr_big) {
  ptr_big->bits[0] = value.bits[0];
  ptr_big->bits[1] = value.bits[1];
  ptr_big->bits[2] = value.bits[2];
  ptr_big->bits[3] = 0;
  ptr_big->bits[4] = 0;
  ptr_big->bits[5] = 0;
}
