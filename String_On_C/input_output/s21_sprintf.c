#include "s21_sprintf.h"

#include "../s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;            // указатель на аргументы
  va_start(args, format);  // выделение памяти для arg
  int result = s21_parser(str, format, args);
  va_end(args);  // очищение памяти
  return result;
}

int s21_parser(char *str, const char *format, va_list args) {
  int i = 0;
  int counter_symbols_str = 0;

  while (format[i] != '\0') {
    if (format[i] != '%') {
      str[counter_symbols_str] = format[i];
      counter_symbols_str++;
    } else {
      Prototype prot = {'\0', 0, 0, 0, 0, 0, 0, 0, -1, -1, '\0'};
      // Обработка спецификатора и его параметров
      i = s21_read_format(&prot, format, i, args);

      if (prot.spec == '%') {
        str[counter_symbols_str] = format[i];
        counter_symbols_str++;
      } else {
        // преобразования аргументов в     строку и их добавления в str
        counter_symbols_str =
            s21_args_to_str(counter_symbols_str, str, &prot, args);
      }
    }
    i++;
  }
  str[counter_symbols_str] = '\0';
  // Возвращается количество символов, добавленных в str
  return counter_symbols_str;
}

// Обработка флагов
char *s21_flag_handler(char *str, Prototype *prot) {
  int negativ_num = (*str == '-') ? 1 : 0;
  char *str_tmp = (char *)malloc(s21_strlen(str) + 1);
  // Копирование строки с пропуском первого символа при наличии минуса
  for (int i = negativ_num; i < (int)s21_strlen(str) + 1; ++i) {
    str_tmp[i - negativ_num] = str[i];
  }
  // Установка ширины поля для вывода
  prot->width_number =
      (prot->width_number != 0) ? prot->width_number : prot->width_star;
  str = str_tmp;
  // Сброс точности для определенных спецификаторов
  if (s21_strchr("fgGeE", prot->spec)) {
    prot->prec_number = -1;
  }
  // Сброс флагов для определенных спецификаторов
  if (s21_strchr("ouxX", prot->spec)) {
    prot->plus_flag = 0;
    prot->space_flag = 0;
  }
  if (prot->spec != 's') {
    if (prot->prec_number != -1) {
      if (prot->prec_number != -1 &&
          // Обработка целых чисел]
          s21_strchr("dniouxxX", prot->spec)) {
        if (prot->prec_number > (int)s21_strlen(str)) {
          str = s21_add_char_left(str,
                                  prot->prec_number - (int)s21_strlen(str) - 1,
                                  (int)s21_strlen(str) + 1, '0', *prot);
        }
      }
      // Добавление решетки для определенных спецификаторов
      if (prot->sharp_flag) {
        str = s21_add_sharp_sign(str, *prot);
      }
      // Обработка ширины поля вывода
      str = (prot->width_number != 0 || prot->width_star != 0)
                ? s21_n_shift(str, negativ_num, *prot)
                : s21_add_sign_or_space(str, *prot, negativ_num);
    } else {
      if (prot->sharp_flag) {
        str = s21_add_sharp_sign(str, *prot);
      }
      str = (prot->width_number != 0 || prot->width_star != 0)
                ? s21_n_shift(str, negativ_num, *prot)
                : s21_add_sign_or_space(str, *prot, negativ_num);
    }
  } else {
    // Обработка спецификатора 's'
    if (!prot->minus_flag) {
      if (prot->width_number > (int)s21_strlen(str)) {
        str = s21_add_char_left(str,
                                prot->width_number - (int)s21_strlen(str) - 1,
                                (int)s21_strlen(str) + 1, ' ', *prot);
      }
    } else {
      if (prot->width_number > (int)s21_strlen(str)) {
        str = s21_add_char_right(str,
                                 prot->width_number - (int)s21_strlen(str) - 1,
                                 (int)s21_strlen(str) + 1, ' ');
      }
    }
  }
  str = s21_add_char_right(str, 1, s21_strlen(str) + 1, '\0');
  return str;
}

