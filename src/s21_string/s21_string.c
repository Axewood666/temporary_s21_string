#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (str[len] != '\0')
    len++;
  return len;
}

char *s21_strchr(const char *str, int c) {
  int found = 0;
  char *char_ptr = (char *)str;

  while (!found && *char_ptr != '\0') {
    if (*char_ptr == c) {
      found = 1;
    } else {
      char_ptr++;
    }
  }
  if (c != '\0' && !found) {
    char_ptr = s21_NULL;
  }
  return char_ptr;
}

char *s21_strrchr(const char *str, int c) {
  char *char_ptr = (char *)str;
  char *found_char_ptr = s21_NULL;

  while (*char_ptr != '\0') {
    if (*char_ptr == c) {
      found_char_ptr = char_ptr;
    }
    char_ptr++;
  }
  if (c == '\0')
    found_char_ptr = char_ptr;
  return found_char_ptr;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  int found = 0;
  char *char_str1_ptr = (char *)str1;

  while (!found && *char_str1_ptr != '\0') {
    char *char_str2_ptr = (char *)str2;
    while (!found && *char_str2_ptr != '\0') {
      if (*char_str1_ptr == *char_str2_ptr) {
        found = 1;
      } else {
        char_str2_ptr++;
      }
    }
    if (!found)
      char_str1_ptr++;
  }
  if (!found) {
    char_str1_ptr = s21_NULL;
  }

  return char_str1_ptr;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  int found = 0;
  char *char_ptr = (char *)str;

  for (s21_size_t i = 0; !found && i < n; i++) {
    if (*char_ptr == (char)c) {
      found = 1;
    } else {
      char_ptr++;
    }
  }
  if (!found) {
    char_ptr = s21_NULL;
  }

  return (void *)char_ptr;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  unsigned char *str1_ptr = (unsigned char *)str1;
  unsigned char *str2_ptr = (unsigned char *)str2;

  for (s21_size_t i = 0; res == 0 && i < n; i++) {
    res = (int)(*str1_ptr - *str2_ptr);
    str1_ptr++;
    str2_ptr++;
  }

  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dest_ptr = (char *)dest;
  const char *src_ptr = (char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    dest_ptr[i] = src_ptr[i];
  }

  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *char_ptr = (char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    char_ptr[i] = (char)c;
  }

  return str;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  for (s21_size_t i = 0; res == 0 && i < n; i++) {
    res = (int)(*str1 - *str2);
    str1++;
    str2++;
  }

  return res;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;

  for (; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  for (; i != n; i++)
    dest[i] = '\0';

  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int found = 0;
  s21_size_t index = 0;
  while (!found && *str1 != '\0') {
    const char *str2_ptr = (const char *)str2;
    while (!found && *str2_ptr != '\0') {
      if (*str1 == *str2_ptr) {
        found = 1;
      } else {
        str2_ptr++;
      }
    }
    if (!found) {
      str1++;
      index++;
    }
  }
  return index;
}

char *s21_strtok(char *str, const char *delim) {
  static char *currentPos = s21_NULL;
  char *startToken = s21_NULL;
  if (str != s21_NULL) {
    currentPos = str;
  }
  while (currentPos != s21_NULL && *currentPos &&
         s21_strchr(delim, *currentPos)) {
    currentPos++;
  }
  if (currentPos == s21_NULL || *currentPos == '\0') {
    startToken = s21_NULL;
  } else {
    startToken = currentPos;
    while (*currentPos && !s21_strchr(delim, *currentPos)) {
      currentPos++;
    }
    if (*currentPos) {
      *currentPos++ = '\0';
    }
  }
  return startToken;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = s21_strchr(dest, '\0');
  for (s21_size_t i = 0; i < n && src[i] != '\0'; i++) {
    *ptr++ = src[i];
  }
  *ptr = '\0';
  return dest;
}

char *s21_strstr(const char *haystack, const char *needle) {
  const char *ptr = haystack;
  int isFinded = 0;
  if (*needle != '\0') {
    while ((ptr = s21_strchr(ptr, *needle)) != s21_NULL && !isFinded) {
      if (s21_strncmp(ptr, needle, s21_strlen(needle)) == 0) {
        isFinded = 1;
      } else {
        ptr++;
      }
    }
  } else {
    isFinded = 1;
  }
  if (isFinded != 1) {
    ptr = s21_NULL;
  }
  return (char *)ptr;
}