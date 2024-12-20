cc=gcc
flags=-Wall -Werror -Wextra
gcov_flags=--coverage
OS_NAME:=$(shell uname -s)
ifeq ($(OS_NAME), Linux)
	check_flags=-lcheck -lm -lsubunit
endif
ifeq ($(OS_NAME), Darwin)
	check_flags=-lcheck
endif
test_files=unit_tests.c
files_for_report=*.gcno *.gcda  test_with_gcov gcov_s21_string.a gcov_s21_string.o 

rebuild: clean all

all: test gcov_report

clean:
	rm -f *.o *.a test $(files_for_report) $(test_files)
	rm -rf report gcov_report

s21_string.a: s21_string.o s21_csharp_string.o
	ar rc s21_string.a s21_string.o s21_csharp_string.o

test: s21_string.a $(test_files)
	$(cc) $(flags) $(test_files) s21_string.a $(check_flags) -o test

gcov_report: gcov_s21_string.a $(test_files)
	mkdir report
	$(cc) $(flags) $(gcov_flags)  $(test_files) gcov_s21_string.a $(check_flags) -o test_with_gcov
	./test_with_gcov
	gcovr --html-details -o ./report/report.html --exclude unit_tests.c
	rm -f $(files_for_report)

gcov_report_lcov: gcov_s21_string.a $(test_files)
	$(cc) $(flags) $(gcov_flags)  $(test_files)  gcov_s21_string.a $(check_flags) -o test_with_gcov
	./test_with_gcov
	lcov --rc branch_coverage=1 -d . -o s21_string_coverage.info -c
	genhtml --branch-coverage s21_string_coverage.info --output-directory gcov_report
	rm -f s21_string_coverage.info $(files_for_report)

unit_tests.c: tests_s21_string.check
	checkmk clean_mode=1 tests_s21_string.check > unit_tests.c

gcov_s21_string.a: gcov_s21_string.o gcov_s21_csharp_string.o
	ar rc gcov_s21_string.a gcov_s21_string.o gcov_s21_csharp_string.o

s21_string.o: s21_string.c
	$(cc) $(flags) -c s21_string.c

gcov_s21_string.o: s21_string.c
	$(cc) $(flags) $(gcov_flags) -c s21_string.c -o gcov_s21_string.o

s21_csharp_string.o: s21_csharp_string.c
	$(cc) $(flags) -c s21_csharp_string.c

gcov_s21_csharp_string.o: s21_csharp_string.c
	$(cc) $(flags) $(gcov_flags) -c s21_csharp_string.c -o gcov_s21_csharp_string.o


sscanf:
	gcc -Wall -Werror -Wextra -std=c11 -o test s21_sscanf.c
	./test
	rm test

sprintf:
	gcc -Wall -Werror -Wextra -std=c11 -o test s21_sprintf/s21_sprintf.c
	./test
	rm test