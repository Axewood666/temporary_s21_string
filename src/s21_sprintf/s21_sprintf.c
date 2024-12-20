#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

int s21_sprintf(char *str, char *format, ...);
void intToStr(int num, char *str);
int main() {
  char buffer1[50];
  char buffer2[50];
  int number = 0;
  scanf("%d", &number);

  s21_sprintf(buffer1, "%d", number);
  sprintf(buffer2, "%d", number);

  printf("%s\n%s", buffer1, buffer2);
  return 0;
}
int s21_sprintf(char *str, char *format, ...) {
  int d;
  double f;
  va_list factor;            // указатель на необязательный параметр
  va_start(factor, format);  // устанавливаем указатель

  for (char *c = format; *c; c++) {
    if (*c != '%') {
      printf("%c", *c);
    } else {
      switch (*++c)  // если символ - %, то переходим к следующему символу
      {
        case 'd':
          d = va_arg(factor, int);
          char buffer[12];
          intToStr(d, buffer);
          s21_strncat(str, buffer, 11);
          break;
        case 'f':
          f = va_arg(factor, double);
          printf("%.2lf", f);
          break;
        default:
          printf("%c", *c);
      }
    }
  }
  va_end(factor);
  return 0;
}

void intToStr(int num, char *str) {
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