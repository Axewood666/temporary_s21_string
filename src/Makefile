cc=gcc
flags=-Wall -Werror -Wextra
gcov_flags=--coverage
test_files=unit_string_tests.c

SRCS := s21_string.c s21_csharp_string.c s21_strerror.c
OBJS := $(SRCS:.c=.o)
GCOV_OBJS := $(SRCS:.c=_gcov.o)

files_for_report=*.gcno *.gcda  test_with_gcov gcov_s21_string.a

OS_NAME:=$(shell uname -s)
ifeq ($(OS_NAME), Linux)
	check_flags=-lcheck -lm -lsubunit
endif
ifeq ($(OS_NAME), Darwin)
	check_flags=-lcheck
endif

rebuild: clean all

all: test gcov_report

clean:
	rm -f $(OBJS) *.a test $(files_for_report) $(test_files) $(GCOV_OBJS)
	rm -rf report gcov_report

s21_string.a: $(OBJS)
	ar rc s21_string.a $(OBJS)
	rm -f $(OBJS)

test: s21_string.a $(test_files)
	$(cc) $(flags) $(test_files) s21_string.a $(check_flags) -o test

unit_string_tests.c: tests_s21_string.check
	checkmk clean_mode=1 tests_s21_string.check > unit_string_tests.c

unit_sprintf_tests.c: tests_s21_string.check
	checkmk clean_mode=1 tests_s21_sprintf.check > unit_sprintf_tests.c

s21_string_gcov.a: $(GCOV_OBJS)
	ar rc s21_string_gcov.a $(GCOV_OBJS)
	rm -f $(GCOV_OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

%_gcov.o: %.c
	$(cc) $(flags) $(gcov_flags) -c $< -o $@

sscanf:
	gcc -Wall -Werror -Wextra -std=c11 -o test s21_sscanf.c
	./test
	rm test

sprintf: s21_string.a
	$(cc) -o test s21_sprintf/s21_sprintf.c s21_string.a
	./test

gcov_report: s21_string_gcov.a $(test_files)
	mkdir report
	$(cc) $(flags) $(gcov_flags)  $(test_files) s21_string_gcov.a $(check_flags) -o test_with_gcov
	./test_with_gcov
	gcovr --html-details -o ./report/report.html --exclude unit_string_tests.c
	rm -f $(files_for_report)

gcov_report_lcov: s21_string_gcov.a $(test_files)
	$(cc) $(flags) $(gcov_flags)  $(test_files)  s21_string_gcov.a $(check_flags) -o test_with_gcov
	./test_with_gcov
	lcov --rc branch_coverage=1 -d . -o s21_string_coverage.info -c
	genhtml --branch-coverage s21_string_coverage.info --output-directory gcov_report
	rm -f s21_string_coverage.info $(files_for_report)