#include "s21_sprintf.h"

int s21_specifier_f(char *buff, va_list args, Prototype prot) {
  // Установка значения prec_number по умолчанию, если оно не задано
  if (prot.prec_number == -1) {
    prot.prec_number = 6;  // Задаем точность по умолчанию
  }
  // Определение типа переменной a в зависимости от длины
  double a;  // Объявляем переменную сразу для обоих случаев
  if (prot.length == 'L') {
    // Для длины 'L' используем long double
    a = va_arg(args, long double);
  } else {
    // Иначе используем double
    a = va_arg(args, double);
  }
  // Преобразование double или long double в строку с заданной точностью и
  // флагами
  s21_long_double_to_str(a, buff, prot.prec_number, prot.sharp_flag);
  // Возвращаем длину полученной строки
  return s21_strlen(buff);
}

void s21_common_num_specifier(char *buff, unsigned long long int num, int base,
                              int uppercase, Prototype prot) {
  // Проверяем, если число равно 0 и точность, и ширина также равны 0, то
  // результат - пустая строка
  if (num == 0 && prot.prec_number == 0 && prot.width_number == 0) {
    buff[0] = '\0';
  } else if (!(num == 0 && prot.prec_number == 0)) {
    // Преобразование числа в указанную систему счисления с заданным регистром
    // букв
    s21_UDecInNumSys(buff, num, base, uppercase);
  } else {
    // В остальных случаях добавляем пробел в буфер
    buff[0] = ' ';
  }
}

int s21_specifier_o(char *buff, va_list args, Prototype prot) {
  unsigned long long int
      num;  // Используем тип unsigned long long int для универсальности
  // Определяем длину для разных типов чисел
  num = (prot.length == 'l') ? va_arg(args, unsigned long int)
                             : va_arg(args, unsigned int);
  // Вызываем общую функцию
  s21_common_num_specifier(buff, num, 8, 0, prot);
  return s21_strlen(buff);
}

int s21_specifier_u(char *buff, va_list args, Prototype prot) {
  unsigned long long int
      num;  // Используем тип unsigned long long int для универсальности
  // Определяем длину для разных типов чисел
  num = (prot.length == 'l') ? va_arg(args, unsigned long int)
                             : va_arg(args, unsigned int);
  // Вызываем общую функцию
  s21_common_num_specifier(buff, num, 10, 0, prot);
  return s21_strlen(buff);
}

int s21_specifier_X(char *buff, va_list args, Prototype prot) {
  unsigned long long int
      num;  // Используем тип unsigned long long int для универсальности
  // Определяем длину для разных типов чисел
  num = (prot.length == 'l') ? va_arg(args, unsigned long int)
                             : va_arg(args, unsigned int);
  // Вызываем общую функцию
  s21_common_num_specifier(buff, num, 16, 1, prot);
  return s21_strlen(buff);
}

int s21_specifier_x(char *buff, va_list args, Prototype prot) {
  unsigned long long int
      num;  // Используем тип unsigned long long int для универсальности
  // Определяем длину для разных типов чисел
  num = (prot.length == 'l') ? va_arg(args, unsigned long int)
                             : va_arg(args, unsigned int);
  // Вызываем общую функцию
  s21_common_num_specifier(buff, num, 16, 0, prot);
  return s21_strlen(buff);
}

int s21_specifier_p(va_list args, char *charbuf, Prototype *prot) {
  // Получаем указатель на аргумент типа void* из списка аргументов
  void *num = va_arg(args, void *);
  // Инициализируем буфер для хранения преобразованного числа в
  // шестнадцатеричную систему
  char buff[512] = {'\0'};
  // Преобразуем указатель в long long int, если num равен NULL, то используем 0
  long long int num2 = (long long int)num;
  if (num == s21_NULL) {
    num2 = 0;
  }
  // Преобразуем число в шестнадцатеричное представление
  s21_UDecInNumSys(buff, num2, 16, 0);
  int p_len = s21_strlen(buff);
  int space_len = 0;
  int zero_len = 0;
  // Вычисляем количество пробелов и нулей для выравнивания
  if (prot->prec_number > p_len) {
    zero_len = prot->prec_number - p_len;
  }
  if (prot->width_number > p_len + zero_len + 2) {
    space_len = prot->width_number - (p_len + zero_len + 2);
  }
  int i = 0;
  // Добавляем пробелы перед числом, если необходимо
  if (prot->minus_flag != 1) {
    for (int k = 0; k < space_len; k++) {
      charbuf[i++] = ' ';
    }
  }
  // Добавляем префикс "0x" для шестнадцатеричных чисел
  s21_strcat(charbuf, "0x");
  i += 2;
  // Добавляем ведущие нули, если необходимо
  for (int k = 0; k < zero_len; k++) {
    charbuf[i++] = '0';
  }
  // Добавляем шестнадцатеричное число
  s21_strcat(charbuf, buff);
  i += p_len;
  // Добавляем пробелы после числа, если необходимо
  if (prot->minus_flag == 1) {
    for (int k = 0; k < space_len; k++) {
      charbuf[i++] = ' ';
    }
  }
  // Завершаем строку в буфере
  charbuf[i] = '\0';
  // Возвращаем длину строки в буфере
  return s21_strlen(charbuf);
}

void s21_specifier_n(va_list args, int j) {
  int *var = va_arg(args, int *);
  *var = j;
}

// преобразует целочисленные значения в строку символов
int s21_specifier_id(va_list args, Prototype *prot, char *charbuf) {
  // Инициализация переменных
  __int128_t num = 0;
  int neg_flag = 0;

  // Определение длины числа на основе указателя длины
  if (prot->length == 'h') {
    num = (short)va_arg(args, int);
  } else if (prot->length == 'l') {
    num = va_arg(args, long int);
  } else {
    num = va_arg(args, int);
  }

  int num_i = 0;

  // Обработка отрицательных чисел
  if (num < 0) {
    neg_flag = 1;
    num *= -1;
    charbuf[num_i] = '-';
    num_i = 1;
  }
  // Обработка случая числа равного нулю
  if (num == 0) {
    if (prot->prec_number == 0) {
      charbuf[num_i] = '\0';
      num_i++;
    } else {
      charbuf[num_i] = '0';
      num_i++;
    }
  } else {
    // Преобразование числа в строку
    while (num > 0) {
      int tmp_dig = num % 10;
      num = num / 10;
      charbuf[num_i] = tmp_dig + '0';
      num_i++;
    }
  }
  // Обратное переворачивание строки
  s21_reverse(charbuf, neg_flag);
  return num_i;
}

