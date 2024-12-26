#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"
void *insert(const char *src, const char *str, s21_size_t start_index);
void *trim(const char *src, const char *trim_chars);
void *to_upper(const char *str);
void *to_lower(const char *str);