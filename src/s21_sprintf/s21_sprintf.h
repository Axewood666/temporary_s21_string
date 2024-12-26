#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

typedef struct {
  char flag[3];
  int width;
  int precision;
  char length;
  char specifier;
} FormatSpec;

int s21_sprintf(char *str, const char *format, ...);
int parse_formatting(int index, char *format_str, FormatSpec *infoSpec);
void handle_d_specifier(char *buffer, int *buffer_index, FormatSpec *spec,
                        va_list *args);
void handle_c_specifier(char *buffer, int *buffer_index, FormatSpec *spec,
                        va_list *args);
void handle_s_specifier(char *buffer, int *buffer_index, FormatSpec *spec,
                        va_list *args);
void int_to_string_unsign(int num, char *str);
void long_int_to_string_unsign(long int num, char *str);
void short_int_to_string_unsign(short int num, char *str);
void precision_handling_int_specifiers(char *number_string, int *length,
                                       int precision);
void flags_handling_int_specifiers(char *number_string, int number, int *length,
                                   char *flags);
void width_handling_int_specifiers(char *number_string, int *length, int width,
                                   char flag);