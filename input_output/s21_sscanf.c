#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int count = 0;               // Счетчик успешных чтений %
  long all_symbols_count = 0;  // Для %n
  va_list valist;              // Список аргументов
  va_start(valist, format);  // Инициализация списка аргументов

  while (*format) {
    if (*format++ == '%') {
      long cycle_symbols_count = 0;  // Счетчик символов в текущем цикле
      char keys[] =
          "csdieEfgGouxXpn%";  // Ключи для определения типа спецификатора
      struct Arguments Arglist = {
          0, -1, '\0', 0};  // Структура для аргументов форматирования
      do {
        if (*format == '*')
          Arglist.asterisk = 1;  // Указательное чтение
        else if (s21_strchr("0123456789", *format))
          parse_width(&Arglist, *format);  // Обработка ширины
        else if (s21_strchr("hlL", *format))
          Arglist.modifier = *format;  // Обработка модификатора
        else if (*format == 'n') {
          process_format_n(&Arglist, &all_symbols_count, valist,
                           &str);  // Обработка %n
          count--;  // Уменьшение счетчика успешных чтений
        } else if (*format == '%') {
          process_percent_specifier(&Arglist, &all_symbols_count,
                                    &str);  // Обработка %%
        } else {
          cycle_symbols_count += process_format_specifier(
              valist, str, &Arglist,
              *format);  // Обработка других спецификаторов
          cycle_symbols_count += process_float_hex_specifier(
              valist, str, &Arglist, *format,
              &count);  // Обработка чисел с плавающей точкой и
                        // шестнадцатеричных чисел
        }
      } while (s21_strchr(keys, *format++) ==
               s21_NULL);  // Переход к следующему спецификатору
      if (Arglist.success == -1) break;  // Завершение, если чтение неуспешно
      if (Arglist.asterisk)
        Arglist.success = 0;  // Если было указательное чтение
      count += Arglist.success;  // Обновление счетчика успешных чтений
      str += cycle_symbols_count;  // Продвижение указателя на строку
      all_symbols_count += cycle_symbols_count;  // Обновление счетчика символов
    }
  }
  va_end(valist);  // Завершение обработки списка аргументов
  return count;  // Возвращаем количество успешных чтений
}

// Разбор ширины из форматной спецификации и обновление Arglist
void parse_width(struct Arguments *Arglist, char format_char) {
  if (Arglist->width == -1)
    Arglist->width = (format_char - '0');
  else
    Arglist->width = Arglist->width * 10 + (format_char - '0');
}

// Обработка форматной спецификации без ширины и модификатора
int process_format_specifier(va_list valist, const char *str,
                             struct Arguments *Arglist, char format) {
  int result = 0;  // Для остальных спецификаторов нет специфической обработки
  switch (format) {
    case 'd':
      result = case_d(valist, str, Arglist);
      break;
    case 'c':
      result = case_c(valist, str, Arglist);
      break;
    case 's':
      result = case_s(valist, str, Arglist);
      break;
    case 'u':
      result = case_u(valist, str, Arglist);
      break;
    case 'o':
      result = case_o(valist, str, Arglist);
      break;
    case 'i':
      result = case_i(valist, str, Arglist);
      break;
    case 'p':
      result = case_p(valist, str, Arglist);
      break;
  }
  return result;
}

// Обработка форматной спецификации с плавающей точкой или шестнадцатеричной
// записью
int process_float_hex_specifier(va_list valist, const char *str,
                                struct Arguments *Arglist, char format,
                                int *count) {
  int result = 0;  // Для остальных спецификаторов нет специфической обработки
  switch (format) {
    case 'e':
    case 'E':
    case 'g':
    case 'G':
    case 'f':
      result = case_f(valist, str, Arglist, count);
      break;
    case 'X':
    case 'x':
      result = case_x(valist, str, Arglist);
      break;
  }
  return result;
}

// Обработка спецификатора %n
void process_format_n(struct Arguments *Arglist, long *all_symbols_count,
                      va_list valist, const char **str) {
  while (**str == ' ') {
    (*str)++;
    (*all_symbols_count)++;
  }
  Arglist->success = 1;
  case_d_write_to_destination(valist, Arglist, all_symbols_count);
}

// Обработка спецификатора %
void process_percent_specifier(struct Arguments *Arglist,
                               long *all_symbols_count, const char **str) {
  while (**str == ' ' || **str == '%') {
    Arglist->success = 0;
    (*all_symbols_count)++;
    (*str)++;  // push through blank spaces
  }
}

