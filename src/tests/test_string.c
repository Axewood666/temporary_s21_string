#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(s21_strlen_test) {
  char *str = "";
  ck_assert_int_eq(s21_strlen(str), strlen(str));

  char *str1 = "Hello";
  ck_assert_int_eq(s21_strlen(str1), strlen(str1));

  char *str2 = "PRivet\nkakdela?bu, ispugalsa?";
  ck_assert_int_eq(s21_strlen(str2), strlen(str2));

  char *str3 = "a";
  ck_assert_int_eq(s21_strlen(str3), strlen(str3));
}
END_TEST

START_TEST(s21_strchr_test) {
  char *str = "";
  ck_assert_ptr_eq(s21_strchr(str, 's'), strchr(str, 's'));

  char *str2 = "PRivet\nkakdela?bu, ispugalsa?";
  ck_assert_ptr_eq(s21_strchr(str2, '\n'), strchr(str2, '\n'));
  ck_assert_ptr_eq(s21_strchr(str2, 'P'), strchr(str2, 'P'));
  ck_assert_ptr_eq(s21_strchr(str2, 'z'), strchr(str2, 'z'));

  char *str3 = "abcde";
  ck_assert_ptr_eq(s21_strchr(str3, 'e'), strchr(str3, 'e'));

  char *str4 = "1234567890";
  ck_assert_ptr_eq(s21_strchr(str4, '\0'), strchr(str4, '\0'));
}
END_TEST

START_TEST(s21_strrchr_test) {
  char *str = "sssssssssssls";
  ck_assert_ptr_eq(s21_strrchr(str, 's'), strrchr(str, 's'));
  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
  ck_assert_ptr_eq(s21_strrchr(str, '\n'), strrchr(str, '\n'));

  char *str2 = "PRivet\nkakdela?bu, ispugalsa?\n";
  ck_assert_ptr_eq(s21_strrchr(str2, '\n'), strrchr(str2, '\n'));

  char *str3 = "abcde";
  ck_assert_ptr_eq(s21_strrchr(str3, 'e'), strrchr(str3, 'e'));

  char *str4 = "1234567890";
  ck_assert_ptr_eq(s21_strrchr(str4, '\0'), strrchr(str4, '\0'));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  char *str = "1234567890";
  ck_assert_ptr_eq(s21_strpbrk(str, "74567"), strpbrk(str, "74567"));
  ck_assert_ptr_eq(s21_strpbrk(str, "sadxzP"), strpbrk(str, "sadxzP"));
  ck_assert_ptr_eq(s21_strpbrk(str, "xyz"), strpbrk(str, "xyz"));

  char *str2 = "PRivet\nkakdela?bu, ispugalsa?";
  ck_assert_ptr_eq(s21_strpbrk(str2, "sadxzP"), strpbrk(str2, "sadxzP"));
  ck_assert_ptr_eq(s21_strpbrk(str2, "nz"), strpbrk(str2, "nz"));

  char *str3 = "abcdef";
  ck_assert_ptr_eq(s21_strpbrk(str3, "def"), strpbrk(str3, "def"));
}
END_TEST

START_TEST(s21_memchr_test) {
  char *str = "l";
  ck_assert_ptr_eq(s21_memchr(str, 's', 1), memchr(str, 's', 1));
  ck_assert_ptr_eq(s21_memchr(str, 'l', 1), memchr(str, 'l', 1));

  char *str2 = "PRivet\nkakdela?bu, ispugalsa?";
  ck_assert_ptr_eq(s21_memchr(str2, '\n', strlen(str2)),
                   memchr(str2, '\n', strlen(str2)));
  ck_assert_ptr_eq(s21_memchr(str2, 'P', 1), memchr(str2, 'P', 1));
  ck_assert_ptr_eq(s21_memchr(str2, 'P', 0), memchr(str2, 'P', 0));

  char *str3 = "abcdef";
  ck_assert_ptr_eq(s21_memchr(str3, 'c', 6), memchr(str3, 'c', 6));
}
END_TEST

START_TEST(s21_memcmp_test) {
  char *str = "0001";
  char *str2 = "0001";
  ck_assert_int_eq(s21_memcmp(str, str2, 3), memcmp(str, str2, 3));
  ck_assert_int_eq(s21_memcmp(str, str2, 4), memcmp(str, str2, 4));

  char *str3 = "test";
  char *str4 = "zero";
  ck_assert_int_eq(s21_memcmp(str3, str3, 0), memcmp(str3, str3, 0));
  ck_assert_int_eq(s21_memcmp(str3, str4, 4), memcmp(str3, str4, 4));

  char *str5 = "case";
  char *str6 = "Case";
  ck_assert_int_eq(s21_memcmp(str5, str6, 4), memcmp(str5, str6, 4));
}
END_TEST

