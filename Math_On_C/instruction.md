# s21_math

## Содержание

1. [О проекте](#о-проекте)
2. [Навыки, полученные в ходе разработки](#навыки-полученные-закрепленные-в-ходе-разработки)
3. [Инструкция по сборке и запуску тестов](#инструкция-по-сборке-и-запуску-тестов)
4. [Команда разработчиков](#команда-разработчиков)

## О проекте

В данном проекте была разработана библиотека math.h на языке C. 
Эта библиотека реализует основные математические операции.

## Навыки, полученные (закрепленные) в ходе разработки
- Создание собственных типов данных
- Структурированное программирование
- Алгоритмы
- Создание и связывание статических библиотек, сборка проекта с помощью Makefile
- Тестирование с помощью библиотеки Check

<br>

## Инструкция по сборке и запуску тестов
## Список всех команд

| Действие                       | Команда                                         |
| ------------------------------ | ----------------------------------------------- |
| Сборка и запуск всех тестов    | `make all`                                      |
| Сборка библиотеки              | `make s21_math.a`                               |
| Запуск базовых тестов          | `make test;./test`                              |
| Формирование отчета о покрытии | `make gcov_report`                              |
| Рестарт проекта                | `make rebuild`                                  |
| Запуск отчистки                | `make clean`                                    |

<br>

## Зависимости

**Шаг 1:**
Установка LCOV (расширение GCOV)

```bash
sudo apt-get install lcov
```

**Шаг 2:**
Установка библиотеки check.h

```bash
sudo apt-get install check
```

<br>
<br>

### Сборка и запуск всех тестов

```bash
make all
```

---

### Сборка библиотеки

```bash
make s21_math.a
```

---

### Запуск базовых тестов

```bash
make test;./test
```

---

### Формирование отчета о покрытии

```bash
make gcov_report
```

---

### Рестарт проекта

```bash
make rebuild
```

---

### Запуск отчистки

```bash
make clean
```

<br>

## Команда разработчиков

<table>
    <tbody>
        <tr>
            <td align="center" valign="middle">
                <a href="https://github.com/NataliaOO" title="NataliaOO">
                    <img valign="middle" width="64px" height="64px" src="https://avatars.githubusercontent.com/u/44684427?s=400&u=dff2dba0b0ee76ede035b11cb12dde7aefccc0dc&v=4">
                </a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/GitLeviathan" title="GitLeviathan">
                    <img valign="middle" width="64px" height="64px" src="https://avatars.githubusercontent.com/u/103376432?v=4">
                </a>
            </td>
        </tr>
        <tr>
            <td align="center" valign="middle">
                <a href="https://github.com/NataliaOO" title="cheremshin">NataliaOO</a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/GitLeviathan" title="rozhnof">GitLeviathan</a>
            </td>
        </tr>
    </tbody>
</table>