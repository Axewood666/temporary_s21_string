#include "s21_string.h"
#include <stdlib.h>
#include <stdio.h>
void *insert(const char *src, const char *str, size_t start_index) {
    char *returnStr = s21_NULL;
    if (src != s21_NULL && str != s21_NULL) {
        int lenSrc = s21_strlen(src);
        int lenStr = s21_strlen(str);
        if (start_index > lenSrc) {
            returnStr = s21_NULL;
        } else {
            int sumLen = lenSrc + lenStr + 1; 
            char *newStr = malloc(sumLen * sizeof(char));
            if (newStr != s21_NULL) {
                s21_strncpy(newStr, src, start_index);
                s21_strncpy(newStr + start_index, str, lenStr);
                s21_strncpy(newStr + start_index + lenStr, src + start_index, lenSrc - start_index);
                newStr[sumLen - 1] = '\0'; 
                returnStr = newStr; 
            }
        }
    }
    return returnStr; 
}

