#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

int s21_sprintf(char *str, const char *format, ...);
void int_to_string(int num, char *str);
int is_number(const char *input_char);
int is_digit(const char input_char);

typedef struct {
    char flag[3];    
    int width;         
    int precision;      
    char length;        
    char specifier;     
} FormatSpec;








int parse_znach(int index,char *format_str,FormatSpec *infoSpec){
  //парсинг флагов
  for(++index;s21_strchr("-+ ",format_str[index]);index++){
    (infoSpec->flag)[3-s21_strlen(s21_strchr("-+ ",format_str[index]))] = 'y';
  }
  //парсинг длины
  for(;s21_strchr("0123456789",format_str[index]);index++){
    infoSpec->width = (infoSpec->width * 10) + (format_str[index] - '0');
  }
  //парсинг длины после запятой
  if(format_str[index] == '.'){
    for(++index;s21_strchr("0123456789",format_str[index]);index++){
      infoSpec->precision = (infoSpec->precision * 10) + (format_str[index] - '0');
    }
  }
  //парсинг флагов h и l
  for(;s21_strchr("hl",format_str[index]);index++){
    infoSpec->length = format_str[index];
  }
  //парсинг спецификаторов c, d, f, s, u
  for(;s21_strchr("cdfsu",format_str[index]);index++){
    infoSpec->specifier = format_str[index];
  }
  return index;
}


int temp_sprintf(char *str, const char *format,...){
  
  va_list factor;
  va_start(factor, format);
  char *temp_format = (char *)calloc(s21_strlen(format), sizeof(char));
  s21_strncpy(temp_format, format, s21_strlen(format));


  for(int i = 0;temp_format[i]!='\0';i++){
    if(temp_format[i] == '%'){
      FormatSpec info = {"nnn",0,0,'n','n'};
      i = parse_znach(i,temp_format,&info);
      printf("%s\n%d\n%d\n%c\n%c",info.flag,info.width,info.precision,info.length,info.specifier);
    }
  }
  return 1;
}

int main() {
    const char Amirka[50] = "%10.3f вот такой длины прибор";
    char Amir[100];
    

    temp_sprintf(Amir, Amirka, 100.564);
    

    printf("%s\n", Amir); 
    
    return 0;
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