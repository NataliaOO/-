# s21_SmartCalc

## Содержание

1. [О проекте](#о-проекте)
2. [Навыки, полученные в ходе разработки](#навыки-полученные-закрепленные-в-ходе-разработки)
3. [Инструкция по сборке и запуску тестов](#инструкция-по-сборке-и-запуску-тестов)
4. [Команда разработчиков](#команда-разработчиков)

## О проекте

В данном проекте была разработана расширенная версия обычного калькулятора, который можно найти в стандартных приложениях каждой операционной системы на языке программирования C с использованием структурного программирования.

## Навыки, полученные (закрепленные) в ходе разработки
- Создание собственных типов и структуры данных
- Структурированное программирование
- Алгоритмы
- Тестирование с помощью библиотеки Check

<br>

## Инструкция по сборке и запуску тестов
## Список всех команд

| Действие                       | Команда                                         |
| ------------------------------ | ----------------------------------------------- |
| Сборка и запуск всех тестов    | `make all`                                      |
| Cборка проекта                 | `make install`                                  |
| Архивирует проект              | `make dist`                                     |
| Формироование отчета           | `make dvi`                                      |
| Запуск базовых тестов          | `make test`                                     |
| Проверка кода на стиль Google  | `make lint`                                     |
| Форматироваание кода (Google-style) |   `make lint-fix`                          | 
| Формирование отчета о покрытии | `make gcov_report`                              |
| Удаление проекта               | `make uninstall`                                |
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
**Шаг 3:**
Установка doxygen

```bash
sudo apt install doxygen
```

**Шаг 4:**
Установка zip

```bash
sudo apt install zip
```

**Шаг 5:**
Установка QT

```bash
sudo apt install qt5-default
sudo apt install qtcreator
sudo apt install libqt5multimedia5-plugins
sudo apt install qtwebengine5-dev
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
        </tr>
        <tr>
            <td align="center" valign="middle">
                <a href="https://github.com/NataliaOO" title="cheremshin">NataliaOO</a>
            </td>
        </tr>
    </tbody>
</table>