// Преобразует последовательность цифр в беззнаковое длинное целое число
// из строки str с учетом указанных аргументов. Подсчитывает количество
// обработанных символов и обновляет флаг успеха в Arglist.
unsigned long long s21_sscanf_atoull(const char *str, struct Arguments *Arglist,
                                     int *symbols_counter) {
  unsigned long long res = 0;

  // Обработка цифр
  while (*str >= '0' && *str <= '9' && Arglist->width--) {
    res = res * 10 + (*str - '0');
    str++;
    (*symbols_counter)++;
    Arglist->success = 1;
  }

  return res;
}

// Преобразует последовательность цифр в знаковое длинное целое число
// из строки str с учетом указанных аргументов. Подсчитывает количество
// обработанных символов и обновляет флаг успеха в Arglist.
long s21_sscanf_atoi(const char *str, struct Arguments *Arglist,
                     int *symbols_counter) {
  long res = 0;
  int sign = 1;

  // Обработка знаков и пробелов
  while (*str == ' ' || *str == '-' || *str == '+') {
    if (*str == '-') {
      sign = -1;
      Arglist->width--;
    } else if (*str == '+') {
      Arglist->width--;
    }
    str++;
    (*symbols_counter)++;
  }

  // Преобразование к беззнаковому целому числу
  res = s21_sscanf_atoull(str, Arglist, symbols_counter);
  return res * sign;
}

// Функция обработки формата '%p'
int case_p(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_counter = 0;

  // Чтение шестнадцатеричного числа из строки
  long decimal = case_x_read(str, Arglist, &symbols_counter);

  if (Arglist->asterisk == 0) {
    void **destination = va_arg(valist, void **);
    *destination = (void *)(0x0 + decimal);
  }

  return symbols_counter;
}

// Функция обработки формата '%i'
int case_i(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_counter = 0;

  // Пропуск пробелов в начале строки
  while (*str == ' ') {
    str++;
    symbols_counter++;
  }

  // Определение формата числа
  if (*str == '0') {
    str++;
    symbols_counter++;

    if (*str == 'x') {
      // В случае 0x111 вызываем обработку шестнадцатеричного числа
      symbols_counter += case_x(valist, str, Arglist);
    } else {
      // В случае 0111 вызываем обработку восьмеричного числа
      symbols_counter += case_o(valist, str, Arglist);
    }
  } else if ((*str >= '0' && *str <= '9') || *str == '-' || *str == '+') {
    // В случае десятичного числа вызываем обработку десятичного числа
    symbols_counter += case_d(valist, str, Arglist);
  }

  return symbols_counter;
}

// Функция обработки формата '%x'
int case_x(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_counter = 0;

  // Чтение шестнадцатеричного числа из строки
  long decimal = case_x_read(str, Arglist, &symbols_counter);

  if (Arglist->asterisk == 0) {
    // Запись десятичного числа в пункт назначения (в аргумент)
    case_d_write_to_destination(valist, Arglist, &decimal);
  }

  return symbols_counter;
}

// Чтение шестнадцатеричного числа из строки
long case_x_read(const char *str, struct Arguments *Arglist,
                 int *symbols_counter) {
  long decimal = 0;
  int sign = 1;

  // Пропуск знаков и пробелов
  while (*str == ' ' || *str == '-' || *str == '+' || *str == '0' ||
         *str == 'x') {
    if (*str == '-') sign = -1;
    str++;
    (*symbols_counter)++;
  }

  char hex_num[50] = {'\0'};
  int i = 0;

  // Чтение шестнадцатеричного числа
  while ((*str && *str != ' ' && *str != '\n' && Arglist->width--) ||
         ((hex_num[i] >= '0' && hex_num[i] <= '9') ||
          (hex_num[i] >= 'a' && hex_num[i] <= 'f') ||
          (hex_num[i] >= 'A' && hex_num[i] <= 'F'))) {
    (*symbols_counter)++;
    hex_num[i++] = *str++;
  }

  int len = s21_strlen(hex_num);
  int temp = 0;

  // Преобразование шестнадцатеричного числа в десятичное
  for (i = 0; hex_num[i] != '\0'; i++) {
    if (hex_num[i] >= '0' && hex_num[i] <= '9') {
      temp = hex_num[i] - 48;
      Arglist->success = 1;
    } else if (hex_num[i] >= 'a' && hex_num[i] <= 'f') {
      temp = hex_num[i] - 87;
      Arglist->success = 1;
    } else if (hex_num[i] >= 'A' && hex_num[i] <= 'F') {
      temp = hex_num[i] - 55;
      Arglist->success = 1;
    }
    decimal += temp * pow(16, --len);
  }

  return decimal *= sign;
}

