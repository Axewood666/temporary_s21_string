#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list factor;
  va_start(factor, format);

  int buffer_index = 0;
  for (int i = 0; format[i] != '\0'; i++) {
    if (format[i] == '%') {
      handle_specifiers(str, &buffer_index, format, &i, &factor);
    } else {
      str[buffer_index++] = format[i];
      str[buffer_index] = '\0';
    }
  }
  str[buffer_index] = '\0';
  va_end(factor);
  return s21_strlen(str);
}

void handle_specifiers(char *str, int *buffer_index, const char *format, int *i,
                       va_list *args) {
  formatting info = {DEFAULT_FORMATTING};
  *i = parse_formatting(*i, format, &info);
  switch (info.specifier) {
    case INT:
      handle_d_specifier(str, buffer_index, &info, args);
      break;
    case CHAR:
      handle_c_specifier(str, buffer_index, &info, args);
      break;
    case STRING:
      handle_s_specifier(str, buffer_index, &info, args);
      break;
    case FLOAT:
      handle_f_specifier(str, buffer_index, &info, args);
      break;
    case UNSIGNED:
      handle_u_specifier(str, buffer_index, &info, args);
      break;
    case '%':
      handle_percent_specifier(str, buffer_index, &info);
      break;
  }
}

int parse_formatting(int index, const char *format_str, formatting *infoSpec) {
  for (++index; s21_strchr(FLAGS, format_str[index]); index++) {
    (infoSpec->flags)[FLAGS_COUNT -
                      s21_strlen(s21_strchr(FLAGS, format_str[index]))] = YES;
  }
  for (; s21_strchr(NUMBERS, format_str[index]); index++) {
    infoSpec->width = (infoSpec->width * 10) + (format_str[index] - '0');
  }
  if (format_str[index] == '.') {
    infoSpec->precision = DEFAULT_PRECISION + 1;
    for (++index; s21_strchr(NUMBERS, format_str[index]); index++) {
      infoSpec->precision =
          (infoSpec->precision * 10) + (format_str[index] - '0');
    }
  }
  if (s21_strchr(LENGTH, format_str[index])) {
    infoSpec->length = format_str[index++];
  }
  if (s21_strchr(SPECIFIERS, format_str[index])) {
    infoSpec->specifier = format_str[index];
  }
  if (infoSpec->specifier == FLOAT &&
      infoSpec->precision == DEFAULT_PRECISION) {
    infoSpec->precision = DEFAULT_PRECISION_FLOAT;
  }
  return index;
}