int s21_specifier_s(char *str, va_list args, Prototype *prot) {
  int i = 0;    // Индекс для работы с строкой
  int len = 0;  // Длина строки
  char *strng_arg = va_arg(args, char *);  // Получение аргумента строки
  // Обработка случая, когда аргумент - NULL
  if (strng_arg == s21_NULL) {
    if (prot->prec_number == 0) {
      i += s21_prep_string(str, strng_arg, prot->prec_number, i);
    } else {
      s21_strncpy(str, "(null)",
                  fmin(6, prot->prec_number));  // Копирование "(null)" в строку
    }
    return 2;  // Возвращаем длину "(null)"
  }
  len = (int)s21_strlen(strng_arg);  // Вычисляем длину аргумента строки
  // Форматирование строки в зависимости от точности и длины
  if (prot->prec_number < len && prot->prec_number != -1) {
    i += s21_prep_string(str, strng_arg, prot->prec_number, i);
  } else if (prot->prec_number == 0) {
    i += s21_prep_string(str, strng_arg, prot->prec_number, i);
  } else if (len <= prot->prec_number || prot->prec_number == -1) {
    i += s21_prep_string(str, strng_arg, len, i);
  }
  return i;  // Возвращаем индекс
}

int s21_specifier_c(char *str, va_list args, Prototype *prot) {
  // Получаем символ из аргументов
  char c = va_arg(args, int);
  // Инициализация переменных
  int sp_qnt = 0;  // Количество пробелов
  int i = 0;       // Индекс для работы с строкой
  int ret = 0;     // Значение для возврата
  if (prot->width_number > 0) {
    sp_qnt = prot->width_number - 1;  // Вычисляем количество пробелов
  }
  // Форматирование вывода
  if (prot->minus_flag == 1) {
    str[i] = c;  // Помещаем символ в строку
    i++;
    i +=
        s21_print_spaces(str, sp_qnt, i);  // Добавляем пробелы, если необходимо
  } else {
    i += s21_print_spaces(str, sp_qnt, i);  // Добавляем пробелы перед символом
    str[i] = c;  // Помещаем символ в строку
    i++;
  }
  if (c == 0) ret = -1;  // Проверяем на конец строки ('\0')

  return ret;  // Возвращаем значение для возврата
}

// Обработка флагов в соответствии с форматом
void s21_process_flags(double *num, Prototype *prot, bool *flag_g,
                       bool *flag_zero_plus, bool *flag_minus_num_g) {
  // Установка флага flag_g, если формат 'g' или 'G'
  if (prot->spec == 'g' || prot->spec == 'G') {
    *flag_g = true;
  }
  // Проверка условия для флага flag_zero_plus при формате 'e' или 'E'
  if ((prot->spec == 'e' || prot->spec == 'E') && (*num < 1 && *num > 0.0) &&
      (*flag_zero_plus == false)) {
    *flag_zero_plus = true;
  }
  // Проверка условия для флага flag_zero_plus при формате 'g' или 'G'
  if ((*flag_g == true) && (*num < 1 && *num > 0.0) &&
      (*flag_zero_plus == false)) {
    *flag_zero_plus = true;
  }
  // Проверка условия для флага flag_minus_num_g при формате 'g' или 'G'
  if ((*flag_g == true) && (*num < 0)) {
    *flag_minus_num_g = true;
  }
}

// Обрабатывает флаг sharp_flag и обновляет флаг point_is_not_here.
// Функция возвращает состояние флага point_is_not_here после обработки.
bool processSharpFlag(char *str_int, char *str_double, int sharp_flag,
                      bool *point_is_not_here) {
  if ((str_double[0] == 'e' || str_double[0] == 'E') && sharp_flag == 0) {
    int n = 0;
    *point_is_not_here = true;
    for (; str_int[n] != '\0'; n++) {
    }
    if (str_int[n - 1] == '.') {
      n--;
      str_int[n] = '\0';
    }
  }
  if (sharp_flag == 1 && (str_double[0] == 'e' || str_double[0] == 'E')) {
    int i = 0;
    for (; str_int[i] != '\0'; i++) {
    }
    if (str_int[i - 1] == '.') {
      str_int[i] = '\0';
    } else {
      str_int[i] = '.';
      str_int[i + 1] = '\0';
    }
  }
  return *point_is_not_here;
}

// Проверка и корректировка флагов и параметров, связанных с точностью, в
// зависимости от условий
// - Обновляет флаг flag_g_prec_1 на основе конкретных условий
// - Корректирует num и prec_0 в соответствии с точностью и условиями флагов
void check_and_adjust_precision_flags(int e, bool *flag_g, bool *flag_g_prec_1,
                                      double *num, bool *prec_0,
                                      Prototype *prot) {
  // Условное обновление флага flag_g_prec_1
  if (*flag_g == true && 1 > e && e >= -4 &&
      (prot->prec_number == 1 || prot->prec_star == 1)) {
    *flag_g_prec_1 = false;
  }
  // Обработка случаев, когда точность равна 0
  if (prot->prec_number == 0 || prot->prec_star == 0) {
    *num = round(*num * pow(10, 0)) / pow(10, 0);
    *prec_0 = true;
  }
  // Обработка случаев, когда точность равна 1 и условия флагов соблюдаются
  else if ((prot->prec_number == 1 || prot->prec_star == 1) &&
           (*flag_g_prec_1 = true) && (*flag_g == true)) {
    *num = round(*num * pow(10, 0)) / pow(10, 0);
    if (*num == 10) {
      *num /= 10;
    }
  }
}

// Выполняет корректировку и применение умножений и точности к save_number_for_g
void apply_multiplications_and_precision(double *save_number_for_g, int num_i_g,
                                         bool check_num_i_g, int save_multiply,
                                         int multiply_for_fractional_num,
                                         long long int *multiply_num_i_g,
                                         int *save_precision_for_rounding_g) {
  if (save_multiply != 1) {
    *multiply_num_i_g /= save_multiply;
    save_precision_for_rounding_g = 0;
  }

  if (num_i_g == 0 && check_num_i_g == false) {
    *save_number_for_g *= multiply_for_fractional_num;
  } else {
    *save_number_for_g *= *multiply_num_i_g;
    *save_number_for_g =
        round(*save_number_for_g * pow(10, *save_precision_for_rounding_g)) /
        pow(10, *save_precision_for_rounding_g);
  }
}

