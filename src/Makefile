cc=gcc
flags=-Wall -Werror -Wextra
gcov_flags=--coverage
string_dir=s21_string
test_dir=tests
sprintf_dir=s21_sprintf

SRCS := $(string_dir)/s21_string.c $(string_dir)/s21_strerror.c $(sprintf_dir)/s21_sprintf.c
OBJS := $(SRCS:.c=.o)
GCOV_OBJS := $(SRCS:.c=_gcov.o)

test_files=$(test_dir)/test_string.c $(test_dir)/test_sprintf.c $(test_dir)/test_csharp.c
TEST_OBJS := $(test_files:.c=.o)
files_for_report=*.gcno *.gcda */*.gcno */*.gcda test_with_gcov s21_string_gcov.a

OS_NAME:=$(shell uname -s)
ifeq ($(OS_NAME), Linux)
	check_flags=-lcheck -lm -lsubunit
endif
ifeq ($(OS_NAME), Darwin)
	check_flags=-lcheck
endif

#standart
rebuild: clean all

all: test gcovr_report

clean:
	rm -f $(OBJS) $(TEST_OBJS) *.a $(files_for_report) $(GCOV_OBJS)
	rm -rf report gcov_report
#------------

#lib
s21_string.a: $(OBJS)
	ar rc s21_string.a $(OBJS)
	rm -f $(OBJS)
#------------

#tests
test: s21_string.a $(TEST_OBJS)
	@echo "\n----------------Tests----------------"
	@$(cc) $(flags) $(test_dir)/test_runner.c $(TEST_OBJS) s21_string.a $(check_flags) -o test
	@./test
	@rm test
	@echo "-------------------------------------\n"
#-------------

#gcov reports
gcov: s21_string_gcov.a $(TEST_OBJS)
	$(cc) $(flags) $(gcov_flags)  $(test_dir)/test_runner.c $(TEST_OBJS) s21_string_gcov.a $(check_flags) -o test_with_gcov
	./test_with_gcov
	rm test_with_gcov

s21_string_gcov.a: $(GCOV_OBJS)
	ar rc s21_string_gcov.a $(GCOV_OBJS)
	rm -f $(GCOV_OBJS)

gcovr_report: gcov
	rm -rf report
	mkdir report
	gcovr --html-details -o ./report/report.html --exclude $(test_dir)/test_runner.c
	rm -f $(files_for_report)

lcov_report: gcov
	lcov --rc branch_coverage=1 -d . -o s21_string_coverage.info -c
	genhtml --branch-coverage s21_string_coverage.info --output-directory gcov_report
	rm -f s21_string_coverage.info $(files_for_report)
#---------------

#for obj
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

%_gcov.o: %.c
	$(cc) $(flags) $(gcov_flags) -c $< -o $@

$(test_dir)/%.o: $(test_dir)/%.c
	$(CC) $(FLAGS) -c $< -o $@
#---------------

#trash
sscanf:
	gcc -Wall -Werror -Wextra -std=c11 -o test s21_sscanf.c
	./test
	rm test

sprintf: s21_string.a
	$(CC) $(FLAGS) -o test s21_sprintf/s21_sprintf.c s21_string.a
	./test

debug: s21_string.a
	$(CC) $(FLAGS) -g -o test s21_sprintf/s21_sprintf.c s21_string.a

cs: s21_string.a
	$(CC) $(FLAGS) -o test s21_csharp/s21_csharp_string.c s21_string.a
	./test
