#include "s21_csharp.h"

void *insert(const char *src, const char *str, s21_size_t start_index) {
  char *return_str = s21_NULL;
  if (src != s21_NULL && str != s21_NULL) {
    s21_size_t len_src = s21_strlen(src);
    int len_str = s21_strlen(str);
    if (start_index > len_src) {
      return_str = s21_NULL;
    } else {
      int sum_len = len_src + len_str + 1;
      char *new_str = malloc(sum_len * sizeof(char));
      if (new_str != s21_NULL) {
        s21_strncpy(new_str, src, start_index);
        s21_strncpy(new_str + start_index, str, len_str);
        s21_strncpy(new_str + start_index + len_str, src + start_index,
                    len_src - start_index);
        new_str[sum_len - 1] = '\0';
        return_str = new_str;
      }
    }
  }
  return return_str;
}

void *trim(const char *src, const char *trim_chars) {
  char *return_str;
  if (src != s21_NULL && trim_chars != s21_NULL) {
    int len_src = s21_strlen(src);
    int start = 0, end = len_src;
    while (start < len_src && s21_strchr(trim_chars, src[start]) != NULL) {
      start++;
    }
    while (end > 0 && s21_strchr(trim_chars, src[end]) != NULL) {
      end--;
    }
    if (start >= end) {
      return_str = malloc(sizeof(char));
      if (return_str == s21_NULL) {
        return_str = s21_NULL;
      }
      return_str[0] = '\0';
    } else {
      int ret_len = end - start + 1;
      return_str = malloc(sizeof(char) * ret_len);
      if (return_str == s21_NULL) {
        return_str = s21_NULL;
      } else {
        s21_strncpy(return_str, src + start, ret_len);
        return_str[ret_len + 1] = '\0';
      }
    }
  } else {
    return_str = s21_NULL;
  }
  return return_str;
}

void *to_upper(const char *str) {
  char *return_str = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);
    return_str = calloc(len + 1, sizeof(char));
    if (return_str != s21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        return_str[i] = (str[i] >= 'a' && str[i] <= 'z') ? str[i] - 32 : str[i];
      }
      return_str[len] = '\0';
    }
  }
  return return_str;
}

void *to_lower(const char *str) {
  char *return_str = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);
    return_str = calloc(len + 1, sizeof(char));
    if (return_str != s21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        return_str[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 32 : str[i];
      }
      return_str[len] = '\0';
    }
  }
  return return_str;
}