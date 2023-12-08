#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dest_end = dest + s21_strlen(dest);
  // Копируем не более n символов из строки src в конец строки dest,
  // обновляя dest_end и src на каждом шаге
  while (n > 0 && *src != '\0') {
    *dest_end = *src;
    dest_end++;
    src++;
    n--;
  }
  // Добавляем завершающий нулевой символ к концу строки dest
  *dest_end = '\0';
  return dest;
}
