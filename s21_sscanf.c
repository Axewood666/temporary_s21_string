#include <stdio.h>
#include <stdarg.h>


void skip_spaces(const char **input) {
    while (**input == ' ') {
        (*input)++;
    }
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
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

// Handlers for specific specifiers
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

int parse_int_with_base(const char **buffer){
    int base = 10;
    int number = 0;
    skip_spaces(buffer);
    if(**buffer=='0'){
        (*buffer)++;
        if(**buffer=='x' || **buffer=='X'){
            base = 16;
            (*buffer)++;
        }else{
            base = 8;
        }
        
    }
    int flagBreak = 0;
    while(**buffer && !flagBreak){
        char c = **buffer;
        int digit;

        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            digit = c - 'A' + 10;
        } else {
            flagBreak = 1;
        }
        if(digit >=base){
            flagBreak = 1;
        }else{
            printf("\n%d\n",digit);
            number = number * base + digit;
            (*buffer)++;
        }
    }
    
    return number;
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

int parse_int_base_handler(const char **buffer,void *output){
    int *int_output = (int *)output;
    *int_output = (int)parse_int_with_base(buffer);
    return 1;
}
// Handler table
FormatHandler handlers[] = {
    {'d', parse_int_handler},
    {'f', parse_float_handler},
    {'c', parse_char_handler},
    {'s', parse_string_handler},
    {'i', parse_int_base_handler}
};
const int handler_count = sizeof(handlers) / sizeof(handlers[0]);

int parse_value(const char **buffer, char specifier, void *output) {
    for (int i = 0; i < handler_count; i++) {
        if (handlers[i].specifier == specifier) {
            return handlers[i].handler(buffer, output);
        }
    }
    return 0;
}

// Main sscanf function
int my_sscanf(const char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int matched_count = 0;
    const char *ptr_buf = buffer;
    const char *ptr_format = format;

    while (*ptr_format) {
        if (*ptr_format == '%') {
            ptr_format++;
            char specifier = *ptr_format;
            void *arg_ptr = va_arg(args, void *);
            int success = parse_value(&ptr_buf, specifier, arg_ptr);
            if (success) {
                matched_count++;
            } else {
                break;
            }
            ptr_format++;
        } else {
            if (*ptr_buf != *ptr_format) {
                break;
            }
            ptr_buf++;
            ptr_format++;
        }
    }

    va_end(args);
    return matched_count;
}

int main() {
    int a, b, c;
    int matched = my_sscanf("42 0x2A 052", "%i %i %i", &a, &b, &c);

    printf("Matched: %d\n", matched);
    printf("a = %d, b = %d, c = %d\n", a, b, c);
    return 0;
}
