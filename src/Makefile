
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra
LDFLAGS=-g
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
LIBSOURCES=s21_matrix.c
LIBOBJECTS=$(LIBSOURCES:.c=.o)
OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECKFLAGS=-lcheck -lm -lpthread -lrt
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

all: gcov_report

s21_matrix.a: $(LIBOBJECTS)
	ar -crs s21_matrix.a $(LIBOBJECTS)
	rm -f *.o

test: clean tests.c s21_matrix.a
	$(CC) $(CFLAGS) tests.c $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	./run

gcov_report: test
	lcov -t "test" -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

# valgrind:
# 	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBSOURCES) test_valgrind.c -o vtests_run
# 	sh valgrind.sh ./vtests_run

rebuild: clean all


clean:
	rm -rf *.o \
		*.a \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report.* \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        unit-test \
        vtests_run \
		run \
		gcov \
		report/ \
		report.info
