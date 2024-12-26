#include <check.h>

#include "../s21_string.h"

START_TEST(test_case) {
  ck_assert_str_eq("test", "test");
}
END_TEST

Suite *test_csharp(void) {
  Suite *s = suite_create("Csharp test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, test_case);
  suite_add_tcase(s, tc);

  return s;
}