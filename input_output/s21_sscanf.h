#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "../s21_string.h"

// Структура, представляющая аргументы формата
struct Arguments {
  short asterisk;  // Флаг, указывающий на наличие '*' (0 или 1)
  int width;      // Ширина поля (-1 по умолчанию)
  char modifier;  // Модификатор (по умолчанию '\0')
  int success;  // Флаг успешной обработки (0 по умолчанию)
};

// Прототипы функций обработки различных форматов
int case_d(va_list valist, const char *str, struct Arguments *Arglist);
int case_c(va_list valist, const char *str, struct Arguments *Arglist);
int case_s(va_list valist, const char *str, struct Arguments *Arglist);
int case_f(va_list valist, const char *str, struct Arguments *Arglist,
           int *total_count);
int case_e(const char *str, long double *result, int *symbols_counter,
           struct Arguments *Arglist);
int case_u(va_list valist, const char *str, struct Arguments *Arglist);
int case_o(va_list valist, const char *str, struct Arguments *Arglist);
int case_x(va_list valist, const char *str, struct Arguments *Arglist);
long case_x_read(const char *str, struct Arguments *Arglist,
                 int *symbols_counter);
int case_i(va_list valist, const char *str, struct Arguments *Arglist);
int case_p(va_list valist, const char *str, struct Arguments *Arglist);

// Функция для записи значения типа long double в соответствующий тип
void case_f_write_to_destination(va_list valist, struct Arguments *Arglist,
                                 long double *result);

// Функция для записи значения типа long int в соответствующий тип
void case_d_write_to_destination(va_list valist, struct Arguments *Arglist,
                                 long int *result);

// Функция для парсинга ширины поля
void parse_width(struct Arguments *Arglist, char format_char);

// Функция для обработки форматного спецификатора
int process_format_specifier(va_list valist, const char *str,
                             struct Arguments *Arglist, char format);

// Функция для обработки форматного спецификатора чисел с плавающей точкой и
// шестнадцатеричных чисел
int process_float_hex_specifier(va_list valist, const char *str,
                                struct Arguments *Arglist, char format,
                                int *count);

// Функция для обработки форматного спецификатора %n
void process_format_n(struct Arguments *Arglist, long *all_symbols_count,
                      va_list valist, const char **str);

// Функция для обработки форматного спецификатора %%
void process_percent_specifier(struct Arguments *Arglist,
                               long *all_symbols_count, const char **str);
