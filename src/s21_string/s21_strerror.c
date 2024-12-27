#include "s21_strerror.h"

#include "../s21_string.h"

char *s21_strerror(int errnum) {
  static char errors[ERRORS_COUNT][MAX_SIZE_ERROR] = ERRORS;
  static char undef_error[MAX_SIZE_ERROR];
  char *error;
  if (errnum >= 0 && errnum < ERRORS_COUNT) {
    error = errors[errnum];
  } else {
    s21_sprintf(undef_error, UNDEF_ERROR, errnum);
    error = undef_error;
  }
  return error;
}