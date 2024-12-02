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
s21_string_lib_name=s21_string

rebuild: clean all

all: test gcov_report

clean:
	rm -f *.o *.a test test_with_gcov *.gcno *.gcda s21_string_coverage.info tests.c *.gcov
	rm -rf gcov_report

gcov_report: gcov_$(s21_string_lib_name).a tests.c
	$(cc) $(flags) $(gcov_flags)  tests.c -L. -l gcov_$(s21_string_lib_name) $(check_flags) -o test_with_gcov
	./test_with_gcov
	lcov --rc lcov_branch_coverage=1 -d . -o s21_string_coverage.info -c
	genhtml --branch-coverage s21_string_coverage.info --output-directory gcov_report
	rm -f *.gcno *.gcda s21_string_coverage.info test_with_gcov

test: s21_string.a tests.c
	$(cc) $(flags) tests.c -L. -l $(s21_string_lib_name) $(check_flags) -o test

tests.c: tests_s21_string.check
	checkmk clean_mode=1 tests_s21_string.check > tests.c

s21_string.a: s21_string.o
	ar rc lib$(s21_string_lib_name).a s21_string.o
gcov_$(s21_string_lib_name).a: gcov_s21_string.o
	ar rc libgcov_$(s21_string_lib_name).a gcov_s21_string.o

s21_string.o: s21_string.c
	$(cc) $(flags) -c s21_string.c
gcov_s21_string.o: s21_string.c
	$(cc) $(flags) $(gcov_flags) -c s21_string.c -o gcov_s21_string.o