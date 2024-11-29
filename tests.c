#include <string.h>
#include <check.h>
#include "s21_string.h"

START_TEST(test_s21_strlen) {
    char* str = "";
    ck_assert_uint_eq(s21_strlen(str), strlen(str));

    char* str1 = "Hello";
    ck_assert_uint_eq(s21_strlen(str1), strlen(str1));
    
    char* str2 = "PRivet\nkakdela?bu, ispugalsa?";
    ck_assert_uint_eq(s21_strlen(str2), strlen(str2));
    
    char* str3 = "a";
    ck_assert_uint_eq(s21_strlen(str3), strlen(str3));
}
END_TEST

START_TEST(test_s21_strchr) {
    char* str = "";
    ck_assert_ptr_eq(s21_strchr(str, 's'), strchr(str, 's'));
    
    char* str2 = "PRivet\nkakdela?bu, ispugalsa?";
    ck_assert_ptr_eq(s21_strchr(str2, '\n'), strchr(str2, '\n'));
    ck_assert_ptr_eq(s21_strchr(str2, 'P'), strchr(str2, 'P'));
    ck_assert_ptr_eq(s21_strchr(str2, 'z'), strchr(str2, 'z'));
    
    char* str3 = "abcde";
    ck_assert_ptr_eq(s21_strchr(str3, 'e'), strchr(str3, 'e'));
}
END_TEST

START_TEST(test_s21_strrchr) {
    char* str = "sssssssssssls";
    ck_assert_ptr_eq(s21_strrchr(str, 's'), strrchr(str, 's'));
    ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
    ck_assert_ptr_eq(s21_strrchr(str, '\n'), strrchr(str, '\n'));
    
    char* str2 = "PRivet\nkakdela?bu, ispugalsa?\n";
    ck_assert_ptr_eq(s21_strrchr(str2, '\n'), strrchr(str2, '\n'));
    
    char* str3 = "abcde";
    ck_assert_ptr_eq(s21_strrchr(str3, 'e'), strrchr(str3, 'e'));
}
END_TEST

START_TEST(test_s21_strpbrk) {
    char* str = "1234567890";
    ck_assert_ptr_eq(s21_strpbrk(str, "74567"), strpbrk(str, "74567"));
    ck_assert_ptr_eq(s21_strpbrk(str, "sadxzP"), strpbrk(str, "sadxzP"));
    ck_assert_ptr_eq(s21_strpbrk(str, "xyz"), strpbrk(str, "xyz"));
    
    char* str2 = "PRivet\nkakdela?bu, ispugalsa?";
    ck_assert_ptr_eq(s21_strpbrk(str2, "sadxzP"), strpbrk(str2, "sadxzP"));
    ck_assert_ptr_eq(s21_strpbrk(str2, "nz"), strpbrk(str2, "nz"));
    
    char* str3 = "abcdef";
    ck_assert_ptr_eq(s21_strpbrk(str3, "def"), strpbrk(str3, "def"));
}
END_TEST

START_TEST(test_s21_memchr) {
    
    char* str = "l";
    ck_assert_ptr_eq(s21_memchr(str, 's', 1), memchr(str, 's', 1));
    ck_assert_ptr_eq(s21_memchr(str, 'l', 1), memchr(str, 'l', 1));

    
    char* str2 = "PRivet\nkakdela?bu, ispugalsa?";
    ck_assert_ptr_eq(s21_memchr(str2, '\n', strlen(str2)), memchr(str2, '\n', strlen(str2)));
    ck_assert_ptr_eq(s21_memchr(str2, 'P', 1), memchr(str2, 'P', 1));
    ck_assert_ptr_eq(s21_memchr(str2, 'P', 0), memchr(str2, 'P', 0));
  
    char* str3 = "abcdef";
    ck_assert_ptr_eq(s21_memchr(str3, 'c', 6), memchr(str3, 'c', 6));
}
END_TEST
   
Suite* s21_string_suite() {
    Suite *s;
    TCase *tc_core;
    s = suite_create("s21_string");

    tc_core = tcase_create("strlen");
    tcase_add_test(tc_core, test_s21_strlen);
    suite_add_tcase(s, tc_core);

    tc_core = tcase_create("strchr");
    tcase_add_test(tc_core, test_s21_strchr);
    suite_add_tcase(s, tc_core);

    tc_core = tcase_create("strrchr");
    tcase_add_test(tc_core, test_s21_strrchr);
    suite_add_tcase(s, tc_core);

    tc_core = tcase_create("strpbrk");
    tcase_add_test(tc_core, test_s21_strpbrk);
    suite_add_tcase(s, tc_core);

    tc_core = tcase_create("memchr");
    tcase_add_test(tc_core, test_s21_memchr);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(){
    Suite *s;
    SRunner *sr;
    s = s21_string_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    srunner_free(sr);
}