// Корректирует различные числа в зависимости от заданных условий
void adjustNumbers(int *precision, int *save_multiply,
                   unsigned long int *multiply_for_fractional_num, int *num_i_g,
                   bool *check_num_i_g, long long int *multiply_num_i_g,
                   double *save_number_for_g) {
  // Коррекция точности и save_multiply при необходимости
  while (*precision > 0 && *save_multiply != 1) {
    (*precision)--;
    (*save_multiply) *= 10;
  }

  *save_number_for_g *= (*save_multiply);

  if (*num_i_g == 0) {
    while (*precision > 0) {
      (*precision)--;
      (*multiply_for_fractional_num) *= 10;
    }
  } else {
    *num_i_g = *precision - *num_i_g;
  }

  if (*num_i_g != 0) {
    while (*num_i_g > 0) {
      (*num_i_g)--;
      (*multiply_num_i_g) *= 10;
    }
    *check_num_i_g = true;
  }
}

int s21_specifier_e(int counter_symbols_str, char *intermediate_str,
                    va_list args, Prototype *prot) {
  int e = 0, symbol = 0, num_i = 0, save_precision_g_1 = 0,
      have_precision_g = 0, dont_write_number_with_point = 0, check_g = 0,
      precision = 6, save_precision_for_rounding_g = 0, save_multiply = 0,
      save_degree = 0, num_i_g = 0;
  long long int num_int = 0, multiply_num_i_g = 1;
  unsigned long int multiply = 1, multiply_for_fractional_num = 1;
  double num = 0.;
  char str_int[512] = {'\0'}, str_double[270] = {'\0'},
       str_double_g[270] = {'\0'}, symbol_e = '\0', str_degree[560] = {'\0'};
  bool flag_zero = false, flag_zero_negative = false, flag_zero_plus = false,
       flag_minus_num = false, flag_minus_num_g = false, check_num_i_g = false,
       flag_g = false, this_is_used = false, flag_g_prec_1 = true,
       prec_0 = false;
  num =
      (prot->length == 'L') ? va_arg(args, long double) : va_arg(args, double);
  double save_number_for_g = num;
  if (s21_check_arg(prot, intermediate_str, counter_symbols_str, num) != 0) {
    return counter_symbols_str;
  }
  s21_process_flags(&num, prot, &flag_g, &flag_zero_plus, &flag_minus_num_g);
  flag_zero_negative =
      s21_mantisssa_and_degree(&num, flag_zero, &num_int, &e, prot);
  if ((num_int == 0 || num_int == 1) &&
      (prot->spec == 'g' || prot->spec == 'G')) {
    str_int[0] = (num_int == 0) ? '0' : '1';
    s21_strcat(intermediate_str, str_int);
    return counter_symbols_str;
  }
  check_and_adjust_precision_flags(e, &flag_g, &flag_g_prec_1, &num, &prec_0,
                                   prot);
  s21_fractional_and_integer_part_of_a_number(
      &num_int, &num, prot, flag_zero_negative, flag_minus_num_g);
  dont_write_number_with_point = s21_rounding_and_precision_number(
      &num, &multiply, prot, &save_number_for_g, &e, &check_g, &precision,
      flag_zero_plus, flag_zero_negative, flag_g,
      &save_precision_for_rounding_g, this_is_used, &have_precision_g,
      &save_precision_g_1, &save_degree, &num_int);
  if (check_g != 1) {
    s21_writing_int_number_with_point(
        &num_int, &symbol, str_int, flag_zero_negative, &counter_symbols_str,
        &dont_write_number_with_point, &save_number_for_g, prot, &num_i_g,
        flag_minus_num, &have_precision_g, &save_precision_g_1, &save_degree,
        &e);
    counter_symbols_str = s21_concat_fractional_number_with_degree(
        num_i, counter_symbols_str, str_double, num, prot, symbol_e, e,
        str_degree, &dont_write_number_with_point);
    s21_check_fractional_number_for_zeros(&multiply, str_double, flag_minus_num,
                                          flag_g, this_is_used);
    bool point_is_not_here = false;
    processSharpFlag(str_int, str_double, prot->sharp_flag, &point_is_not_here);
    s21_strcat(str_int, str_double);  // соединяем 2 строки получаем число
    if (flag_g == true && prot->sharp_flag == 0 && point_is_not_here == false)
      s21_leading_zeros(str_int, &save_precision_g_1, &have_precision_g,
                        &check_g, prec_0);
    s21_strcat(intermediate_str,
               str_int);  // закидываем готовый результат в промежуточную строку
  } else {
    s21_writing_int_number_with_point(
        &num_int, &symbol, str_int, flag_zero_negative, &counter_symbols_str,
        &dont_write_number_with_point, &save_number_for_g, prot, &num_i_g,
        flag_minus_num, &have_precision_g, &save_precision_g_1, &save_degree,
        &e);
    save_multiply = multiply;
    precision++;
    s21_check_fractional_number_for_zeros(&multiply, str_double, flag_minus_num,
                                          flag_g, this_is_used);
    adjustNumbers(&precision, &save_multiply, &multiply_for_fractional_num,
                  &num_i_g, &check_num_i_g, &multiply_num_i_g,
                  &save_number_for_g);
    s21_fractional_and_integer_part_of_a_number(&num_int, &save_number_for_g,
                                                prot, flag_zero_negative,
                                                flag_minus_num_g);
    apply_multiplications_and_precision(
        &save_number_for_g, num_i_g, check_num_i_g, save_multiply,
        multiply_for_fractional_num, &multiply_num_i_g,
        &save_precision_for_rounding_g);
    save_number_for_g = (long long int)save_number_for_g;
    s21_double_to_str(save_number_for_g, str_double_g, num_i);
    s21_reverse(str_double_g, 0);
    s21_strcat(str_double, str_double_g);
    s21_strcat(str_int, str_double);
    if (prot->sharp_flag == 0)
      s21_leading_zeros(str_int, &save_precision_g_1, &have_precision_g,
                        &check_g, prec_0);
    s21_strcat(intermediate_str, str_int);
  }
  return counter_symbols_str;
}

int s21_double_to_str(long double num, char *str_double, int num_i) {
  // Преобразование числа с плавающей точкой в строку
  while (num > 0) {
    int num_double = 0;
    // Получение последней цифры дробной части
    num_double = (long int)num % 10;

    // Преобразование цифры в символ и добавление к строке
    str_double[num_i] = num_double + '0';
    // Переход к следующей позиции в строке
    num_i++;
    // Удаление последней цифры дробной части
    num /= 10;
    num = (unsigned long int)num;
  }
  return num_i;  // Возвращаем обновленное значение индекса в строке
}

int s21_isnan(double number) {
  int result = 0;
  if (number != number) {
    result = 1;
  }
  return result;
}