START_TEST(s21_memcpy_test) {
  char *str = "01234";
  char str2[40] = {0};
  char str3[40] = {0};
  ck_assert_ptr_eq(s21_memcpy(str2, str, 4), memcpy(str2, str, 4));
  ck_assert_str_eq((char *)s21_memcpy(str3, str, 4),
                   (char *)memcpy(str3, str, 4));

  char src[] = "Hello, World!";
  char dest1[50] = {0};
  char dest2[50] = {0};
  s21_memcpy(dest1, src, 14);
  memcpy(dest2, src, 14);
  ck_assert_str_eq(dest1, dest2);

  char src2[] = "Test";
  char dest3[50] = "Initial content";
  char dest4[50] = "Initial content";
  s21_memcpy(dest3, src2, 0);
  memcpy(dest4, src2, 0);
  ck_assert_str_eq(dest3, dest4);
}
END_TEST

START_TEST(s21_memset_test) {
  char str1[] = "Test function memset s21";
  ck_assert_ptr_eq(s21_memset(str1, ' ', 24), memset(str1, ' ', 24));

  char str2[15] = {0};
  char str3[15] = {0};
  s21_memset(str2, '\0', 15);
  memset(str3, '\0', 15);
  ck_assert_str_eq(str2, str3);

  char str4[6] = "Hello";
  char str5[6] = "Hello";
  s21_memset(str4, 'X', 5);
  memset(str5, 'X', 5);
  ck_assert_str_eq(str4, str5);

  char str7[100] = "XXXXXXXXXXXXXXXX";
  char str8[100] = "XXXXXXXXXXXXXXXX";
  s21_memset(str7, 'Y', 99);
  memset(str8, 'Y', 99);
  ck_assert_str_eq(str7, str8);
}
END_TEST

START_TEST(s21_strncpy_test) {
  char *str = "01234";
  char str2[40] = {0};
  char str3[40] = {0};
  ck_assert_ptr_eq(s21_strncpy(str2, str, 2), strncpy(str2, str, 2));
  ck_assert_str_eq(s21_strncpy(str3, str, 4), strncpy(str3, str, 4));

  char src[] = "Hello, World!";
  char dest1[50] = {0};
  char dest2[50] = {0};
  s21_strncpy(dest1, src, 14);
  strncpy(dest2, src, 14);
  ck_assert_str_eq(dest1, dest2);

  char src3[] = "Full string copy";
  char dest5[50] = {0};
  char dest6[50] = {0};
  s21_strncpy(dest5, src3, strlen(src3) + 1);
  strncpy(dest6, src3, strlen(src3) + 1);
  ck_assert_str_eq(dest5, dest6);
}
END_TEST

START_TEST(s21_strcspn_test) {
  char *str = "1234567890";
  ck_assert_int_eq(s21_strcspn(str, "74567"), strcspn(str, "74567"));
  ck_assert_int_eq(s21_strcspn(str, "sadxzP"), strcspn(str, "sadxzP"));
  ck_assert_int_eq(s21_strcspn(str, "xyz"), strcspn(str, "xyz"));

  char *str2 = "PRivet\nkakdela?bu, ispugalsa?";
  ck_assert_int_eq(s21_strcspn(str2, "sadxzP"), strcspn(str2, "sadxzP"));
  ck_assert_int_eq(s21_strcspn(str2, "nz"), strcspn(str2, "nz"));

  char *str3 = "abcdef";
  ck_assert_int_eq(s21_strcspn(str3, "def"), strcspn(str3, "def"));
}
END_TEST

START_TEST(s21_strtok_test) {
  char str1[] = "One,Two,Three";
  char str2[] = "One,Two,Three";

  ck_assert_str_eq(s21_strtok(str1, ","), strtok(str2, ","));
  ck_assert_str_eq(s21_strtok(str1, ","), strtok(str2, ","));
  ck_assert_str_eq(s21_strtok(str1, ","), strtok(str2, ","));
  ck_assert_str_eq(s21_strtok(str1, ","), strtok(str2, ","));
  ck_assert_ptr_eq(s21_strtok(s21_NULL, ","), strtok(s21_NULL, ","));

  char str3[] = ",LeadingComma,TrailingComma,";
  char str4[] = ",LeadingComma,TrailingComma,";
  for (int i = 0; i < 3; i++) {
    ck_assert_str_eq(s21_strtok(str3, ","), strtok(str4, ","));
  }

  char str5[] = "A||B||C";
  char str6[] = "A||B||C";
  for (int i = 0; i < 6; i++) {
    ck_assert_str_eq(s21_strtok(str5, ","), strtok(str6, ","));
  }
}
END_TEST

