cc=gcc
flags=-Wall -Werror -Wextra
gcov_flags=--coverage
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	check_flags=-lcheck -lm -lsubunit
endif
ifeq ($(UNAME_S), Darwin)
	check_flags=-lcheck
endif
s21_string_lib_name=s21_string.a

rebuild: clean all

all: test gcov_report

clean:
	rm -f *.o *.a test test_with_gcov *.gcno *.gcda s21_string_coverage.info tests.c
	rm -rf gcov_report

gcov_report: gcov_$(s21_string_lib_name) tests.c
	$(cc) $(flags) $(gcov_flags) tests.c -L. -l:gcov_$(s21_string_lib_name) $(check_flags) -o test_with_gcov
	./test_with_gcov
	lcov --capture --directory . --output-file s21_string_coverage.info
	genhtml s21_string_coverage.info --output-directory gcov_report
	rm -f *.gcno *.gcda s21_string_coverage.info test_with_gcov

test: $(s21_string_lib_name) tests.c
	$(cc) $(flags) tests.c -L. -l:$(s21_string_lib_name) $(check_flags) -o test

tests.c: tests_s21_string.check
	checkmk clean_mode=1 tests_s21_string.check > tests.c

$(s21_string_lib_name): s21_string.o
	ar rc $(s21_string_lib_name) s21_string.o
gcov_$(s21_string_lib_name): gcov_s21_string.o
	ar rc gcov_$(s21_string_lib_name) gcov_s21_string.o

s21_string.o: s21_string.c
	$(cc) $(flags) -c s21_string.c
gcov_s21_string.o: s21_string.c
	$(cc) $(flags) $(gcov_flags) -c s21_string.c -o gcov_s21_string.o