/**
 * Функция управления ведущими нулями для формата 'g'
 * str_int: строка с числом
 * save_precision_g_1: указатель на сохраненную точность для формата 'g'
 * have_precision_g: указатель на флаг наличия точности для формата 'g'
 * check_g: указатель на флаг формата 'g'
 * prec_0: флаг, указывающий на точность 0
 */

void s21_leading_zeros(char *str_int, int *save_precision_g_1,
                       int *have_precision_g, int *check_g, bool prec_0) {
  int counter_g_leading_zeros = 0, counter_g_prec = 0;
  char str_degree_from_degree[1024] = {'\0'};
  bool this_is_zero = false, this_is_int = false, check_for_g = false;
  // Проверка, начинается ли строка с "-." для определения нуля
  if (str_int[counter_g_prec] == '-' && str_int[counter_g_prec + 1] == '.') {
    counter_g_leading_zeros += 1;
    this_is_zero = true;
    this_is_int = true;
  } else if (str_int[counter_g_prec] == '-')
    counter_g_prec += 1;
  // Определение ведущих нулей перед целой частью числа
  while (this_is_int == false && this_is_zero == false) {
    if (counter_g_prec < (int)s21_strlen(str_int) &&
        str_int[counter_g_prec] != '.') {
      counter_g_leading_zeros += 1;
      counter_g_prec += 1;
    } else {
      counter_g_prec += 1;
      this_is_int = true;
    }
  }
  // Вычисление точности для формата 'g'
  if (*have_precision_g == 0) {
    *save_precision_g_1 = 6;
    *save_precision_g_1 -= counter_g_leading_zeros;
  } else
    *save_precision_g_1 -= counter_g_leading_zeros;
  // Пропуск лишних символов для точности
  for (int i = 1; i <= *save_precision_g_1; i++) {
    if (str_int[counter_g_prec] != '\0') counter_g_prec++;
  }
  counter_g_prec--;
  // Подготовка строки для формата 'g'
  if (*check_g != 1) {
    check_for_g = true;
    str_degree_from_degree[0] = str_int[counter_g_prec + 1];
    str_degree_from_degree[1] = str_int[counter_g_prec + 2];
    int n = 3, n_degree = 2;
    while (str_int[counter_g_prec + n] != '\0') {
      str_degree_from_degree[n_degree] = str_int[counter_g_prec + n];
      n++;
      n_degree++;
    }
  }
  // Удаление ведущих нулей после целой части числа
  bool this_is_not_zero = false;
  while (this_is_not_zero == false) {
    if (str_int[counter_g_prec] == '0') {
      counter_g_prec--;
    } else
      this_is_not_zero = true;
  }
  // Обработка не нулевого числа
  if (this_is_not_zero == true) {
    str_int[counter_g_prec + 1] = '\0';
    if (check_for_g == true && prec_0 == false)
      s21_strcat(str_int, str_degree_from_degree);
  }
}

int s21_check_arg(Prototype *prot, char *intermediate_str,
                  int counter_symbols_str, double num) {
  int flag_check_arg = 0;
  // Проверка на бесконечность (Infinity)
  if (num == INFINITY || num == -INFINITY) {
    int counter = 0;
    // Если число отрицательная бесконечность, добавляем минус в строку
    if (num == -INFINITY) {
      intermediate_str[counter++] = '-';
    }
    // Выбираем строку для записи в зависимости от спецификатора
    const char *inf_str =
        (prot->spec == 'E' || prot->spec == 'G') ? "INF" : "inf";
    int inf_str_length = (prot->spec == 'E' || prot->spec == 'G') ? 3 : 3;

    // Копируем символы строки в промежуточную строку
    for (int i = 0; i < inf_str_length; i++) {
      intermediate_str[counter++] = inf_str[i];
    }
    // Обновляем счетчик символов и возвращаем его
    counter_symbols_str += counter;
    return counter_symbols_str;
  }
  // Проверка на NaN (Not-a-Number)
  if (s21_isnan(num) == 1) {
    // Выбираем строку для записи в зависимости от спецификатора
    const char *nan_str =
        (prot->spec == 'E' || prot->spec == 'G') ? "NAN" : "nan";
    int nan_str_length = (prot->spec == 'E' || prot->spec == 'G') ? 3 : 3;
    // Копируем символы строки в промежуточную строку
    for (int i = 0; i < nan_str_length; i++) {
      intermediate_str[i] = nan_str[i];
    }
    // Обновляем счетчик символов и возвращаем его
    counter_symbols_str += nan_str_length;
    return counter_symbols_str;
  }
  return flag_check_arg;
}

/*выполняет вычисления, связанные с представлением числа в экспоненциальной
форме M × 10^e и обрабатывает особые случаи, связанные с нулями и отрицательными
нулями для разных спецификаторов формата.*/
bool s21_mantisssa_and_degree(double *num, bool flag_zero,
                              long long int *num_int, int *e, Prototype *prot) {
  bool flag_zero_negative = false;
  // Проверяем, если число равно нулю
  if (*num == 0) {
    flag_zero = true;  // Устанавливаем флаг нулевого числа
  }
  // Проверяем, если спецификатор 'e' или 'E' и число отрицательно и между -1 и
  // 0
  if ((prot->spec == 'e' || prot->spec == 'E') &&
      (*num > -1 && signbit(*num) && *num < 0.0)) {
    flag_zero_negative = true;  // Устанавливаем флаг отрицательного нуля
  }
  // Проверяем, если спецификатор 'g' или 'G' и число отрицательно и между -1 и
  // 0
  if ((prot->spec == 'g' || prot->spec == 'G') &&
      (*num > -1 && signbit(*num) && *num < 0.0)) {
    flag_zero_negative = true;  // Устанавливаем флаг отрицательного нуля
  }
  // Получаем целую часть дробного числа
  *num_int = (long long int)*num;

  // Рассчитываем мантиссу и степень числа
  if (*num >= 1 || *num <= -1 || flag_zero == true) {
    if ((*num_int >= 10 || *num_int <= -10)) {
      do {
        *num /= 10;
        *e += 1;  // Увеличиваем степень на 1
      } while (*num > 10 || *num < -10);
    }
  } else {
    do {
      *num *= 10;
      *e -= 1;               // Уменьшаем степень на 1
      *num_int = (int)*num;  // Обновляем целую часть числа
    } while (*num_int == 0 && flag_zero == false);
  }
  return flag_zero_negative;  // Возвращаем флаг отрицательного нуля
}

/*отвечает за разбиение дробного числа на его целую и дробную части, а также
 * производит коррекцию значений*/
