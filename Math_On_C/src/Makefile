CC = gcc -Wall -Werror -Wextra -std=c11 -pedantic
LFLAGS = -lcheck -lpthread -lrt -lm -lsubunit -fprofile-arcs -ftest-coverage # флаги библиотек
SOURCES = $(wildcard s21_*.c)
OBJECTS = $(SOURCES:.c=.o)

all: clean test gcov_report

s21_math.a: $(OBJECTS)
	ar rcs $@ $^
	rm -f s21_*.o

%.o: %.c
	$(CC) -c $<

test: test.c s21_math.h s21_math.a 
	$(CC) -o $@ test.c s21_math.h s21_math.a $(LFLAGS)

rebuild: clean all

clean:
	rm -rf *.o *.gcno *.info *.gcda report s21_math.a test 

gcov_report: s21_math.a
	$(CC) --coverage *.c -o test $(LFLAGS)
	./test
	lcov -t "test" -o report.info -c -d .
	genhtml -o report report.info
	xdg-open ./report/index.html
	rm -f *.gcno *.info *.gcda

# $@: $^ - объект сборки: исходники
# ar - это утилита архивации, используемая для создания и манипуляции архивами файлов
# rcs - это опции команды ar:
# r - добавление файлов к архиву или обновление файлов в архиве
# c - создание нового архива, если он не существует
# s - создание индекса архива для быстрого доступа
# -fprofile-arcs -ftest-coverage - анализ покрытия
