#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

START_TEST(test_to_upper) {
  char *line1 = "123qwe123";
  char *line2 = "123QWE123";
  char *res = to_upper(line1);
  ck_assert_str_eq(res, line2);
  free(res);
  char *line3 = NULL;
  char *res2 = to_upper(line3);
  ck_assert_ptr_null(res2);
}
END_TEST

START_TEST(test_to_lower) {
  char *line1 = "123QWE123";
  char *line2 = "123qwe123";
  char *res = to_lower(line1);
  ck_assert_str_eq(res, line2);
  free(res);
  char *line3 = NULL;
  char *res2 = to_lower(line3);
  ck_assert_ptr_null(res2);
}
END_TEST

START_TEST(test_insert) {
  char *line1 = "123QWE123";
  char *line2 = "456";
  char *actual = "123456QWE123";
  char *res = insert(line1, line2, 3);
  ck_assert_str_eq(res, actual);
  free(res);

  char *line3 = NULL;
  char *res2 = insert(line3, line2, 1);
  ck_assert_ptr_null(res2);

  char *line4 = "123";
  char *line5 = "456";
  char *res3 = insert(line4, line5, 4);
  ck_assert_ptr_null(res3);
}
END_TEST

START_TEST(test_trim) {
  char *line1 = "52amir52";
  char *line2 = "52";
  char *actual = "amir";
  char *res = trim(line1, line2);
  ck_assert_str_eq(res, actual);
  free(res);

  char *line3 = NULL;
  char *res2 = trim(line3, "52");
  ck_assert_ptr_null(res2);

  char *line4 = "******";
  char *line5 = "*";
  char *actual1 = "";
  char *res3 = trim(line4, line5);
  ck_assert_str_eq(res3, actual1);
  free(res3);
}
END_TEST

Suite *test_csharp(void) {
  Suite *s = suite_create("Csharp test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, test_to_upper);
  tcase_add_test(tc, test_to_lower);
  tcase_add_test(tc, test_insert);
  tcase_add_test(tc, test_trim);
  suite_add_tcase(s, tc);
  return s;
}