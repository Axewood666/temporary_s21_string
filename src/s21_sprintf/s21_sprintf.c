#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"


// Чек-лист
// Сделать парсер ✅
// Спецификаторы
// Флаги
// Ширина
// Точность
// Длина
// 





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





void handle_d_specifier(char *buffer, int *buffer_index, FormatSpec *spec, va_list *args){
  int number;
  char number_str[20];

  // получаем число
  if(spec->length == 'h'){
    number = (short)va_arg(*args,int);
  }else if(spec->length == 'l'){
    number  = va_arg(*args,long);
  }else{
    number  = va_arg(*args,int);
  }
  // Преобразуем число в строку
  int_to_string(number,number_str);
  // Точность
  int len = s21_strlen(number_str);
  if(spec->precision > 0){
    
    if(len < spec->precision){
      int zeros = spec->precision - len;
      for(int i = len;i>=0;i--){
        number_str[i+zeros] = number_str[i];
      }
      for(int i = 0;i<zeros;i++){
        number_str[i] = '0';
      }
    }
  }

  // знак
  if(number < 0){
    buffer[*(buffer_index)++] = '-';
  }else if(spec->flag[1] == 'y'){
    buffer[*(buffer_index)++] = '+';
  }else if(spec->flag[2] == 'y'){
    buffer[*(buffer_index)++] = ' ';
  }

  int padding = spec->width - len;
  if(padding > 0){
    if(spec->flag[0]=='y'){

      for(int i = 0;i<len;i++){
        buffer[*(buffer_index)++] = number_str[i];
      }
      for(int i = 0;i<padding;i++){
        buffer[*(buffer_index)++] = ' ';
      }

    } else{
      for (int i = 0; i < padding; i++) {
          buffer[(*buffer_index)++] = ' ';
      }
      for (int i = 0; i < len; i++) {
          buffer[(*buffer_index)++] = number_str[i];
      }
    }
  } else{
    for (int i = 0; i < len; i++) {
          buffer[(*buffer_index)++] = number_str[i];
      }
  }

}

int temp_sprintf(char *str, const char *format,...){
  
  va_list factor;
  va_start(factor, format);
  char *temp_format = (char *)calloc(s21_strlen(format), sizeof(char));
  s21_strncpy(temp_format, format, s21_strlen(format));

  int buffer_index = 0;
  for(int i = 0;temp_format[i]!='\0';i++){
    if(temp_format[i] == '%'){
      FormatSpec info = {"nnn",0,-1,'n','n'};
      i = parse_znach(i,temp_format,&info);
      if(info.specifier == 'd'){
        handle_d_specifier(str, &buffer_index, &info, &factor);
      }
    }
  }
  return 1;
}




int main() {
  char buffer[50];
  s21_sprintf(buffer, "Number: %+10d, Another: %-05d", 42, -123);
  printf("%s\n", buffer);
  return 0;
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