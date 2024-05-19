CORE=$(shell uname -s | tr '[:upper:]' '[:lower:]')
CC=gcc
CCFLAGS=-Wall -Wextra -Werror -g -std=c11 -pedantic
GCOVFLAGS=-fprofile-arcs -ftest-coverage
SRC_MODULES=$(wildcard ./Backend/*.c)

ifdef CORE
	ifeq ($(CORE), linux)
		CHECKFLAGS=-pthread -lcheck_pic -lrt -lm -lsubunit
		OPEN_CMD=xdg-open
	endif

	ifeq ($(CORE), darwin)
		CHECKFLAGS=$(shell pkg-config --cflags --libs check)
		OPEN_CMD=open
	endif
endif

all: dist dvi test gcov_report install

install:
	cd Frontend/ && qmake && make
	make clean

uninstall:
	make clean
	rm -rf Frontend/SmartCalc

clean: test_clean
	cd Frontend/ && rm -rf *.o .qmake.stash moc_* Makefile ui_*
	rm -rf Test/output/ *.gcda *.gcno
	rm -rf doc dist


dist: clean
	doxygen
	zip -r SmartCalc.zip ./* && mkdir dist && mv ./SmartCalc.zip ./dist

dvi: clean
	doxygen
	$(OPEN_CMD) doc/html/index.html

test: test_clean test_build test_run clean
	
test_clean:
	rm -rf Test/output
	rm -rf Test/report
	rm -rf Test/tests.info

test_build:
	mkdir Test/output

	$(CC) $(CCFLAGS) $(GCOVFLAGS) Test/s21_standart_test.c $(SRC_MODULES) $(CHECKFLAGS) -o ./Test/output/s21_standart_test
	$(CC) $(CCFLAGS) $(GCOVFLAGS) Test/s21_credit_test.c $(SRC_MODULES) $(CHECKFLAGS) -o ./Test/output/s21_credit_test
	$(CC) $(CCFLAGS) $(GCOVFLAGS) Test/s21_deposit_test.c $(SRC_MODULES) $(CHECKFLAGS) -o ./Test/output/s21_deposit_test

test_run:
	Test/output/s21_standart_test
	Test/output/s21_credit_test
	Test/output/s21_deposit_test

gcov_report: clean test
	lcov -o Test/tests.info -c -d .
	genhtml -o Test/report Test/tests.info
	$(OPEN_CMD)  Test/report/index.html

lint:
	clang-format --style=Google -n **/*.c **/*.h

lint-fix:
	clang-format --style=Google -i **/*.c **/*.h 
