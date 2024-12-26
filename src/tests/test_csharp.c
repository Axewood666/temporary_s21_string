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

Suite *test_csharp(void) {
  Suite *s = suite_create("Csharp test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, test_to_upper);
  suite_add_tcase(s, tc);
  return s;
}