void s21_fractional_and_integer_part_of_a_number(long long int *num_int,
                                                 double *num, Prototype *prot,
                                                 bool flag_zero_negative,
                                                 bool flag_minus_num_g) {
  // Определяем целую часть дробного числа
  *num_int = (long long int)*num;
  // Вычитаем целую часть, чтобы получить дробную
  *num -= *num_int;
  // Если целая часть была отрицательной, делаем дробное число положительным
  if (*num_int < 0) {
    *num *= -1;
  }
  // Коррекция для спецификатора 'g' или 'G' в случае отрицательных нулей
  if ((prot->spec == 'g' || prot->spec == 'G') && flag_zero_negative &&
      flag_minus_num_g) {
    *num *= -1;
  }
}

// Получение точности в соответствии с форматом
void s21_get_precision(Prototype *prot, int *precision, int *have_precision_g,
                       int *save_precision_g_1) {
  // Если точность задана через '*'
  if (prot->prec_star != -1) {
    *precision = prot->prec_star;  // Задаем точность из '*'
    *save_precision_g_1 = *precision;  // Сохраняем точность для формата 'g'
    *have_precision_g =
        1;  // Устанавливаем флаг, что точность задана для формата 'g'
  }
  // Если точность задана числом
  else if (prot->prec_number != -1) {
    *precision = prot->prec_number;  // Задаем точность из числа
    *save_precision_g_1 = *precision;  // Сохраняем точность для формата 'g'
    *have_precision_g =
        1;  // Устанавливаем флаг, что точность задана для формата 'g'
  }
}

// Подготовка числа и данных для формата g/G
void s21_prepare_for_format_g(double *num, int *e, double *save_number_for_g,
                              int *precision, bool *flag_g_e_more_minus_four,
                              int *counter_g_minus_e,
                              int *counter_g_final_precision, Prototype *prot,
                              int *have_precision_g) {
  // Проверяем, подходят ли условия для формата 'g' или 'G' с учетом точности и
  // экспоненты
  if ((prot->spec == 'g' || prot->spec == 'G') &&
      ((*e >= -4 && *e <= 5 && (*have_precision_g == 0)) ||
       (*precision > *e && *e >= -4 && *have_precision_g == 1))) {
    *flag_g_e_more_minus_four =
        true;  // Устанавливаем флаг, что экспонента соответствует условиям
    *num = *save_number_for_g;  // Заменяем числовое значение на сохраненное для
                                // формата 'g'
    while (*e < 0) {
      *e += 1;  // Увеличиваем экспоненту на 1
      (*counter_g_minus_e)++;  // Увеличиваем счетчик экспоненты вниз
    }
    if (*counter_g_minus_e > 0) {
      *counter_g_final_precision =
          *counter_g_minus_e;  // Применяем счетчик в качестве точности для
                               // формата 'g'
    }
  }
}

// Применение округления и точности к числу, а также конвертация в целое число
void s21_apply_precision_and_conversion(double *num, int *precision,
                                        bool flag_g, bool flag_zero_plus,
                                        bool flag_zero_negative,
                                        bool this_is_used, int *check_g,
                                        int save_precision_g,
                                        unsigned long int *multiply,
                                        long long int *flag, bool *skip) {
  // Применяем умножение на 10 для применения точности
  for (int i = 0; i < *precision; i++) {
    *num *= 10;
    if (*num == 0) {
      *skip =
          true;  // Если число становится нулевым, устанавливаем флаг пропуска
    }

    *flag = (long long int)*num;
    // Если это формат 'g' и установлен флаг flag_g, умножаем multiply на 10,
    // если последняя цифра числа равна 0
    if ((flag_zero_negative == false && flag_zero_plus == false &&
         flag_g == true) &&
        *flag % 10 == 0) {
      *multiply *= 10;
    }

    // Если число становится нулевым, умножаем multiply на 10
    if (*flag == 0) {
      *multiply *= 10;
    }
  }
  // Убираем нулевые концевые цифры путем деления на 10
  while (*flag % 10 == 0 && *skip == false) {
    *multiply /= 10;
    *flag /= 10;
    *flag = (long long int)*flag;
  }
  // Восстанавливаем точность, если была применена для формата 'g'
  if (this_is_used == true) {
    *precision = save_precision_g;  // сохранение точности
  }
  // Применяем округление числа до целой части, если это формат 'g' и необходимо
  if (flag_g == true && *check_g == 0) {
    *num = round(*num * pow(10, 0)) / pow(10, 0);
  }
  // Если число отрицательное, берем его модуль
  if (*num < 0) {
    *num = fabs(*num);
  }
  // Конвертируем число в беззнаковое целое число (отбрасываем дробную часть)
  *num = (unsigned long int)*num;  // получение дробного числа в виде инта
}

// Функция применения округления и точности
// Применение округления и точности к числу в соответствии с форматом
void s21_apply_rounding_and_precision(double *num, Prototype *prot,
                                      double *save_number_for_g, int *check_g,
                                      int *precision,
                                      int counter_g_final_precision,
                                      bool this_is_used, bool flag_g) {
  // Применяем округление числа с учетом указанной точности и дополнительной
  // точности для формата 'g'
  if (prot->length == 'L') {
    *num = roundl(*num * pow(10, *precision + counter_g_final_precision)) /
           pow(10, *precision + counter_g_final_precision);
  } else {
    *num = round(*num * pow(10, *precision + counter_g_final_precision)) /
           pow(10, *precision + counter_g_final_precision);
  }
  // Если это формат 'g' и флаг check_g равен 0, применяем еще одно округление
  if (flag_g == true && *check_g == 0) {
    *num = round(*num * pow(10, *precision + counter_g_final_precision)) /
           pow(10, *precision + counter_g_final_precision);
  }
  // Если данное число используется для формата 'g', сохраняем его значение
  if (this_is_used == true) {
    *save_number_for_g = *num;
  }
}

// Проверяет наличие нулевых десятичных цифр и корректирует точность
void check_zeros_and_adjust_precision(double *check_fractional_num_g,
                                      int *precision,
                                      bool *this_is_prec_with_zeros) {
  int counter = *precision;
  for (int i = 0; i < counter && *this_is_prec_with_zeros == false; i++) {
    *check_fractional_num_g *= 10;
    if ((long long int)*check_fractional_num_g % 10 == 0) {
      *precision -= 1;
    }
  }
}
// Округляет число и проверяет наличие ненулевых десятичных цифр
void round_and_check_fractional(double *check_fractional_num_g,
                                double *save_number_for_g, int *precision,
                                bool *this_is_prec_with_zeros) {
  *check_fractional_num_g =
      round(*check_fractional_num_g * pow(10, *precision)) /
      pow(10, *precision);

  double check_fractional_num_from_zeros_g = *save_number_for_g;
  for (int i = 0; i < *precision; i++) {
    check_fractional_num_from_zeros_g *= 10;
  }

  if ((long long int)check_fractional_num_from_zeros_g % 10 != 0) {
    *this_is_prec_with_zeros = true;
  }
}

