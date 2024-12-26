#include "s21_csharp.h"

void *insert(const char *src, const char *str, s21_size_t start_index) {
  char *returnStr = s21_NULL;
  if (src != s21_NULL && str != s21_NULL) {
    s21_size_t lenSrc = s21_strlen(src);
    int lenStr = s21_strlen(str);
    if (start_index > lenSrc) {
      returnStr = s21_NULL;
    } else {
      int sumLen = lenSrc + lenStr + 1;
      char *newStr = malloc(sumLen * sizeof(char));
      if (newStr != s21_NULL) {
        s21_strncpy(newStr, src, start_index);
        s21_strncpy(newStr + start_index, str, lenStr);
        s21_strncpy(newStr + start_index + lenStr, src + start_index,
                    lenSrc - start_index);
        newStr[sumLen - 1] = '\0';
        returnStr = newStr;
      }
    }
  }
  return returnStr;
}

void *trim(const char *src, const char *trim_chars) {
  char *returnStr;
  if (src != s21_NULL && trim_chars != s21_NULL) {
    int lenSrc = s21_strlen(src);
    int start = 0, end = lenSrc;
    while (start < lenSrc && s21_strchr(trim_chars, src[start]) != NULL) {
      start++;
    }
    while (end > 0 && s21_strchr(trim_chars, src[end]) != NULL) {
      end--;
    }
    if (start >= end) {
      returnStr = malloc(sizeof(char));
      if (returnStr == s21_NULL) {
        returnStr = s21_NULL;
      }
      returnStr[0] = '\0';
    } else {
      int retLen = end - start + 1;
      returnStr = malloc(sizeof(char) * retLen);
      if (returnStr == s21_NULL) {
        returnStr = s21_NULL;
      } else {
        s21_strncpy(returnStr, src + start, retLen - 1);
        returnStr[retLen - 1] = '\0';
      }
    }
  } else {
    returnStr = s21_NULL;
  }
  return returnStr;
}

void *to_upper(const char *str) {
  char *returnStr = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);
    returnStr = calloc(len + 1, sizeof(char));
    if (returnStr != s21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        returnStr[i] = (str[i] >= 'a' && str[i] <= 'z') ? str[i] - 32 : str[i];
      }
      returnStr[len] = '\0';
    }
  }
  return returnStr;
}

void *to_lower(const char *str) {
  char *returnStr = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);
    returnStr = calloc(len + 1, sizeof(char));
    if (returnStr != s21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        returnStr[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 32 : str[i];
      }
      returnStr[len] = '\0';
    }
  }
  return returnStr;
}