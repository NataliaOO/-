#ifndef _S21_STRING_H_
#define _S21_STRING_H_

typedef long unsigned s21_size_t;
typedef long unsigned int s21_size_t;

#define s21_NULL ((void *)0)

// функции копирования
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);

// функции поиска
void *s21_memchr(const void *str, int c, s21_size_t n);
char *s21_strrchr(const char *str, int c);
char *s21_strchr(const char *str, int c);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);

// функции сравнения
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

// функции вычисления
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strcspn(const char *str1, const char *str2);

// функции дополнительные
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strerror(int errnum);
char *s21_strtok(char *str, const char *delim);

// функции - sprintf, sscanf
int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

// дополнительные функции не входящие в стандартную библиотеку
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
// Функция для преобразования строки в верхний/нижний регистр
void *s21_change_case_str(const char *str, int to_upper);

#endif  // _S21_STRING_H_