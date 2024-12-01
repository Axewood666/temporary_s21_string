#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  if (str == s21_NULL)
    return 0;
  s21_size_t len = 0;
  while (str[len] != '\0')
    len++;
  return len;
}

char *s21_strchr(const char *str, int c) {
  if (str == s21_NULL)
    return s21_NULL;

  int is_find = 0;
  char *char_ptr = (char *)str;

  while (!is_find && *char_ptr != '\0') {
    if (*char_ptr == c) {
      is_find = 1;
    } else {
      char_ptr++;
    }
  }
  if (!is_find) {
    char_ptr = s21_NULL;
  }

  return char_ptr;
}

char *s21_strrchr(const char *str, int c) {
  if (str == s21_NULL)
    return s21_NULL;

  char *char_ptr = (char *)str;
  char *found_char_ptr = s21_NULL;

  while (*char_ptr != '\0') {
    if (*char_ptr == c) {
      found_char_ptr = char_ptr;
    }
    char_ptr++;
  }
  return found_char_ptr;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  if (str1 == s21_NULL || str2 == s21_NULL)
    return s21_NULL;

  int is_find = 0;
  char *char_str1_ptr = (char *)str1;

  while (!is_find && *char_str1_ptr != '\0') {
    char *char_str2_ptr = (char *)str2;
    while (!is_find && *char_str2_ptr != '\0') {
      if (*char_str1_ptr == *char_str2_ptr) {
        is_find = 1;
      } else {
        char_str2_ptr++;
      }
    }
    if (!is_find)
      char_str1_ptr++;
  }
  if (!is_find) {
    char_str1_ptr = s21_NULL;
  }

  return char_str1_ptr;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  if (str == s21_NULL)
    return s21_NULL;

  int is_find = 0;
  char *char_ptr = (char *)str;

  for (s21_size_t i = 0; !is_find && i < n; i++) {
    if (*char_ptr == c) {
      is_find = 1;
    } else {
      char_ptr++;
    }
  }
  if (!is_find) {
    char_ptr = s21_NULL;
  }

  return (void *)char_ptr;
}