// Функция обработки формата '%o'
int case_o(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_counter = 0;

  // Чтение восьмеричного числа из строки
  long octal = s21_sscanf_atoi(str, Arglist, &symbols_counter);
  long decimal = 0;

  // Пропуск знаков и пробелов
  while (*str == ' ' || *str == '-' || *str == '+' || *str == '0') {
    str++;
  }

  int i = 0;

  // Преобразование восьмеричного числа в десятичное
  while (octal != 0 && Arglist->width--) {
    decimal = decimal + (octal % 10) * pow(8, i++);
    octal = octal / 10;
  }

  if (Arglist->asterisk == 0) {
    // Запись десятичного числа в пункт назначения (в аргумент)
    case_d_write_to_destination(valist, Arglist, &decimal);
  }

  return symbols_counter;
}

// Функция обработки формата '%u'
int case_u(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_counter = 0;

  if (Arglist->asterisk == 0) {
    if (Arglist->modifier == '\0') {
      unsigned int *destination = va_arg(valist, unsigned int *);
      long temp = s21_sscanf_atoi(str, Arglist, &symbols_counter);
      *destination = (unsigned int)temp;
    } else if (Arglist->modifier == 'h') {
      unsigned short *destination = va_arg(valist, unsigned short *);
      long temp = s21_sscanf_atoi(str, Arglist, &symbols_counter);
      *destination = (unsigned short)temp;
    } else if (Arglist->modifier == 'l') {
      unsigned long *destination = va_arg(valist, unsigned long *);
      long temp = s21_sscanf_atoull(str, Arglist, &symbols_counter);
      *destination = (unsigned long)temp;
    } else if (Arglist->modifier == 'L') {
      unsigned long long *destination = va_arg(valist, unsigned long long *);
      *destination = s21_sscanf_atoull(str, Arglist, &symbols_counter);
    }
  } else {
    // Пропуск символов, подсчет символов
    s21_sscanf_atoi(str, Arglist, &symbols_counter);
  }

  return symbols_counter;
}
// Обработка формата 'e' или 'E' внутри формата '%f'
int case_e(const char *str, long double *result, int *symbols_counter,
           struct Arguments *Arglist) {
  str++;  // Пропуск символа 'e'
  Arglist->width--;
  int e_symbols_counter =
      1;  // Счетчик символов 'e' (1, так как 'e' уже учтено)

  // Получение числа после "e+" или "e-", всегда положительное
  int n = s21_sscanf_atoi(str, Arglist, &e_symbols_counter);

  // Если символ после 'e' - это '+', или цифра от 0 до 9
  if (*str == '+' || (*str >= '0' && *str <= '9')) {
    while (n--)
      *result *= 10.0;  // Умножаем результат на 10 для положительного
                        // показателя степени
  } else if (*str == '-') {
    while (n++)
      *result /=
          10.0;  // Делим результат на 10 для отрицательного показателя степени
  }

  *symbols_counter +=
      e_symbols_counter;  // Увеличиваем счетчик символов для общего подсчета
  return e_symbols_counter;  // Возвращаем количество обработанных символов 'e'
                             // и показателя степени
}

// Обработка формата '%f' в функции printf
int case_f(va_list valist, const char *str, struct Arguments *Arglist,
           int *total_count) {
  int symbols_counter = 0;

  // Чтение числа до точки или 'e'
  long double left_from_dot_or_e =
      s21_sscanf_atoi(str, Arglist, &symbols_counter);
  long double result = left_from_dot_or_e;

  int sign = 1;
  const char *str_temp = str;
  while (*str_temp == ' ') str_temp++;
  if (*str_temp == '-') sign = -1;  // Учитываем знак числа

  str += symbols_counter;  // Перемещаем указатель str к точке или 'e'

  switch (*str) {
    case '.':
      str++;
      int symbols_to_right_of_dot = 0;  // Счетчик цифр после точки
      long double right_from_dot =
          s21_sscanf_atoi(str, Arglist, &symbols_to_right_of_dot);
      symbols_counter += symbols_to_right_of_dot + 1;  // +1 за саму точку

      for (int n = symbols_to_right_of_dot; n > 0; n--) right_from_dot /= 10;

      // Обработка случаев с нулем перед и после точки
      if (!left_from_dot_or_e && !right_from_dot && sign == -1)
        result = -0.0;
      else if (sign == -1)
        result -= right_from_dot;
      else
        result += right_from_dot;

      str += symbols_to_right_of_dot;
      break;
    case 'e':
    case 'E':
      // Обработка показателя степени
      if (Arglist->width == 1) {
        case_f_write_to_destination(valist, Arglist, &result);
        Arglist->success = -1;
        (*total_count)++;
        break;
      }
      str += case_e(str, &result, &symbols_counter, Arglist);
      break;
  }
  if (*str == 'e' || *str == 'E')
    case_e(str, &result, &symbols_counter, Arglist);

  // Запись результата в соответствующий тип в зависимости от модификатора
  if (Arglist->asterisk == 0 && Arglist->success)
    case_f_write_to_destination(valist, Arglist, &result);
  return symbols_counter;  // Возвращаем количество обработанных символов
}

