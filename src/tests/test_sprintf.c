#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

#define STRING_LENGTH 50

START_TEST(string_without_format_test) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "Hello, world!");
  int res2 = sprintf(buffer2, "Hello, world!");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%d", 1234567890);
  int res2 = sprintf(buffer2, "%d", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_width_larger_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%20d", 1234567890);
  int res2 = sprintf(buffer2, "%20d", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_width_smaller_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%5d", 1234567890);
  int res2 = sprintf(buffer2, "%5d", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_width_munis_flag) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%-20d", 1234567890);
  int res2 = sprintf(buffer2, "%-20d", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_precision_smaller_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%.5d", 1234567890);
  int res2 = sprintf(buffer2, "%.5d", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_precision_larger_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%.20d", 1234567890);
  int res2 = sprintf(buffer2, "%.20d", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_flag_plus_positive_number) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%+d", 1234567890);
  int res2 = sprintf(buffer2, "%+d", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_flag_plus_negative_number) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%+d", -1234567890);
  int res2 = sprintf(buffer2, "%+d", -1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_flag_space_positive_number) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "% d", 1234567890);
  int res2 = sprintf(buffer2, "% d", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_flag_space_negative_number) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "% d", -1234567890);
  int res2 = sprintf(buffer2, "% d", -1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_lengh_l) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%ld", 90000000000000000);
  int res2 = sprintf(buffer2, "%ld", 90000000000000000);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_lengh_h) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%hd", 12345);
  int res2 = sprintf(buffer2, "%hd", 12345);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_c) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%c", 'a');
  int res2 = sprintf(buffer2, "%c", 'a');

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_c_with_width) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%10c", 'a');
  int res2 = sprintf(buffer2, "%10c", 'a');

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_c_with_width_flag_minus) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%-10c", 'a');
  int res2 = sprintf(buffer2, "%-10c", 'a');

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_s) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%s", "Hello, world!");
  int res2 = sprintf(buffer2, "%s", "Hello, world!");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_s_with_precision_smaller_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%.5s", "Hello, world!");
  int res2 = sprintf(buffer2, "%.5s", "Hello, world!");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_s_with_precision_larger_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%.20s", "Hello, world!");
  int res2 = sprintf(buffer2, "%.20s", "Hello, world!");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_s_with_width_larger_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%20s", "Hello, world!");
  int res2 = sprintf(buffer2, "%20s", "Hello, world!");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_s_with_width_smaller_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%5s", "Hello, world!");
  int res2 = sprintf(buffer2, "%5s", "Hello, world!");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_s_with_width_munis_flag) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%-20s", "Hello, world!");
  int res2 = sprintf(buffer2, "%-20s", "Hello, world!");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_u) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%u", 1234567890);
  int res2 = sprintf(buffer2, "%u", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_u_with_width_larger_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%20u", 1234567890);
  int res2 = sprintf(buffer2, "%20u", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_u_with_width_smaller_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%5u", 1234567890);
  int res2 = sprintf(buffer2, "%5u", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_u_with_width_munis_flag) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%-20u", 1234567890);
  int res2 = sprintf(buffer2, "%-20u", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_u_with_precision_smaller_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%.5u", 1234567890);
  int res2 = sprintf(buffer2, "%.5u", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_u_with_precision_larger_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%.20u", 1234567890);
  int res2 = sprintf(buffer2, "%.20u", 1234567890);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_u_with_lengh_l) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%lu", 9000000000000000000);
  int res2 = sprintf(buffer2, "%lu", 9000000000000000000);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_u_with_lengh_h) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%hu", 12345);
  int res2 = sprintf(buffer2, "%hu", 12345);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_f) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%f", 123.456789);
  int res2 = sprintf(buffer2, "%f", 123.456789);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_f_with_width_larger_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%20f", 123.456789);
  int res2 = sprintf(buffer2, "%20f", 123.456789);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_f_with_width_smaller_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%5f", 123.456789);
  int res2 = sprintf(buffer2, "%5f", 123.456789);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_f_with_width_munis_flag) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%-20f", 123.456789);
  int res2 = sprintf(buffer2, "%-20f", 123.456789);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_f_with_precision_smaller_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%.f", 123.656789);
  int res2 = sprintf(buffer2, "%.f", 123.656789);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_f_with_precision_larger_than_length) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%.20f", 123.456789);
  int res2 = sprintf(buffer2, "%.20f", 123.456789);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_f_with_flag_plus_positive_number) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%+f", 123.456789);
  int res2 = sprintf(buffer2, "%+f", 123.456789);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_f_with_flag_plus_negative_number) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%+f", -123.456789);
  int res2 = sprintf(buffer2, "%+f", -123.456789);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_f_with_flag_space_positive_number) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "% f", 123.456789);
  int res2 = sprintf(buffer2, "% f", 123.456789);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_f_with_flag_space_negative_number) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "% f", -123.456789);
  int res2 = sprintf(buffer2, "% f", -123.456789);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifier_d_with_text) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "Unknown error: %d", 107);
  int res2 = sprintf(buffer2, "Unknown error: %d", 107);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(string_rewriting) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "Unknown error: %d", 100);
  res1 = s21_sprintf(buffer1, "Unknown error: %d", 107);
  int res2 = sprintf(buffer2, "Unknown error: %d", 100);
  res2 = sprintf(buffer2, "Unknown error: %d", 107);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(two_specifiers) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%d %d", 100, 200);
  int res2 = sprintf(buffer2, "%d %d", 100, 200);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(two_defferent_specifiers) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%10d space %.3s", 100, "Hello");
  int res2 = sprintf(buffer2, "%10d space %.3s", 100, "Hello");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(specifiers_percent) {
  char buffer1[STRING_LENGTH + 1] = {0};
  char buffer2[STRING_LENGTH + 1] = {0};

  int res1 = s21_sprintf(buffer1, "%% space");
  int res2 = sprintf(buffer2, "%% space");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

Suite *test_sprintf(void) {
  Suite *s = suite_create("Sprintf test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, string_without_format_test);

  tcase_add_test(tc, specifier_d);
  tcase_add_test(tc, specifier_d_with_width_larger_than_length);
  tcase_add_test(tc, specifier_d_with_width_smaller_than_length);
  tcase_add_test(tc, specifier_d_with_width_munis_flag);
  tcase_add_test(tc, specifier_d_with_precision_smaller_than_length);
  tcase_add_test(tc, specifier_d_with_precision_larger_than_length);
  tcase_add_test(tc, specifier_d_with_flag_plus_positive_number);
  tcase_add_test(tc, specifier_d_with_flag_plus_negative_number);
  tcase_add_test(tc, specifier_d_with_flag_space_positive_number);
  tcase_add_test(tc, specifier_d_with_flag_space_negative_number);
  tcase_add_test(tc, specifier_d_with_lengh_l);
  tcase_add_test(tc, specifier_d_with_lengh_h);

  tcase_add_test(tc, specifier_c);
  tcase_add_test(tc, specifier_c_with_width);
  tcase_add_test(tc, specifier_c_with_width_flag_minus);

  tcase_add_test(tc, specifier_s);
  tcase_add_test(tc, specifier_s_with_precision_smaller_length);
  tcase_add_test(tc, specifier_s_with_precision_larger_length);
  tcase_add_test(tc, specifier_s_with_width_larger_than_length);
  tcase_add_test(tc, specifier_s_with_width_smaller_than_length);
  tcase_add_test(tc, specifier_s_with_width_munis_flag);

  tcase_add_test(tc, specifier_u);
  tcase_add_test(tc, specifier_u_with_width_larger_than_length);
  tcase_add_test(tc, specifier_u_with_width_smaller_than_length);
  tcase_add_test(tc, specifier_u_with_width_munis_flag);
  tcase_add_test(tc, specifier_u_with_precision_smaller_than_length);
  tcase_add_test(tc, specifier_u_with_precision_larger_than_length);
  tcase_add_test(tc, specifier_u_with_lengh_l);
  tcase_add_test(tc, specifier_u_with_lengh_h);

  tcase_add_test(tc, specifier_f);
  tcase_add_test(tc, specifier_f_with_width_larger_than_length);
  tcase_add_test(tc, specifier_f_with_width_smaller_than_length);
  tcase_add_test(tc, specifier_f_with_width_munis_flag);
  tcase_add_test(tc, specifier_f_with_precision_smaller_than_length);
  tcase_add_test(tc, specifier_f_with_precision_larger_than_length);
  tcase_add_test(tc, specifier_f_with_flag_plus_positive_number);
  tcase_add_test(tc, specifier_f_with_flag_plus_negative_number);
  tcase_add_test(tc, specifier_f_with_flag_space_positive_number);
  tcase_add_test(tc, specifier_f_with_flag_space_negative_number);

  tcase_add_test(tc, specifier_d_with_text);
  tcase_add_test(tc, string_rewriting);
  tcase_add_test(tc, two_specifiers);
  tcase_add_test(tc, two_defferent_specifiers);

  tcase_add_test(tc, specifiers_percent);

  suite_add_tcase(s, tc);

  return s;
}