// обрабатывает различные случаи связанные с точностью, округлением и конверсией
// числа в соответствии с заданным форматом
int s21_rounding_and_precision_number(
    double *num, unsigned long int *multiply, Prototype *prot,
    double *save_number_for_g, int *e, int *check_g, int *precision,
    bool flag_zero_plus, bool flag_zero_negative, bool flag_g,
    int *save_precision_for_rounding_g, bool this_is_used,
    int *have_precision_g, int *save_precision_g_1, int *save_degree,
    long long int *num_int) {
  long long int flag = -1;
  int dont_write_number_with_point = 0, counter_g_minus_e = 0,
      counter_g_plus_e = 0, counter_g_final_precision = 0,
      save_precision_g = -1;
  double check_fractional_num_g = 0;
  bool flag_g_e_more_minus_four = false, this_is_prec_with_zeros = false,
       skip = false;
  // Получение точности в соответствии с форматом
  s21_get_precision(prot, precision, have_precision_g, save_precision_g_1);
  *save_degree = *e;
  // Подготовка числа и данных для формата g/G
  s21_prepare_for_format_g(num, e, save_number_for_g, precision,
                           &flag_g_e_more_minus_four, &counter_g_minus_e,
                           &counter_g_final_precision, prot, have_precision_g);
  // Проверка и установка флага для формата g/G, если применимо
  if (flag_g_e_more_minus_four == true) {
    *num = *save_number_for_g;
    *check_g = 1;
  }
  // Обработка случая, когда точность равна 0
  if (prot->prec_number == 0 || prot->prec_star == 0) {
    dont_write_number_with_point = 1;
    if (prot->spec == 'g' || prot->spec == 'G') {
      *save_number_for_g = *num_int;
    }
  } else {
    // Обработка случая, когда точность не задана
    if (prot->prec_number == -1 || prot->prec_star == -1) {
      if (prot->spec == 'g' || prot->spec == 'G') {
        *precision -= 1;
        save_precision_g = *precision;
      }
      // Обработка случая, когда точность не задана и экспонента отрицательна
      if (counter_g_minus_e == 0 && flag_g_e_more_minus_four == true) {
        // Установка параметров точности для формата g/G
        this_is_used = true;
        *precision += 1;
        flag = (int)*num;
        if (flag < 0) flag *= -1;
        while (flag > 0) {
          flag /= 10;
          counter_g_plus_e++;
        }
        check_fractional_num_g = *save_number_for_g;
        s21_fractional_and_integer_part_of_a_number(
            &flag, &check_fractional_num_g, prot, 0, 0);
        *precision -= counter_g_plus_e;
        round_and_check_fractional(&check_fractional_num_g, save_number_for_g,
                                   precision, &this_is_prec_with_zeros);
        check_zeros_and_adjust_precision(&check_fractional_num_g, precision,
                                         &this_is_prec_with_zeros);
        *save_precision_for_rounding_g = *precision;
        flag = -1;
      }
      // Применение округления и точности
      s21_apply_rounding_and_precision(num, prot, save_number_for_g, check_g,
                                       precision, counter_g_final_precision,
                                       this_is_used, flag_g);
      // Применение точности и конверсии
      s21_apply_precision_and_conversion(
          num, precision, flag_g, flag_zero_plus, flag_zero_negative,
          this_is_used, check_g, save_precision_g, multiply, &flag, &skip);
    }
  }
  return dont_write_number_with_point;
}

// Обработка целой и дробной части числа для форматов g/G
void s21_process_integer_and_fractional_part(double send_to_function_num,
                                             char *str_int, int *num_i_g,
                                             bool flag_zero_negative,
                                             bool flag_minus_num,
                                             int *have_precision_g,
                                             int *save_precision_g_1) {
  // Если числовое значение равно 0 и не отрицательное, добавить "0."
  if (*num_i_g == 0 && send_to_function_num >= 0 &&
      flag_zero_negative == false) {
    str_int[0] = '0';
    str_int[1] = '.';
  } else {
    // Инвертировать порядок символов, чтобы получить правильное представление
    // дробной части
    s21_reverse(str_int, 0);
    // Если число положительное и не нулевое, добавить точку для дробной части
    if (flag_zero_negative == false && send_to_function_num >= 0)
      str_int[*num_i_g] = '.';
  }
  // Обработка отрицательных чисел
  if (flag_zero_negative == true) {
    send_to_function_num *= -1;
    str_int[0] = '-';
    str_int[1] = '0';
    str_int[2] = '.';
  }
  // Если числовое значение равно 0 и отрицательное, добавить "-0."
  if ((*num_i_g == 0 && send_to_function_num < 0) &&
      flag_zero_negative == false) {
    unsigned long int counter = 10;
    flag_minus_num = true;
    send_to_function_num *= -1;
    *num_i_g = s21_double_to_str(send_to_function_num, str_int, 0);
    s21_reverse(str_int, 0);
    s21_check_fractional_number_for_zeros(&counter, str_int, flag_minus_num, 0,
                                          0);
    str_int[*num_i_g + 1] = '.';
  }
  // Обработка точности, установка символа завершения строки
  if ((*num_i_g == 6 && *have_precision_g == 0) ||
      (*num_i_g == *save_precision_g_1 && *have_precision_g == 1)) {
    // Увеличить индекс, если число отрицательное
    if (str_int[0] == '-') *num_i_g += 1;
    str_int[*num_i_g] = '\0';
  }
}

