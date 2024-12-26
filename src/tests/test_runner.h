#include <check.h>
#include <stdio.h>

Suite* test_string(void);
Suite* test_sprintf(void);
Suite* test_csharp(void);

#define TEST_FUNCS test_string(), test_sprintf(), test_csharp()