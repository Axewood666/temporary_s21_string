#!/bin/bash

# Флаги для компиляции
CFLAGS="-std=c11 -Wall -Wextra -Wpedantic -Wdeprecated-declarations -Wshadow -Wstrict-prototypes -Wconversion -Wformat -Wundef"
SANITIZER_FLAGS="-fsanitize=address,undefined,leak"
COVERAGE_FLAGS="-fprofile-arcs -ftest-coverage"
SRC="s21_string.c"  # Укажи свои файлы здесь

# Флаги для cppcheck
CPPCHECK_FLAGS="--enable=all --suppress=missingIncludeSystem --inconclusive --std=c11"

# Компиляция программы с POSIX.1-2017
echo "Compiling the program with POSIX.1-2017 compliance (with _POSIX_C_SOURCE=201710L)..."
gcc $CFLAGS -D_POSIX_C_SOURCE=201710L $SRC 
if [ $? -ne 0 ]; then
    echo "Compilation with POSIX.1-2017 failed!"
    exit 1
else
    echo "Compilation with POSIX.1-2017 successful!"
fi

# Компиляция программы без POSIX (чистый C11)
echo "Compiling the program with pure C11 compliance (without _POSIX_C_SOURCE)..."
gcc $CFLAGS $SRC 
if [ $? -ne 0 ]; then
    echo "Compilation with pure C11 failed!"
    exit 1
else
    echo "Compilation with pure C11 successful!"
fi

# Запуск статического анализатора cppcheck
echo "Running static analysis with cppcheck..."
cppcheck $CPPCHECK_FLAGS $SRC
if [ $? -ne 0 ]; then
    echo "Static analysis failed!"
    exit 1
else
    echo "Static analysis completed!"
fi

# Запуск статического анализатора clang-tidy
# echo "Running additional static analysis with clang-tidy..."
# clang-tidy $SRC -- -std=c11
# if [ $? -ne 0 ]; then
#     echo "Clang-tidy analysis failed!"
#     exit 1
# else
#     echo "Clang-tidy analysis completed!"
# fi

# Компиляция программы с санитайзерами
# echo "Compiling the program with sanitizers..."
# gcc $CFLAGS $SANITIZER_FLAGS $SRC 
# if [ $? -ne 0 ]; then
#     echo "Compilation with sanitizers failed!"
#     exit 1
# else
#     echo "Compilation with sanitizers successful!"
# fi

# # Компиляция программы с покрытием кода
# echo "Compiling the program with code coverage..."
# gcc $COVERAGE_FLAGS $SRC -o s21_cat
# if [ $? -ne 0 ]; then
#     echo "Compilation with code coverage failed!"
#     exit 1
# else
#     echo "Compilation with code coverage successful!"
# fi

# FLAGS=("-A" "-b" "-e" "-E" "-n" "-s" "-t" "-T" "-u" "-v")  

# for FLAG in "${FLAGS[@]}"; do
    
#     ./s21_cat ./data-samples/555.txt $FLAG > /dev/null 2>&1

# done

# gcov s21_cat.c

# Форматирование исходного кода
echo "Running code formatting with clang-format..."
clang-format -n $SRC
echo "Code formatting completed!"

echo "Code validation finished!"
# rm a.out s21_cat s21_cat.gcno s21_cat.gcda 
#  s21_cat.c.gcov