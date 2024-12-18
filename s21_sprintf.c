#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int s21_sprintf(char *str, const char *format, ...);

int main()
{
    char buffer[50];

    int result = sprintf(buffer, "Hello, %ld world!", -9223372036854775807);
    printf("Result: %d\n", result);
    printf("Buffer: %s\n", buffer);
    printf("Short: %d", (short int)32768);

    return 0;
}