// Добавляет решетку (или не добавляет) к строке в зависимости от спецификатора
// и значений параметров форматирования
char *s21_add_sharp_sign(char *str, Prototype prot) {
  char *res;
  if ((prot.spec == 'o' || prot.spec == 'x' || prot.spec == 'X') &&
      *str == '0' && s21_strlen(str) == 1) {
    // Создание новой строки такой же длины как исходная и копирование исходной
    // строки
    res = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    s21_memcpy(res, str, s21_strlen(str) + 1);
  } else if ((prot.spec == 'o' &&
              (prot.prec_number == -1 || prot.prec_number == 0)) ||
             prot.spec == 'x' || prot.spec == 'X') {
    int n = prot.spec == 'o' ? 1 : 2;
    // Создание новой строки с дополнительным местом для решетки и символа '\0'
    res = (char *)malloc((s21_strlen(str) + 1 + n) * sizeof(char));
    // Копирование символов из исходной строки с соответствующим сдвигом
    for (int i = n; i < (int)s21_strlen(str) + 2; i++) {
      res[i] = str[i - n];
    }
    if (prot.spec == 'o') {
      res[0] = '0';
    } else if (prot.spec == 'x' || prot.spec == 'X') {
      res[0] = '0';
      res[1] = prot.spec;
    }
    res[s21_strlen(str) + n] = '\0';
  } else {
    res = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    s21_memcpy(res, str, s21_strlen(str) + 1);
  }
  return res;
}

// Выполняет выравнивание и добавление пробелов или нулей в строку с учетом
// ширины поля
char *s21_n_shift(char *str, int negativ_num, Prototype prot) {
  int sign_size = 0;
  if (negativ_num == 1 || prot.plus_flag == 1 || prot.space_flag) {
    sign_size = 1;
  }
  if (prot.minus_flag == 1) {
    if ((int)s21_strlen(str) >= (prot.width_number + prot.width_star)) {
      str = s21_add_sign_or_space(str, prot, negativ_num);
    } else {
      int str_size = s21_strlen(str);
      str = s21_add_sign_or_space(str, prot, negativ_num);
      // Добавление пробелов справа до достижения заданной ширины
      str =
          s21_add_char_right(str, prot.width_number - str_size - 1 - sign_size,
                             str_size + 1 + sign_size, ' ');
    }
  } else {
    if ((int)s21_strlen(str) >= prot.width_number) {
      str = s21_add_sign_or_space(str, prot, negativ_num);
    } else {
      if (prot.zero_flag || *str == '0') {
        str = s21_add_char_left(
            str, prot.width_number - s21_strlen(str) - 1 - sign_size,
            s21_strlen(str) + 1, ' ', prot);
        str = s21_add_sign_or_space(str, prot, negativ_num);
      } else {
        int str_size = s21_strlen(str);
        str = s21_add_sign_or_space(str, prot, negativ_num);
        // Добавление пробелов слева до достижения заданной ширины
        str =
            s21_add_char_left(str, prot.width_number - str_size - 1 - sign_size,
                              str_size + 1 + sign_size, ' ', prot);
      }
    }
  }
  return str;
}

// Добавляет знак или пробел к строке в зависимости от наличия флагов
// форматирования и знака числа, которое должно быть выведено
char *s21_add_sign_or_space(char *buf_str, Prototype prot, int sign) {
  char *res;
  // Проверка наличия флагов '+' или 'space' и необходимости добавления знака
  if (prot.plus_flag == 1 || sign == 1 || prot.space_flag) {
    int str_size = s21_strlen(buf_str);
    res = (char *)malloc((str_size + 2) * sizeof(char));
    // Копирование символов из исходной строки с соответствующим сдвигом
    for (int i = 1; i < str_size + 2; i++) {
      res[i] = buf_str[i - 1];
    }
    // Определение, какой знак должен быть добавлен
    if (sign == 1) {  // если отрицательное число то по дефолту ставим -
      res[0] = '-';
    } else if (sign == 0 && prot.plus_flag) {
      res[0] = '+';
    } else if (sign == 0 && !prot.plus_flag && prot.space_flag) {
      res[0] = ' ';
    }
  } else {
    int str_size = s21_strlen(buf_str);
    res = (char *)malloc((str_size + 1) * sizeof(char));
    s21_memcpy(res, buf_str, s21_strlen(buf_str) + 1);
  }

  return res;
}

