#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void skip_spaces(const char **input) {
  while (**input == ' ') {
    (*input)++;
  }
}

int is_digit(char c) { return c >= '0' && c <= '9'; }

int is_hex(char c) {
  return is_digit(c) || ('A' <= c && 'F' >= c) || ('a' <= c && 'f' >= c);
}

int parse_oct_handler(const char **buffer, void *output) {
  int digit = 0;
  int *number = (int *)output;
  skip_spaces(buffer);
  if (**buffer == '0') {
    (*buffer)++;
    while (is_digit(**buffer) && (**buffer != '8' || **buffer != '9')) {
      digit = digit * 8 + (**buffer - '0');
      (*buffer)++;
    }
  }
  *number = digit;
  return 1;
}

int parse_int_notSign(const char **buffer, void *output) {
  int number = 0;
  int *result = (int *)output;
  while (is_digit(**buffer)) {
    number = number * 10 + (**buffer - '0');
    (*buffer)++;
  }
  *result = number;
  return 1;
}

int parse_hex_handler(const char **buffer, void *output) {
  int number = 0;
  int *result = (int *)output;
  if (**buffer == '0' && ((*buffer)[1] == 'x' || (*buffer)[1] == 'X')) {
    (*buffer) += 2;
    while (is_hex(**buffer)) {
      int digit;
      char c = **buffer;
      if (c >= '0' && c <= '9') {
        digit = c - '0';
      } else if (c >= 'a' && c <= 'f') {
        digit = c - 'a' + 10;
      } else if (c >= 'A' && c <= 'F') {
        digit = c - 'A' + 10;
      }
      number = number * 16 + digit;
      (*buffer)++;
    }
  }

  *result = number;
  return 1;
}

int parse_int_with_base(const char **buffer) {
  int output;

  if (**buffer == '0' && ((*buffer)[1] == 'x' || (*buffer)[1] == 'X')) {
    parse_hex_handler(buffer, &output);
  } else if (**buffer == '0') {
    parse_oct_handler(buffer, &output);
  } else {
    parse_int_notSign(buffer, &output);
  }

  return output;
}

double parse_number(const char **input, int *is_integer) {
  float number = 0.0, fraction = 0.0, divisor = 1.0;
  int sign = 1;
  *is_integer = 1;

  skip_spaces(input);

  if (**input == '-') {
    sign = -1;
    (*input)++;
  } else if (**input == '+') {
    (*input)++;
  }

  while (is_digit(**input)) {
    number = number * 10 + (**input - '0');
    (*input)++;
  }

  if (**input == '.') {
    *is_integer = 0;
    (*input)++;
    while (is_digit(**input)) {
      fraction = fraction * 10 + (**input - '0');
      divisor *= 10;
      (*input)++;
    }
  }

  return sign * (number + fraction / divisor);
}

typedef int (*ParseHandler)(const char **buffer, void *output);

typedef struct {
  char specifier;
  ParseHandler handler;
} FormatHandler;

int parse_int_handler(const char **buffer, void *output) {
  int is_integer = 1;
  int *int_output = (int *)output;
  *int_output = (int)parse_number(buffer, &is_integer);
  return is_integer;
}

int parse_float_handler(const char **buffer, void *output) {
  int is_integer = 1;
  float *double_output = (float *)output;
  *double_output = parse_number(buffer, &is_integer);
  return 1;
}

int parse_char_handler(const char **buffer, void *output) {
  skip_spaces(buffer);
  char *char_output = (char *)output;
  if (**buffer != '\0') {
    *char_output = **buffer;
    (*buffer)++;
    return 1;
  }
  return 0;
}

int parse_string_handler(const char **buffer, void *output) {
  skip_spaces(buffer);
  char *str_output = (char *)output;
  while (**buffer != '\0' && **buffer != ' ') {
    *str_output++ = **buffer;
    (*buffer)++;
  }
  *str_output = '\0';
  return 1;
}

int parse_int_base_handler(const char **buffer, void *output) {
  int *int_output = (int *)output;
  *int_output = (int)parse_int_with_base(buffer);
  return 1;
}

int parse_hex_without_prefix_handler(const char **buffer, void *output) {
  unsigned long number =
      0;  // Используем unsigned long для хранения шестнадцатеричного числа
  unsigned long *result = (unsigned long *)output;
  if (**buffer == '0' && ((*buffer + 1)[0] == 'x' || (*buffer + 1)[0] == 'X')) {
    (*buffer) += 2;
  }
  while (is_hex(**buffer)) {
    int digit;
    char c = **buffer;
    if (c >= '0' && c <= '9') {
      digit = c - '0';
    } else if (c >= 'a' && c <= 'f') {
      digit = c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
      digit = c - 'A' + 10;
    }
    number = number * 16 + digit;
    (*buffer)++;
  }
  *result = number;
  return 1;
}

int parse_p_handler(const char **buffer, void *output) {
  skip_spaces(buffer);
  unsigned long
      result;  // Используем unsigned long для хранения шестнадцатеричного числа
  parse_hex_without_prefix_handler(buffer, &result);
  void **ptr_output = (void **)output;
  *ptr_output = (void *)result;  // Приводим unsigned long к void*
  return 1;
}

FormatHandler handlers[] = {
    {'d', parse_int_handler},      {'f', parse_float_handler},
    {'c', parse_char_handler},     {'s', parse_string_handler},
    {'i', parse_int_base_handler}, {'o', parse_oct_handler},
    {'u', parse_int_notSign},      {'x', parse_hex_handler},
    {'X', parse_hex_handler},      {'p', parse_p_handler}};
const int handler_count = sizeof(handlers) / sizeof(handlers[0]);

int parse_value(const char **buffer, char specifier, void *output) {
  for (int i = 0; i < handler_count; i++) {
    if (handlers[i].specifier == specifier) {
      return handlers[i].handler(buffer, output);
    }
  }
  return 0;
}

int my_sscanf(const char *buffer, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int matched_count = 0;
  const char *ptr_buf = buffer;
  const char *ptr_format = format;

  while (*ptr_format && matched_count >= 0) {
    if (*ptr_format == '%') {
      ptr_format++;
      char specifier = *ptr_format;
      if (specifier == 'n') {
        int *n_output = va_arg(args, int *);
        *n_output = ptr_buf - buffer;
      } else {
        void *arg_ptr = va_arg(args, void *);
        int success = parse_value(&ptr_buf, specifier, arg_ptr);
        (success) ? matched_count++ : matched_count * (-1);
      }
      ptr_format++;
    } else {
      if (*ptr_buf != *ptr_format) {
        matched_count = -1;
      }
      ptr_buf++;
      ptr_format++;
    }
  }

  va_end(args);
  return matched_count;
}

int main() {
  void *original_ptr = (void *)0x1A2B3C4D;
  char buffer[50];
  void *parsed_ptr;

  // Test with sprintf output
  sprintf(buffer, "%p", original_ptr);
  printf("Input string: %s\n", buffer);
  int matched = my_sscanf(buffer, "%p", &parsed_ptr);
  printf("Matched: %d\n", matched);
  printf("Parsed pointer: %p, Original pointer: %p\n", parsed_ptr,
         original_ptr);

  return 0;
}
