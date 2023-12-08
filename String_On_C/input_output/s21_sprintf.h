#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../s21_string.h"
#define PRECISION 6;

typedef struct {
  char spec;
  int minus_flag;
  int plus_flag;
  int space_flag;
  int zero_flag;
  int sharp_flag;
  int width_number;
  int width_star;
  int prec_number;
  int prec_star;
  char length;
} Prototype;

// main
int s21_parser(char *str, const char *format, va_list args);
int s21_read_format(Prototype *prot, const char *format, int i, va_list args);
bool s21_check_number(const char *format, int i);
int s21_write_number(const char *format, int *i);
void s21_check_flags(const char *format, int i, Prototype *prot,
                     int *this_is_prec, int *this_is_width);
void s21_check_width(const char *format, int i, int *this_is_width,
                     Prototype *prot, va_list args);
int s21_check_prec(const char *format, int i, int *this_is_prec,
                   Prototype *prot, va_list args);
int s21_args_to_str(int j, char *str, Prototype *prot, va_list args);

char *s21_add_sign_or_space(char *buf_str, Prototype prot, int sign);

char *s21_main_func(char *str, Prototype *prot);

// flag handler
char *s21_add_char_left(char *str, int n, int str_size, char c, Prototype prot);
char *s21_add_char_right(char *str, int n, int str_size, char c);
char *s21_n_shift(char *str, int negativ_num, Prototype prot);
char *s21_add_sharp_sign(char *str, Prototype prot);

// specifiers
int s21_specifier_o(char *buff, va_list args, Prototype prot);
int s21_specifier_x(char *buff, va_list args, Prototype prot);
int s21_specifier_X(char *buff, va_list args, Prototype prot);
int s21_specifier_u(char *buff, va_list args, Prototype prot);
int s21_specifier_f(char *buff, va_list args, Prototype prot);

int s21_specifier_c(char *str, va_list args, Prototype *prot);
int s21_specifier_id(va_list args, Prototype *prot, char *charbuf);
void s21_specifier_n(va_list args, int j);
int s21_specifier_s(char *str, va_list args, Prototype *prot);
int s21_specifier_p(va_list args, char *charbuf, Prototype *prot);

int s21_specifier_e(int j, char *intermediate_str, va_list args,
                    Prototype *prot);

// spec eg
int s21_double_to_str(long double num, char *str_double, int num_i);
int s21_isnan(double number);
int s21_check_arg(Prototype *prot, char *intermediate_str,
                  int counter_symbols_str, double num);
bool s21_mantisssa_and_degree(double *num, bool flag_zero,
                              long long int *num_int, int *e, Prototype *prot);
void s21_fractional_and_integer_part_of_a_number(long long int *num_int,
                                                 double *num, Prototype *prot,
                                                 bool flag_zero_negative,
                                                 bool flag_minus_num_g);
int s21_rounding_and_precision_number(
    double *num, unsigned long int *multiply, Prototype *prot,
    double *save_number_for_g, int *e, int *check_g, int *precison,
    bool flag_zero_plus, bool flag_zero_negative, bool flag_g,
    int *save_precision_for_rounding_g, bool this_is_used,
    int *have_precision_g, int *save_precision_g, int *save_degree,
    long long int *num_int);
void s21_leading_zeros(char *str_int, int *save_precision_g_1,
                       int *have_precision_g, int *check_g, bool prec_0);
void s21_writing_int_number_with_point(
    long long int *num_int, int *symbol, char *str_int, bool flag_zero_negative,
    int *counter_symbols_str, int *dont_write_number_with_point,
    double *save_number_for_g, Prototype *prot, int *num_i_g,
    bool flag_minus_num, int *have_precision_g, int *save_precision_g,
    int *save_degree, int *e);
int s21_concat_fractional_number_with_degree(int num_i, int counter_symbols_str,
                                             char *str_double, double num,
                                             Prototype *prot, char symbol_e,
                                             int e, char *str_degree,
                                             int *dont_write_number_with_point);
void s21_check_fractional_number_for_zeros(unsigned long int *multiply,
                                           char *str_double,
                                           bool flag_minus_num, bool flag_g,
                                           bool this_is_used);

// sub functions
void s21_shift_str(char *str, int size);

void s21_UDecInNumSys(char *buff, unsigned long long int n, int mes, int flag);

void s21_long_double_to_str(long double num, char *str, int pres,
                            int sharp_flag);

void *s21_reverse(char *str, int neg_flag);

int s21_print_spaces(char *str, int n, int j);

int s21_prep_string(char *str, char *strng_arg, int n, int j);

int s21_check_arg(Prototype *prot, char *intermediate_str,
                  int counter_symbols_str, double num);

#endif