void handle_d_specifier(char *buffer, int *buffer_index, formatting *spec,
                        va_list *args) {
  int number;
  long int long_number;
  short int short_number;
  char number_string[NUMBER_SIZE] = {0};

  if (spec->length == LONG) {
    long_number = va_arg(*args, long int);
    long_int_to_string_unsign(long_number, number_string);
  } else if (spec->length == SHORT) {
    short_number = (short)va_arg(*args, int);
    short_int_to_string_unsign(short_number, number_string);
  } else {
    number = va_arg(*args, int);
    int_to_string_unsign(number, number_string);
  }

  int length = s21_strlen(number_string);

  precision_handling_int_specifiers(number_string, &length, spec->precision);

  flags_handling_sign_numbers_specifiers(number_string, number, &length,
                                         spec->flags);

  width_handling_specifiers(number_string, &length, spec->width,
                            spec->flags[MINUS_FLAG]);

  s21_strncat(buffer, number_string, length);
  *buffer_index += length;
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

void flags_handling_sign_numbers_specifiers(char *number_string, int number,
                                            int *length, char *flags) {
  if (number > 0 && flags[1] == YES) {
    for (int i = *length; i >= 0; i--) {
      number_string[i + 1] = number_string[i];
    }
    number_string[0] = PLUS;
    (*length)++;
  } else if (number > 0 && flags[PLUS_FLAG] == NO && flags[SPACE_FLAG] == YES) {
    for (int i = *length; i >= 0; i--) {
      number_string[i + 1] = number_string[i];
    }
    number_string[0] = SPACE;
    (*length)++;
  } else if (number < 0) {
    for (int i = *length; i >= 0; i--) {
      number_string[i + 1] = number_string[i];
    }
    number_string[0] = MINUS;
    (*length)++;
  }
}

void width_handling_specifiers(char *number_string, int *length, int width,
                               char minus_flag) {
  if (width > *length && minus_flag == YES) {
    for (int i = *length; i < width; i++, (*length)++) {
      number_string[i] = SPACE;
    }
  } else if (width > *length) {
    for (int i = *length; i >= 0; i--) {
      number_string[i + width - *length] = number_string[i];
    }

    s21_memset(number_string, SPACE, width - *length);
    *length = width;
  }
}

void handle_c_specifier(char *buffer, int *buffer_index, formatting *spec,
                        va_list *args) {
  char symbol[CHAR_SIZE];
  symbol[0] = (char)va_arg(*args, int);
  int length = 1;
  width_handling_specifiers(symbol, &length, spec->width,
                            spec->flags[MINUS_FLAG]);

  s21_strncat(buffer, symbol, length);
  *buffer_index += length;
}

void handle_s_specifier(char *buffer, int *buffer_index, formatting *spec,
                        va_list *args) {
  char *str = va_arg(*args, char *);
  char buffer_for_str[STRING_SIZE];
  int length = s21_strlen(str);
  if (spec->precision >= 0 && spec->precision < length) {
    length = spec->precision;
  }
  s21_strncpy(buffer_for_str, str, length);
  width_handling_specifiers(buffer_for_str, &length, spec->width,
                            spec->flags[MINUS_FLAG]);
  s21_strncat(buffer, buffer_for_str, length);
  *buffer_index += length;
}

void handle_f_specifier(char *buffer, int *buffer_index, formatting *spec,
                        va_list *args) {
  char number_str[NUMBER_SIZE];
  double number = va_arg(*args, double);
  int length = float_to_string(number, number_str, spec->precision);
  flags_handling_sign_numbers_specifiers(number_str, number, &length,
                                         spec->flags);
  width_handling_specifiers(number_str, &length, spec->width,
                            spec->flags[MINUS_FLAG]);
  s21_strncat(buffer, number_str, length);
  *buffer_index += length;
}

int float_to_string(double number, char *str, int precision) {
  int i = 0;
  if (number < 0) number *= -1;
  number = round_to_precision(number, precision);
  int int_part = (int)number;
  double fractional_part = number - int_part;
  char buffer_int_part[NUMBER_SIZE];

  if (int_part == 0) {
    buffer_int_part[i++] = '0';
  } else {
    while (int_part > 0) {
      buffer_int_part[i++] = (int_part % 10) + '0';
      int_part /= 10;
    }
  }
  if (number < 0) {
    buffer_int_part[i++] = '-';
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

double round_to_precision(double number, int precision) {
  double factor = pow(10, precision);
  return round(number * factor) / factor;
}

void handle_u_specifier(char *buffer, int *buffer_index, formatting *spec,
                        va_list *args) {
  unsigned int number;
  unsigned long int long_number;
  unsigned short int short_number;
  char number_string[NUMBER_SIZE] = {0};

  if (spec->length == LONG) {
    long_number = va_arg(*args, unsigned long int);
    long_int_to_string_unsign(long_number, number_string);
  } else if (spec->length == SHORT) {
    short_number = (short)va_arg(*args, unsigned int);
    short_int_to_string_unsign(short_number, number_string);
  } else {
    number = va_arg(*args, unsigned int);
    int_to_string_unsign(number, number_string);
  }

  int length = s21_strlen(number_string);

  precision_handling_int_specifiers(number_string, &length, spec->precision);

  width_handling_specifiers(number_string, &length, spec->width,
                            spec->flags[MINUS_FLAG]);

  s21_strncat(buffer, number_string, length);
  *buffer_index += length;
}

void handle_percent_specifier(char *buffer, int *buffer_index,
                              formatting *spec) {
  char percent_str[STRING_SIZE] = {0};
  percent_str[0] = '%';
  int length = 1;
  width_handling_specifiers(percent_str, &length, spec->width,
                            spec->flags[MINUS_FLAG]);
  s21_strncat(buffer, percent_str, length);
  *buffer_index += length;
}