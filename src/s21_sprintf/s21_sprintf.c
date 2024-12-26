#include "s21_sprintf.h"

int main() {
  char buffer[100];
  char buffer1[100];
  s21_sprintf(buffer, "Chlen vot stok .%+10.2d. sm", 123);
  sprintf(buffer1, "Chlen vot stok .%+10.2d. sm", 123);
  printf("%s\n", buffer);
  printf("%s\n", buffer1);
  return 0;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list factor;
  va_start(factor, format);
  char *temp_format = (char *)calloc(s21_strlen(format), sizeof(char));
  s21_strncpy(temp_format, format, s21_strlen(format));

  int buffer_index = 0;
  for (int i = 0; temp_format[i] != '\0'; i++) {
    if (temp_format[i] == '%') {
      FormatSpec info = {"nnn", 0, -1, 'n', 'n'};
      i = parse_formatting(i, temp_format, &info);
      if (info.specifier == 'd') {
        handle_d_specifier(str, &buffer_index, &info, &factor);
      }
    } else {
      str[buffer_index++] = format[i];  // Копирование обычных символов
    }
  }
  str[buffer_index] = '\0';  // Завершение строки
  va_end(factor);
  return 1;
}

int parse_formatting(int index, char *format_str, FormatSpec *infoSpec) {
  // парсинг флагов
  for (++index; s21_strchr("-+ ", format_str[index]); index++) {
    (infoSpec->flag)[3 - s21_strlen(s21_strchr("-+ ", format_str[index]))] =
        'y';
  }
  // парсинг длины
  for (; s21_strchr("0123456789", format_str[index]); index++) {
    infoSpec->width = (infoSpec->width * 10) + (format_str[index] - '0');
  }
  // парсинг длины после запятой
  if (format_str[index] == '.') {
    infoSpec->precision = 0;
    for (++index; s21_strchr("0123456789", format_str[index]); index++) {
      infoSpec->precision =
          (infoSpec->precision * 10) + (format_str[index] - '0');
    }
  }
  // парсинг флагов h и l
  if (s21_strchr("hl", format_str[index])) {
    infoSpec->length = format_str[index++];
  }
  // парсинг спецификаторов c, d, f, s, u
  if (s21_strchr("cdfsu", format_str[index])) {
    infoSpec->specifier = format_str[index];
  }
  return index;
}

void handle_d_specifier(char *buffer, int *buffer_index, FormatSpec *spec,
                        va_list *args) {
  int number;
  long int long_number;
  short int short_number;
  char number_string[100];

  // Обработка длины
  if (spec->length == 'l') {
    long_number = va_arg(*args, long int);
    long_int_to_string_unsign(long_number, number_string);
  } else if (spec->length == 'h') {
    short_number = (short)va_arg(*args, int);
    short_int_to_string_unsign(short_number, number_string);
  } else {
    number = va_arg(*args, int);
    int_to_string_unsign(number, number_string);
  }

  int length = s21_strlen(number_string);

  // Обработка точности
  precision_handling_int_specifiers(number_string, &length, spec->precision);

  // Обработка флагов
  flags_handling_int_specifiers(number_string, number, &length, spec->flag);

  // Обработка ширины
  width_handling_int_specifiers(number_string, &length, spec->width,
                                spec->flag[0]);

  s21_strncat(buffer, number_string, length);
  *buffer_index += length;
}

void precision_handling_int_specifiers(char *number_string, int *length,
                                       int precision) {
  if (precision > 0) {
    if (precision > *length) {
      int zeros_count = precision - *length;
      for (int i = *length; i >= 0; i--) {
        number_string[i + zeros_count] = number_string[i];
      }
      s21_memset(number_string, '0', zeros_count);
      *length += zeros_count;
    }
  }
}

void flags_handling_int_specifiers(char *number_string, int number, int *length,
                                   char *flags) {
  if (number > 0 && flags[1] == 'y') {
    for (int i = *length; i >= 0; i--) {
      number_string[i + 1] = number_string[i];
    }
    number_string[0] = '+';
    (*length)++;
  } else if (number > 0 && flags[1] == 'n' && flags[2] == 'y') {
    for (int i = *length; i >= 0; i--) {
      number_string[i + 1] = number_string[i];
    }
    number_string[0] = ' ';
    (*length)++;
  } else if (number < 0) {
    for (int i = *length; i >= 0; i--) {
      number_string[i + 1] = number_string[i];
    }
    number_string[0] = '-';
    (*length)++;
  }
}

void width_handling_int_specifiers(char *number_string, int *length, int width,
                                   char flag) {
  if (width > *length && flag == 'y') {
    for (int i = *length; i < width; i++, (*length)++) {
      number_string[i] = ' ';
    }
  } else if (width > *length) {
    for (int i = *length; i >= 0; i--) {
      number_string[i + width - *length] = number_string[i];
    }

    s21_memset(number_string, ' ', width - *length);
    *length = width;
  }
}

void int_to_string_unsign(int num, char *str) {
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

  str[i] = '\0';

  for (int j = 0, k = i - 1; j < k; j++, k--) {
    char temp = str[j];
    str[j] = str[k];
    str[k] = temp;
  }
}

void long_int_to_string_unsign(long int num, char *str) {
  int i = 0;
  long int sign = num;

  if (num == 0) {
    str[i++] = '0';
  }

  if (num < 0) num = -num;

  while (num > 0) {
    str[i++] = num % 10 + '0';
    num /= 10;
  }

  str[i] = '\0';

  for (int j = 0, k = i - 1; j < k; j++, k--) {
    char temp = str[j];
    str[j] = str[k];
    str[k] = temp;
  }
}

void short_int_to_string_unsign(short int num, char *str) {
  int i = 0;
  short int sign = num;

  if (num == 0) {
    str[i++] = '0';
  }

  if (num < 0) num = -num;

  while (num > 0) {
    str[i++] = num % 10 + '0';
    num /= 10;
  }

  str[i] = '\0';

  for (int j = 0, k = i - 1; j < k; j++, k--) {
    char temp = str[j];
    str[j] = str[k];
    str[k] = temp;
  }
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