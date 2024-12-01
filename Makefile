cc=gcc
flags=-Wall -Werror -Wextra
gcov_flags=--coverage
check_flags=-lcheck -lm -lsubunit
s21_string_lib_name=s21_string.a
link_lib=-L. -l:$(s21_string_lib_name)

rebuild: clean all

all: test

clean:
	rm -f *.o *.a test test_with_gcov *.gcno *.gcda s21_string_coverage.info tests.c
	rm -rf gcov_report

gcov_report: s21_string.c tests.c
	$(cc) $(flags) $(gcov_flags) tests.c s21_string.c $(check_flags) -o test_with_gcov
	./test_with_gcov
	lcov --capture --directory . --output-file s21_string_coverage.info
	genhtml s21_string_coverage.info --output-directory gcov_report

test: $(s21_string_lib_name) tests.c
	$(cc) $(flags) tests.c $(link_lib) $(check_flags) -o test

tests.c: tests_s21_string.check
	checkmk clean_mode=1 tests_s21_string.check > tests.c

$(s21_string_lib_name): s21_string.o
	ar rc $(s21_string_lib_name) s21_string.o

s21_string.o: s21_string.c
	$(cc) $(flags) -c s21_string.c