// Функция для записи результата в соответствующий тип
void case_f_write_to_destination(va_list valist, struct Arguments *Arglist,
                                 long double *result) {
  if (Arglist->modifier == 'l') {
    double *destination = va_arg(valist, double *);
    *destination = (double)*result;
  } else if (Arglist->modifier == 'L') {
    long double *destination = va_arg(valist, long double *);
    *destination = (long double)*result;
  } else {
    float *destination = va_arg(valist, float *);
    *destination = (float)*result;
  }
}

// Обработка формата '%s'
int case_s(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_counter = 0;

  // Пропуск пробелов и символов новой строки
  while (*str == ' ' || *str == '\n') {
    str++;
    symbols_counter++;
  }

  // Если нет модификатора '*'
  if (Arglist->asterisk == 0) {
    if (Arglist->modifier == 'l') {
      wchar_t *destination = va_arg(valist, wchar_t *);
      // Копирование символов в широкую строку до достижения пробела или новой
      // строки, с учетом ширины
      while (*str && *str != ' ' && *str != '\n' && Arglist->width--) {
        symbols_counter++;
        *destination++ = *str++;
        Arglist->success = 1;
      }
      *destination = L'\0';  // Завершение широкой строки
    } else {
      char *destination = va_arg(valist, char *);
      // Копирование символов в строку до достижения пробела или новой строки, с
      // учетом ширины
      while (*str && *str != ' ' && *str != '\n' && Arglist->width--) {
        symbols_counter++;
        *destination++ = *str++;
        Arglist->success = 1;
      }
      *destination = '\0';  // Завершение строки
    }
  } else {
    // Если есть модификатор '*', копируем символы, игнорируя ширину
    while (*str && *str != ' ' && *str != '\n' && Arglist->width--) {
      str++;
      symbols_counter++;
      Arglist->success = 1;
    }
  }

  return symbols_counter;  // Возвращаем количество обработанных символов
}

// Обработка формата '%c'
int case_c(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_counter = 0;

  // Если задана ширина
  if (Arglist->width > 0) {
    symbols_counter +=
        case_s(valist, str, Arglist);  // Вызываем case_s для обработки символов
  } else if (Arglist->asterisk == 0) {
    if (Arglist->modifier == 'l') {
      wchar_t *destination = va_arg(valist, wchar_t *);
      *destination = *str;  // Присваиваем символ широкой строке
    } else {
      char *destination = va_arg(valist, char *);
      *destination = *str;  // Присваиваем символ строке
    }
    symbols_counter++;
    Arglist->success = 1;
  }
  return symbols_counter;  // Возвращаем количество обработанных символов
}

// Обработка формата '%d'
int case_d(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_counter = 0;

  // Извлечение целого числа из строки с обновлением счетчика символов
  long result = s21_sscanf_atoi(str, Arglist, &symbols_counter);

  // Если нет модификатора '*'
  if (Arglist->asterisk == 0)
    case_d_write_to_destination(
        valist, Arglist, &result);  // Запись результата в соответствующий тип

  return symbols_counter;  // Возвращаем количество обработанных символов
}

// Запись результата типа long int в соответствующий тип, в зависимости от
// модификатора
void case_d_write_to_destination(va_list valist, struct Arguments *Arglist,
                                 long int *result) {
  if (Arglist->modifier == '\0') {
    int *destination = va_arg(valist, int *);
    *destination = (int)*result;  // Присваиваем целое число типа long int
                                  // целочисленной переменной
  } else if (Arglist->modifier == 'h') {
    short *destination = va_arg(valist, short *);
    *destination = (short)*result;  // Присваиваем целое число типа long int
                                    // переменной типа short
  } else if (Arglist->modifier == 'l') {
    long *destination = va_arg(valist, long *);
    *destination = (long)*result;  // Присваиваем целое число типа long int
                                   // переменной типа long
  }
}
