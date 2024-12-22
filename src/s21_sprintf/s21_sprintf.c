#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

int s21_sprintf(char *str, const char *format, ...);
void int_to_string(int num, char *str);
int is_number(const char *input_char);
int is_digit(const char input_char);

int main() {
  char str1[10] = {0};
  char gen_str[5] = "1234";
  int res1 = sprintf(str1, "%.10s", gen_str);
  printf("%d\n%s", res1, str1);
}

int s21_sprintf(char *str, const char *format, ...) {
  // int d;
  // double f;
  // char *string;
  va_list factor;
  va_start(factor, format);
  char *temp_format = (char *)calloc(s21_strlen(format), sizeof(char));
  s21_strncpy(temp_format, format, s21_strlen(format));

  for (char *ch = temp_format; *ch; ch++) {
    if (*ch != '%') {
        } else {
    }
  }
  va_end(factor);
  if (temp_format) {
    free(temp_format);
  }

  return s21_strlen(str);
}

int is_number(const char *input_str) {
  int result = 1;
  s21_size_t i = 0;
  if (*input_str == '-') {
    i++;
  }
  for (; i < s21_strlen(input_str); i++) {
    result = is_digit(input_str[i]);
  }
  return result;
}

int is_digit(const char input_char) {
  return (input_char >= '0' && input_char <= '9');
}

void int_to_string(int num, char *str) {
  int i = 0;
  int sign = num;

  if (num == 0) {
    str[i++] = '0';
  }

  if (num < 0) num = -num;

  while (num > 0) {
    str[i++] = num % 10 + '0';
    num /= 10;
  }

  if (sign < 0) {
    str[i++] = '-';
  }

  str[i] = '\0';

  for (int j = 0, k = i - 1; j < k; j++, k--) {
    char temp = str[j];
    str[j] = str[k];
    str[k] = temp;
  }
}