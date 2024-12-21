cc=gcc
flags=-Wall -Werror -Wextra
gcov_flags=--coverage
string_dir=s21_string
test_dir=tests
sprintf_dir=s21_sprintf

SRCS := $(string_dir)/s21_string.c s21_csharp_string.c $(string_dir)/s21_strerror.c $(sprintf_dir)/s21_sprintf.c
OBJS := $(SRCS:.c=.o)
GCOV_OBJS := $(SRCS:.c=_gcov.o)

test_files=$(test_dir)/unit_string_tests.c $(test_dir)/unit_sprintf_tests.c
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
	rm -f $(OBJS) *.a test_s21_sprintf test_s21_string $(files_for_report) $(test_files) $(GCOV_OBJS)
	rm -rf report gcov_report

s21_string.a: $(OBJS)
	ar rc s21_string.a $(OBJS)
	rm -f $(OBJS)

test: s21_string.a $(test_files)
	@echo "\n----------------Tests----------------"
	@for test_file in $(test_files) ; do \
		$(cc) $(flags) $$test_file s21_string.a $(check_flags) -o unit_test \
		&& echo "\n-------------------------\nTest $$test_file" \
		&& ./unit_test && rm -f unit_test \
		&& echo "-------------------------\n" ; \
		done
	@echo "-------------------------------------\n"

$(test_dir)/%.c: $(test_dir)/%.check
	checkmk clean_mode=1 $< > $@

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