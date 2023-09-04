CC = gcc -Wall -Werror -Wextra -std=c11 -pedantic
LFLAGS = -lcheck -lpthread -lrt -lm -lsubunit -fprofile-arcs -ftest-coverage # флаги библиотек
TESTS = ./tests/*.c ./tests/special/*.c ./tests/functional/*.c ./tests/input_output/*.c

SOURCES_SPECIAL = $(wildcard special/s21_*.c)
SOURCES_FUNCTIONAL = $(wildcard functional/s21_*.c)
SOURCES_INPUT_OUTPUT = $(wildcard input_output/*.c)
SOURCES = $(SOURCES_SPECIAL) $(SOURCES_FUNCTIONAL) $(SOURCES_INPUT_OUTPUT)
OBJECTS = $(SOURCES:.c=.o)

all: clean test gcov_report

s21_string.a: $(OBJECTS)
	ar rcs $@ $^
	rm -f */s21_*.o

%.o: %.c
	$(CC) -c $< -o $@

test: $(TESTS) ./tests/*.h s21_string.h s21_string.a 
	$(CC) -o $@ $^ $(LFLAGS)

rebuild: clean all

clean:
	rm -rf *.o input_output/specificators/*.o *.gcno *.info *.gcda report s21_string.a test 

gcov_report: s21_string.a
	$(CC) --coverage $(SOURCES) $(TESTS) -o test $(LFLAGS)
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