// Добавляет символы слева от строки для выравнивания
char *s21_add_char_left(char *str, int n, int str_size, char c,
                        Prototype prot) {
  if (prot.zero_flag == 1) {
    c = '0';
  }
  int j = str_size - 1;
  // Создаем новую строку с достаточным пространством для добавления символов
  char *res = (char *)malloc((str_size + n + 1) * sizeof(char));

  for (int i = str_size + n; i >= 0; i--) {
    res[i] = (j >= 0) ? (str[j--]) : c;
  }
  res[str_size + n] = '\0';  // Завершаем новую строку символом '\0'
  return res;
}

// Добавляет символы справа от строки для выравнивания
char *s21_add_char_right(char *str, int n, int str_size, char c) {
  char *res = (char *)malloc((str_size + n + 1) * sizeof(char));
  for (int i = 0; i < str_size + n; i++) {
    res[i] = (i < str_size - 1) ? str[i] : c;
  }
  res[str_size + n] = '\0';
  return res;
}

// Получения параметров форматирования
int s21_read_format(Prototype *prot, const char *format, int i, va_list args) {
  int this_is_width = 0;
  int this_is_prec = 0;
  i++;
  while (format[i]) {
    s21_check_flags(format, i, prot, &this_is_prec, &this_is_width);  // Флаги
    s21_check_width(format, i, &this_is_width, prot, args);    // Ширина
    i = s21_check_prec(format, i, &this_is_prec, prot, args);  // Точность
    // Проверяем модификаторы
    if (format[i] == 'h') {
      prot->length = format[i];
    } else if (format[i] == 'l') {
      prot->length = format[i];
    } else if (format[i] == 'L') {
      prot->length = format[i];
    }
    // Проверяем спецификатор
    if (s21_strchr("cdieEfgGosuxXpn%", format[i])) {
      prot->spec = format[i];
    }
    if (prot->spec == format[i])
      break;  // выходим нашелся спецификатор
    else
      i++;  // продолжаем дальше обрабатывать прототип спецификатора
  }
  return i;
}

// Проверяет наличие точности в форматной строке
int s21_check_prec(const char *format, int i, int *this_is_prec,
                   Prototype *prot, va_list args) {
  if (format[i] == '.') {
    i++;
    // Проверяем, есть ли числовое значение точности после точки
    if (s21_check_number(format, i) == true && *this_is_prec == 0) {
      prot->prec_number = s21_write_number(format, &i);
      *this_is_prec = 1;
    } else if (format[i] == '*' && *this_is_prec == 0) {
      // Если встречаем '*' после точки, получаем значение точности из
      // аргументов
      prot->prec_star = va_arg(args, int);
      prot->prec_number = prot->prec_star;
      *this_is_prec = 1;
    } else if (*this_is_prec == 0)
      prot->prec_number = 0;
  }
  return i;
}

// Проверяет наличие ширины в форматной строке
void s21_check_width(const char *format, int i, int *this_is_width,
                     Prototype *prot, va_list args) {
  // Если ширина ещё не установлена и встречаем '*', извлекаем значение из
  // аргументов
  if (prot->width_number == 0 && format[i] == '*' && *this_is_width == 0) {
    prot->width_star = va_arg(args, int);
    *this_is_width = 1;
  }
  // Если ширина ещё не установлена и встречаем числовое значение,
  // извлекаем его и обновляем структуру Prototype
  if (s21_check_number(format, i) == true && *this_is_width == 0) {
    prot->width_number = s21_write_number(format, &i);
    *this_is_width = 1;
  }
}