// Запись целого числа с десятичной точкой в строку str_int
void s21_writing_int_number_with_point(
    long long int *num_int, int *symbol, char *str_int, bool flag_zero_negative,
    int *counter_symbols_str, int *dont_write_number_with_point,
    double *save_number_for_g, Prototype *prot, int *num_i_g,
    bool flag_minus_num, int *have_precision_g, int *save_precision_g_1,
    int *save_degree, int *e) {
  bool check_g = false;
  double send_to_function_num = 0;
  // Проверка, применяется ли формат g/G с учетом точности и степени числа
  if ((prot->spec == 'g' || prot->spec == 'G') &&
      ((*save_degree >= -4 && *save_degree <= 5 &&
        (prot->prec_number == -1 || prot->prec_star == -1)) ||
       (*save_precision_g_1 > *save_degree && *save_degree >= -4 &&
        (prot->prec_number != -1 || prot->prec_star != -1)))) {
    // Определение числа для форматов g/G с учетом степени
    if (*save_precision_g_1 <= *e && *save_precision_g_1 != 0)
      *num_int = *num_int % 10;
    else
      *num_int = (long long int)*save_number_for_g;
    check_g = true;
  }
  // Установка символа для записи и числа для функции преобразования
  if (check_g == true) {
    *symbol = *num_int;
    send_to_function_num = *symbol;
  } else
    *symbol = *num_int % 10;
  // Запись числа в строку с учетом формата и точности
  if (*dont_write_number_with_point == 1) {
    if (*symbol < 0) {
      *symbol *= -1;
      str_int[0] = '-';
      str_int[1] = *symbol + '0';
    } else
      str_int[0] = *symbol + '0';
  } else {
    if ((*symbol < 0 || flag_zero_negative == true) && check_g == false) {
      *symbol *= -1;
      str_int[0] = '-';
      str_int[1] = *symbol + '0';
      str_int[2] = '.';
      *counter_symbols_str += 3;
    } else {
      if (check_g == true) {
        // Запись числа с учетом формата g/G
        *num_i_g = s21_double_to_str(send_to_function_num, str_int, 0);
        s21_process_integer_and_fractional_part(
            send_to_function_num, str_int, num_i_g, flag_zero_negative,
            flag_minus_num, have_precision_g, save_precision_g_1);
      } else {
        // Запись обычного числа с десятичной точкой
        str_int[0] = *symbol + '0';
        str_int[1] = '.';
        *counter_symbols_str += 2;
      }
    }
  }
}

// создания строки, представляющей дробное число в научной (экспоненциальной)
// форме с заданной точностью и символом степени
int s21_concat_fractional_number_with_degree(
    int num_i, int counter_symbols_str, char *str_double, double num,
    Prototype *prot, char symbol_e, int e, char *str_degree,
    int *dont_write_number_with_point) {
  // Записываем дробную часть числа в массив char и соединяем дробную часть
  // с символом степени, если необходимо
  if (*dont_write_number_with_point != 1) {
    num_i = s21_double_to_str(num, str_double, num_i);
    s21_reverse(str_double, 0);
  }
  // Определение символа для обозначения степени в зависимости от формата
  if (prot->spec == 'E' || prot->spec == 'G')
    symbol_e = 'E';
  else
    symbol_e = 'e';
  // Добавление символа степени к строке и увеличение счетчика символов
  str_double[num_i] = symbol_e;
  counter_symbols_str++;
  // Добавление знака степени (+ или -) и увеличение счетчика символов
  if (e >= 0) {
    str_double[num_i + 1] = '+';
    counter_symbols_str++;
  } else {
    str_double[num_i + 1] = '-';
    counter_symbols_str++;
  }
  // Обработка значения степени
  if (e >= 10) {
    s21_double_to_str(e, str_degree, 0);
    s21_reverse(str_degree, 0);
  } else {
    str_double[num_i + 2] = '0';
    counter_symbols_str++;
  }
  // Обработка нулевой степени
  if (e == 0) {
    str_double[num_i + 3] = '0';
    counter_symbols_str++;
  } else {
    // Обработка отрицательной степени
    if (e < 0) e *= -1;
    s21_double_to_str(e, str_degree, 0);
    s21_reverse(str_degree, 0);
    s21_strcat(str_double, str_degree);  // соединяем число с символом степени
  }
  return counter_symbols_str;
}

// проверка дробной части числа (представленной в виде строки) на наличие нулей
void s21_check_fractional_number_for_zeros(unsigned long int *multiply,
                                           char *str_double,
                                           bool flag_minus_num, bool flag_g,
                                           bool this_is_used) {
  // Проверка на наличие нулей в дробной части
  if (!flag_g && !this_is_used) {
    while (*multiply >= 10) {
      int length = s21_strlen(str_double);
      // Сдвиг всех символов на одну позицию вправо
      for (int i = length - 1; i >= 0; i--) {
        str_double[i + 1] = str_double[i];
      }
      // Вставка минуса или нуля в начало строки
      if (flag_minus_num) {
        str_double[0] = '-';
      } else {
        str_double[0] = '0';
      }
      *multiply /= 10;  // Уменьшение множителя для проверки следующей цифры
    }
  }
}

// Функция для сдвига символов в строке на одну позицию вправо
void s21_shift_str(char *str, int size) {
  for (int i = size - 1; i > 0; --i) {
    // Копируем символ из предыдущей позиции в текущую
    str[i] = str[i - 1];
  }
}

// Функция для преобразования целого числа в строку с заданной системой
// счисления и опциональным выбором регистра для шестнадцатеричных чисел
void s21_UDecInNumSys(char *buff, unsigned long long int n, int base,
                      int uppercase) {
  int size_ans =
      0;  // Переменная для отслеживания размера ответа (длины строки)
  char str[2] = {
      'a',
      'A'};  // Массив символов для выбора регистра в шестнадцатеричной системе
  if (n == 0) {
    buff[size_ans++] = '0';  // Обрабатываем случай, когда число равно нулю
  } else {
    while (n != 0) {
      size_ans += 1;  // Увеличиваем размер ответа
      s21_shift_str(
          buff, size_ans);  // Сдвигаем символы в строке на одну позицию вправо
      if (n % base > 9) {
        // Если остаток от деления больше 9, то используем буквы для
        // шестнадцатеричных чисел
        buff[0] = n % base - 10 + str[uppercase];
      } else {
        buff[0] =
            n % base + '0';  // Иначе просто добавляем символ числа к строке
      }
      n /=
          base;  // Делим число на базу системы счисления для следующей итерации
    }
  }
  buff[size_ans] = '\0';  // Завершаем строку нулевым символом
}

/**
 * Функция для округления числа, представленного в виде строки
 * @param count_before_dot: количество символов до десятичной точки
 * @param pres: количество символов после десятичной точки (для округления)
 * @param neg_flag: флаг, указывающий на отрицательное число
 * @param add_point: флаг, указывающий на наличие десятичной точки в исходной
 * строке
 * @param index: текущий индекс в строке
 * @return  Возвращаем обновленный индекс
 */
