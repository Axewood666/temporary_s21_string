/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "tests/unit_sprintf_tests.check" instead.
 */

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

#define NUM_COUNT 10
#define STRING_COUNT 100
#define STRING_LENGTH 50

void generate_random_string(char *str, s21_size_t length);

START_TEST(s21_randomstrings_test) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};
  char generated_string[STRING_LENGTH + 1] = {0};
  for (s21_size_t i = 0; i < STRING_COUNT; i++) {
    generate_random_string(generated_string, STRING_LENGTH);
    int res1 = s21_sprintf(buffer1, generated_string);
    int res2 = sprintf(buffer2, generated_string);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buffer1, buffer2);
  }
}
END_TEST

Suite *test_sprintf(void) {
  Suite *s = suite_create("Sprintf test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, s21_randomstrings_test);
  suite_add_tcase(s, tc);

  return s;
}

void generate_random_string(char *str, s21_size_t length) {
  const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  for (s21_size_t i = 0; i < length; i++) {
    int key = rand() % (int)(sizeof(charset) - 1);
    str[i] = charset[key];
  }
  str[length] = '\0';  // Завершение строки
}