#include "s21_sprintf.h"

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
      } else if (info.specifier == 'c') {
        handle_c_specifier(str, &buffer_index, &info, &factor);
      } else if (info.specifier == 's') {
        handle_s_specifier(str, &buffer_index, &info, &factor);
      } else if (info.specifier == 'f') {
        handle_f_specifier(str, &buffer_index, &info, &factor);
      } else if (info.specifier == 'u') {
        handle_u_specifier(str, &buffer_index, &info, &factor);
      }

    } else {
      str[buffer_index++] = format[i];
    }
  }
  str[buffer_index] = '\0';
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

  if (infoSpec->specifier == 'f' && infoSpec->precision == -1) {
    infoSpec->precision = 6;
  }
  return index;
}

void handle_f_specifier(char *buffer, int *buffer_index, FormatSpec *spec,
                        va_list *args) {
  char number_str[100];
  double number = va_arg(*args, double);
  int length = float_to_string(number, number_str, spec->precision);
  flags_handling_int_specifiers(number_str, number, &length, spec->flag);
  width_handling_int_specifiers(number_str, &length, spec->width,
                                spec->flag[0]);
  s21_strncat(buffer, number_str, length);
  *buffer_index += length;
}

void handle_c_specifier(char *buffer, int *buffer_index, FormatSpec *spec,
                        va_list *args) {
  char symbol[100];
  symbol[0] = (char)va_arg(*args, int);
  int length = 1;
  width_handling_int_specifiers(symbol, &length, spec->width, spec->flag[0]);

  s21_strncat(buffer, symbol, length);
  *buffer_index += length;
}

void handle_s_specifier(char *buffer, int *buffer_index, FormatSpec *spec,
                        va_list *args) {
  char *str = va_arg(*args, char *);
  char buffer_for_str[1024];
  int length = s21_strlen(str);
  if (spec->precision >= 0 && spec->precision < length) {
    length = spec->precision;
  }
  s21_strncpy(buffer_for_str, str, length);
  width_handling_int_specifiers(buffer_for_str, &length, spec->width,
                                spec->flag[0]);
  s21_strncat(buffer, buffer_for_str, length);
  *buffer_index += length;
}

void handle_d_specifier(char *buffer, int *buffer_index, FormatSpec *spec,
                        va_list *args) {
  int number;
  long int long_number;
  short int short_number;
  char number_string[1024] = {0};

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

void handle_u_specifier(char *buffer, int *buffer_index, FormatSpec *spec,
                        va_list *args) {
  unsigned int number;
  unsigned long int long_number;
  unsigned short int short_number;
  char number_string[1024] = {0};

  // Обработка длины
  if (spec->length == 'l') {
    long_number = va_arg(*args, unsigned long int);
    long_int_to_string_unsign(long_number, number_string);
  } else if (spec->length == 'h') {
    short_number = (short)va_arg(*args, unsigned int);
    short_int_to_string_unsign(short_number, number_string);
  } else {
    number = va_arg(*args, unsigned int);
    int_to_string_unsign(number, number_string);
  }

  int length = s21_strlen(number_string);

  // Обработка точности
  precision_handling_int_specifiers(number_string, &length, spec->precision);

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

int float_to_string(double number, char *str, int precision) {
  int int_part = (int)number;
  double fractional_part = number - int_part;
  char buffer_int_part[20];
  int i = 0;
  if (int_part == 0) {
    buffer_int_part[i++] = '0';
  } else {
    while (int_part > 0) {
      buffer_int_part[i++] = (int_part % 10) + '0';
      int_part /= 10;
    }
  }
  for (int j = i - 1; j >= 0; j--) {
    *str++ = buffer_int_part[j];
  }
  if (precision > 0) {
    *str++ = '.';
    i++;
    for (int j = 0; j < precision; j++, i++) {
      fractional_part *= 10;
      int frac_digit = (int)fractional_part;
      *str++ = frac_digit + '0';
      fractional_part -= frac_digit;
    }
  }
  return i;
}

void int_to_string_unsign(int num, char *str) {
  int i = 0;

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