int s21_rounding(char *str, int count_before_dot, int pres, int neg_flag,
                 int add_point, int index) {
  int trans = 1;  // Переменная для переноса в процессе округления
  // Проходим по строке в обратном порядке и выполняем округление
  for (int i = count_before_dot + pres - 1 + add_point + neg_flag; i > 0; --i) {
    if (str[i] != '.') {
      int a = str[i] - '0';
      str[i] = (a + trans) % 10 + '0';  // Добавляем перенос и обновляем символ
      trans = (a + trans) / 10;  // Обновляем значение переноса
    }
  }
  // Обработка случаев округления
  if (trans == 1 && str[0] == '9') {
    // Если первый символ равен '9', то происходит перенос влево
    s21_shift_str(str, count_before_dot + pres - 1 + add_point + neg_flag);
    str[1] = '0';  // Вставляем '0' вместо '9'
    str[0] = '1';  // Устанавливаем новый первый символ как '1'
  } else if (trans == 1 && str[0] == '-') {
    // Если первый символ равен '-', значит, было отрицательное число
    // Выполняем аналогичный перенос влево
    s21_shift_str(str + 1, count_before_dot + pres + add_point + 1);
    str[1] = '1';  // Устанавливаем новый второй символ как '1'
    index++;  // Увеличиваем индекс
  } else if (trans == 1) {
    // Просто добавляем 1 к первому символу
    str[0] = str[0] + 1;
  }
  return index;  // Возвращаем обновленный индекс
}

// Обрабатывает случай, когда дробная часть числа близка к 1, выполняя
// округление.
void s21_process_bad_fraction(char *str, int count_before_dot, int neg_flag) {
  int trans = 1;
  // Начиная с конца числа, выполняем округление и перенос разряда.
  for (int i = count_before_dot + neg_flag - 1; i > 0; --i) {
    if (str[i] != '.' && str[i] != '-') {
      int a = str[i] - '0';
      str[i] = (a + trans) % 10 + '0';  // Вычисляем новое значение цифры.
      trans = (a + trans) / 10;  // Вычисляем перенос на следующий разряд.
    }
  }
}

// Преобразует дробную часть числа в строку с заданной точностью.
void s21_convert_fractional_part(long double *num2, char *str, int pres,
                                 int *index) {
  for (int i = 0; i < pres; ++i) {
    *num2 *= 10;
    int y = (int)*num2;
    *num2 -= y;
    str[(*index)++] =
        y + '0';  // Преобразование цифры в символ и добавление в строку.
  }
}

/**
 * Функция для преобразования числа типа long double в строку с заданной
 * точностью и опциональным флагом остроты.
 * @param num - число, которое будет преобразовано
 * @param str - указатель на строку, в которую будет записан результат
 * преобразования
 * @param pres - количество знаков после запятой (точности)
 * @param sharp_flag - флаг остроты (добавления десятичной точки, даже если
 * числа после нее нет)
 */
void s21_long_double_to_str(long double num, char *str, int pres,
                            int sharp_flag) {
  int count_before_dot = 0, index = 0, neg_flag = 0;
  long double num1 = 0, num2 = num;
  // Обработка отрицательных чисел
  if (num < 0) {
    str[index++] = '-';
    num *= -1;
    num2 *= -1;
    neg_flag = 1;
  }
  // Подсчет количества цифр до десятичной точки
  while (num >= 1) {
    num /= 10;
    count_before_dot++;
  }
  // Преобразование целой части числа в строку
  for (int i = 0; i < count_before_dot; ++i) {
    num *= 10;
    int y = (int)num;
    num1 = num1 * 10 + y;
    num -= y;
    str[index++] = y + '0';
  }
  // Обработка случая, когда целая часть числа равна 0
  if (count_before_dot == 0) {
    str[index++] = '0';
    count_before_dot = 1;
  }
  int add_point = 0;
  // Добавление точки (если задано) для десятичной части числа
  if (pres != 0 || sharp_flag == 1) {
    str[index++] = '.';
    add_point = 1;
  }
  // Преобразование десятичной части числа в строку с заданной точностью
  num2 -= num1;
  int flag_bad = 0;
  // Обработка случая, когда дробная часть числа равна 1
  if (num2 == 1.) {
    num2 = 0.;
    flag_bad = 1;
  }
  s21_convert_fractional_part(&num2, str, pres, &index);
  num2 *= 10;
  int y = (int)num2;
  // Округление числа
  if (y >= 5) {
    index =
        s21_rounding(str, count_before_dot, pres, neg_flag, add_point, index);
  }
  // Обработка флага bad для дробной части
  if (flag_bad == 1) {
    s21_process_bad_fraction(str, count_before_dot, neg_flag);
  }
  str[index] = '\0';  // Завершение строки
}

/**
 * Функция для обращения строки (реверса)
 * @param str - указатель на строку, которую нужно обратить
 * @param neg_flag - флаг, указывающий на отрицательное число
 * @return Указатель на обращенную строку (str)
 */
void *s21_reverse(char *str, int neg_flag) {
  if (str == NULL) return NULL;  // Проверка на NULL
  int bgn = 0;
  if (neg_flag == 1) bgn = 1;  // Если отрицательное число, начинаем с 1 символа
  int end = s21_strlen(str) - 1;  // Индекс последнего символа строки
  char temp;
  // Пока начальный индекс меньше конечного, меняем символы местами
  while (bgn < end) {
    temp = str[bgn];
    *(str + bgn) = *(str + end);
    *(str + end) = temp;
    bgn++;
    end--;
  }
  return str;  // Возвращаем указатель на обращенную строку
}

/**
 * Функция для заполнения указанной части строки пробелами.
 * @param str - указатель на строку, в которую будут добавлены пробелы
 * @param n - количество пробелов, которые нужно добавить
 * @param j - индекс начальной позиции в строке, с которой начнется добавление
 * пробелов
 * @return Количество добавленных пробелов (n)
 */
int s21_print_spaces(char *str, int n, int j) {
  for (int i = 0; i < n; i++) {
    str[j + i] = ' ';  // Заполнение символами пробела
  }
  return n;  // Возвращаем количество добавленных пробелов
}

/**
 * Функция для копирования части одной строки в другую строку.
 * @param str - указатель на строку, в которую будет скопирована часть другой
 * строки
 * @param strng_arg - указатель на исходную строку, из которой будет скопирована
 * часть
 * @param n - количество символов, которые нужно скопировать
 * @param j - индекс начальной позиции в строке, с которой начнется копирование
 * @return Количество скопированных символов (n)
 */
int s21_prep_string(char *str, char *strng_arg, int n, int j) {
  for (int i = 0; i < n; i++) {
    str[j + i] = strng_arg[i];  // Копирование символов из strng_arg в str
  }
  return n;  // Возвращаем количество скопированных символов
}