START_TEST(s21_strncat_test) {
  char strka1[100] = "One,Two,Three";
  char strka2[100] = "One,Two,Three";
  ck_assert_str_eq(s21_strncat(strka1, ",Four,Five", 20),
                   strncat(strka2, ",Four,Five", 20));

  char strka3[100] = "Good";
  char strka4[100] = "Good";
  ck_assert_str_eq(s21_strncat(strka3, "Morning", 10),
                   strncat(strka4, "Morning", 10));

  strka3[0] = '\0';
  strka4[0] = '\0';
  ck_assert_str_eq(s21_strncat(strka3, "Test", 2), strncat(strka4, "Test", 2));
}
END_TEST

START_TEST(s21_strstr_test) {
  char *haystack1 = "Hello, World!";
  char *needle1 = "World";
  ck_assert_ptr_eq(s21_strstr(haystack1, needle1), strstr(haystack1, needle1));

  char *haystack2 = "Test string";
  char *needle2 = "Test";
  ck_assert_ptr_eq(s21_strstr(haystack2, needle2), strstr(haystack2, needle2));

  char *haystack3 = "Find me at the end";
  char *needle3 = "end";
  ck_assert_ptr_eq(s21_strstr(haystack3, needle3), strstr(haystack3, needle3));

  char *haystack4 = "No match here";
  char *needle4 = "match!";
  ck_assert_ptr_eq(s21_strstr(haystack4, needle4), strstr(haystack4, needle4));

  char *haystack5 = "Any string";
  char *needle5 = "";
  ck_assert_ptr_eq(s21_strstr(haystack5, needle5), strstr(haystack5, needle5));

  char *haystack6 = "";
  char *needle6 = "not found";
  ck_assert_ptr_eq(s21_strstr(haystack6, needle6), strstr(haystack6, needle6));

  char *haystack7 = "Short";
  char *needle7 = "Longer";
  ck_assert_ptr_eq(s21_strstr(haystack7, needle7), strstr(haystack7, needle7));

  char *haystack8 = "abcabcabc";
  char *needle8 = "abc";
  ck_assert_ptr_eq(s21_strstr(haystack8, needle8), strstr(haystack8, needle8));

  char *haystack9 = "Identical";
  char *needle9 = "Identical";
  ck_assert_ptr_eq(s21_strstr(haystack9, needle9), strstr(haystack9, needle9));

  char *haystack10 = "This is a test";
  char *needle10 = "is a";
  ck_assert_ptr_eq(s21_strstr(haystack10, needle10),
                   strstr(haystack10, needle10));
}
END_TEST

START_TEST(s21_strerror_test) {
  for (int i = -1; i < 140; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

int sign(int num) {
  if (num > 0) {
    return 1;
  } else if (num < 0) {
    return -1;
  } else {
    return 0;
  }
}

START_TEST(s21_strncmp_test) {
  char *str = "0001";
  char *str2 = "0001";
  ck_assert_int_eq(sign(s21_strncmp(str, str2, 3)),
                   sign(strncmp(str, str2, 3)));
  ck_assert_int_eq(sign(s21_strncmp(str, str2, 4)),
                   sign(strncmp(str, str2, 4)));

  char *str3 = "test";
  char *str4 = "zero";
  ck_assert_int_eq(sign(s21_strncmp(str3, str4, 0)),
                   sign(strncmp(str3, str4, 0)));
  ck_assert_int_eq(sign(s21_strncmp(str3, str4, 2)),
                   sign(strncmp(str3, str4, 2)));

  char *str5 = "case";
  char *str6 = "Case";
  ck_assert_int_eq(sign(s21_strncmp(str5, str6, 4)),
                   sign(strncmp(str5, str6, 4)));

  char str7[13] = "Hello!?>21.?:";
  char str8[13] = "Hello!?>21.?:";
  ck_assert_int_eq(sign(s21_strncmp(str7, str8, 13)),
                   sign(strncmp(str7, str8, 13)));
}
END_TEST

Suite *test_string(void) {
  Suite *s = suite_create("String functions test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, s21_strlen_test);
  tcase_add_test(tc, s21_strchr_test);
  tcase_add_test(tc, s21_strrchr_test);
  tcase_add_test(tc, s21_strpbrk_test);
  tcase_add_test(tc, s21_memchr_test);
  tcase_add_test(tc, s21_memcmp_test);
  tcase_add_test(tc, s21_memcpy_test);
  tcase_add_test(tc, s21_memset_test);
  tcase_add_test(tc, s21_strncpy_test);
  tcase_add_test(tc, s21_strcspn_test);
  tcase_add_test(tc, s21_strtok_test);
  tcase_add_test(tc, s21_strncat_test);
  tcase_add_test(tc, s21_strstr_test);
  tcase_add_test(tc, s21_strerror_test);
  tcase_add_test(tc, s21_strncmp_test);

  suite_add_tcase(s, tc);
  return s;
}
