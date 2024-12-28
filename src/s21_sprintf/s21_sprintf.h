#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

#define DEFAULT_FORMATTING "nnn", 0, -1, 'n', 'n'
#define DEFAULT_PRECISION_FLOAT 6
#define DEFAULT_PRECISION -1
#define FLAGS_COUNT 3
#define YES 'y'
#define NO 'n'
#define FLAGS "-+ "
#define LENGTH "hl"
#define SPECIFIERS "cdfsu%"
#define NUMBERS "0123456789"
#define FLOAT 'f'
#define INT 'd'
#define STRING 's'
#define CHAR 'c'
#define UNSIGNED 'u'
#define NUMBER_SIZE 1024
#define STRING_SIZE 1024
#define CHAR_SIZE 1024
#define LONG 'l'
#define SHORT 'h'
#define MINUS '-'
#define PLUS '+'
#define SPACE ' '

enum { MINUS_FLAG = 0, PLUS_FLAG = 1, SPACE_FLAG = 2 };

typedef struct {
  char flags[3];
  int width;
  int precision;
  char length;
  char specifier;
} formatting;

int s21_sprintf(char *str, const char *format, ...);
void handle_specifiers(char *str, int *buffer_index, const char *format, int *i,
                       va_list *factor);
int parse_formatting(int index, const char *format_str, formatting *infoSpec);
void handle_d_specifier(char *buffer, int *buffer_index, formatting *spec,
                        va_list *args);
void long_int_to_string_unsign(long int num, char *str);
void short_int_to_string_unsign(short int num, char *str);
void int_to_string_unsign(int num, char *str);
void precision_handling_int_specifiers(char *number_string, int *length,
                                       int precision);
void flags_handling_sign_numbers_specifiers(char *number_string,
                                            long int number, int *length,
                                            char *flags);
void width_handling_specifiers(char *number_string, int *length, int width,
                               char flag);
void handle_c_specifier(char *buffer, int *buffer_index, formatting *spec,
                        va_list *args);
void handle_s_specifier(char *buffer, int *buffer_index, formatting *spec,
                        va_list *args);
void handle_f_specifier(char *buffer, int *buffer_index, formatting *spec,
                        va_list *args);
int float_to_string(double number, char *str, int precision);
double round_to_precision(double number, int precision);
void handle_u_specifier(char *buffer, int *buffer_index, formatting *spec,
                        va_list *args);
void handle_percent_specifier(char *buffer, int *buffer_index,
                              formatting *spec);