cc=gcc
flags=-Wall -Werror -Wextra
gcov_flags=-fprofile-arcs -ftest-coverage
check_flags=-lcheck -lm -lsubunit
s21_string_lib_name=s21_string.a
link_lib=-L. -l:$(s21_string_lib_name)

rebuild: clean all

all: test

clean:
	rm -f *.o *.a test test_with_gcov *.gcno *.gcda s21_string_coverage.info
	rm -rf gcov_report

gcov_report: gcov_$(s21_string_lib_name) tests.c
	$(cc) $(flags) $(gcov_flags) tests.c $(link_lib) $(check_flags) -o test_with_gcov
	./test_with_gcov
	lcov --capture --directory . --output-file s21_string_coverage.info
	genhtml s21_string_coverage.info --output-directory gcov_report

test: $(s21_string_lib_name) tests.c
	$(cc) $(flags) tests.c $(link_lib) $(check_flags) -o test

$(s21_string_lib_name): s21_string.o
	ar rcs $(s21_string_lib_name) s21_string.o
gcov_$(s21_string_lib_name): gcov_s21_string.o
	ar rcs $(s21_string_lib_name) gcov_s21_string.o

s21_string.o: s21_string.c
	$(cc) $(flags) -c s21_string.c
gcov_s21_string.o: s21_string.c
	$(cc) $(flags) $(gcov_flags) -c s21_string.c -o gcov_s21_string.o