// Проверяет наличие флагов форматирования в форматной строке
void s21_check_flags(const char *format, int i, Prototype *prot,
                     int *this_is_prec, int *this_is_width) {
  if (format[i] == '+') {
    prot->plus_flag = 1;
  } else if (format[i] == '-') {
    prot->minus_flag = 1;
  } else if (format[i] == ' ') {
    prot->space_flag = 1;
  } else if (format[i] == '#') {
    prot->sharp_flag = 1;  // Устанавливаем флаг "решетка"
  } else if (format[i] == '0' && *this_is_prec == 0 && *this_is_width == 0) {
    prot->zero_flag = 1;
  }
}

// Проверяет, является ли символ числовым символом (от '0' до '9')
bool s21_check_number(const char *format, int i) {
  bool result = false;
  if (format[i] >= '0' && format[i] <= '9') result = true;
  return result;
}

// Считывает число из форматной строки, начиная с указанного индекса,
// и возвращает это число в виде целого числа
int s21_write_number(const char *format, int *i) {
  int width = 0;
  // Преобразуем первый символ в число и добавляем к нему
  // для начального значения ширины
  width += format[*i] - '0';
  *i += 1;
  // Продолжаем считывать символы и добавлять к числу, умножая на 10
  // для получения полного значения числа
  while (s21_check_number(format, *i) == true) {
    width *= 10;
    width += format[*i] - '0';
    *i += 1;
  }
  return width;
}

// Форматирует аргументы и вставляет их в строку с учетом параметров
// форматирования
int s21_args_to_str(int counter_symbols_str, char *str, Prototype *prot,
                    va_list args) {
  // Временный массив для хранения строки без параметров форматирования
  char intermediate_str[4096] = {'\0'};
  char *res = s21_NULL;
  int tmp = 0;
  if (prot->spec == 'c') {
    tmp = s21_specifier_c(intermediate_str, args, prot);
    res = intermediate_str;
  } else if (prot->spec == 'd' || prot->spec == 'i') {
    s21_specifier_id(args, prot, intermediate_str);
    res = s21_flag_handler(intermediate_str, prot);
  } else if (prot->spec == 's') {
    s21_specifier_s(intermediate_str, args, prot);
    res = s21_flag_handler(intermediate_str, prot);
  } else if (prot->spec == 'n') {
    s21_specifier_n(args, counter_symbols_str);
    res = intermediate_str;
  } else if (prot->spec == 'x') {
    s21_specifier_x(intermediate_str, args, *prot);
    res = s21_flag_handler(intermediate_str, prot);
  } else if (prot->spec == 'X') {
    s21_specifier_X(intermediate_str, args, *prot);
    res = s21_flag_handler(intermediate_str, prot);
  } else if (prot->spec == 'o') {
    s21_specifier_o(intermediate_str, args, *prot);
    res = s21_flag_handler(intermediate_str, prot);
  } else if (prot->spec == 'u') {
    s21_specifier_u(intermediate_str, args, *prot);
    res = s21_flag_handler(intermediate_str, prot);
  } else if (prot->spec == 'f') {
    s21_specifier_f(intermediate_str, args, *prot);
    res = s21_flag_handler(intermediate_str, prot);
  } else if (prot->spec == 'p') {
    s21_specifier_p(args, intermediate_str, prot);
    res = intermediate_str;
  } else if (s21_strchr("eEgG", prot->spec)) {
    s21_specifier_e(counter_symbols_str, intermediate_str, args, prot);
    res = s21_flag_handler(intermediate_str, prot);
  }
  int index = 0;
  // Вставляем сформатированную строку в основную строку
  while (res[index] != '\0') {
    str[counter_symbols_str++] = res[index++];
  }
  str[counter_symbols_str] = '\0';
  // Освобождаем память, если это были динамически выделенные данные
  if (s21_strchr("fuoxXdiseEgG", prot->spec)) {
    free(res);
  }
  // Увеличиваем счетчик символов, если tmp == -1 (для спецификатора 'n')
  if (tmp == -1) {
    counter_symbols_str++;
  }
  return counter_symbols_str;
}
