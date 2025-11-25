# kubsh — Учебный шелл на C++[![progress-banner](https://backend.codecrafters.io/progress/shell/29322007-ccf1-4aec-bbf8-ad5b3f552236)](https://app.codecrafters.io/users/codecrafters-bot?r=2qF)



Собственная реализация командной оболочки (shell) с поддержкой виртуальной файловой системы пользователей через FUSE.This is a starting point for C++ solutions to the

["Build Your Own Shell" Challenge](https://app.codecrafters.io/courses/shell/overview).

## Возможности

In this challenge, you'll build your own POSIX compliant shell that's capable of

- ✅ Ввод команд в интерактивном режимеinterpreting shell commands, running external programs and builtin commands like

- ✅ Выход по `Ctrl+D` или команде `\q`cd, pwd, echo and more. Along the way, you'll learn about shell command parsing,

- ✅ История команд (`history`), сохраняется в `~/kubsh_history`REPLs, builtin commands, and more.

- ✅ Встроенная команда `echo`

- ✅ Вывод переменных окружения (`\e $PATH`) — списком, если есть `:`**Note**: If you're viewing this repo on GitHub, head over to

- ✅ Запуск внешних программ (поиск в `$PATH`)[codecrafters.io](https://codecrafters.io) to try the challenge.

- ✅ Обработка сигнала `SIGHUP` — выводит "Configuration reloaded"

- ✅ Просмотр таблицы разделов MBR (`\l /dev/sda`)# Passing the first stage

- ✅ VFS с информацией о пользователях через FUSE

The entry point for your `shell` implementation is in `src/main.cpp`. Study and

## VFS пользователейuncomment the relevant code, and push your changes to pass the first stage:



При запуске kubsh автоматически монтируется виртуальная файловая система в директорию `users/`:```sh

git commit -am "pass 1st stage" # any msg

```git push origin master

users/```

├── root/

│   ├── id        # UID пользователяTime to move on to the next stage!

│   ├── home      # домашний каталог

│   └── shell     # путь до шелла# Stage 2 & beyond

├── youminava/

│   ├── idNote: This section is for stages 2 and beyond.

│   ├── home

│   └── shell1. Ensure you have `cmake` installed locally

└── ...1. Run `./your_program.sh` to run your program, which is implemented in

```   `src/main.cpp`.

1. Commit your changes and run `git push origin master` to submit your solution

### Операции с VFS   to CodeCrafters. Test output will be streamed to your terminal.


```bash
ls users/                    # список пользователей
cat users/root/id            # показать UID пользователя
cat users/root/home          # показать домашний каталог
mkdir users/newuser          # создать нового пользователя (вызывает useradd)
rmdir users/newuser          # удалить пользователя (вызывает userdel)
```

> ⚠️ Для создания/удаления пользователей требуются права root и доступ к FUSE (`/dev/fuse`)

## Сборка

### Зависимости

```bash
# Debian/Ubuntu
sudo apt install g++ make libfuse3-dev

# Arch Linux
sudo pacman -S gcc make fuse3
```

### Компиляция

```bash
make build    # скомпилировать
make run      # запустить
make deb      # собрать deb-пакет
make clean    # очистить
```

## Использование

### Запуск

```bash
./kubsh           # обычный запуск
sudo ./kubsh      # с правами root (для VFS mkdir/rmdir)
```

### Встроенные команды

| Команда | Описание |
|---------|----------|
| `echo <текст>` | Вывести текст |
| `\q` | Выйти из шелла |
| `history` | Показать историю команд |
| `\e $VAR` | Вывести переменную окружения (списком по `:`) |
| `\l /dev/sda` | Показать таблицу разделов MBR |

### Примеры

```bash
$ echo Hello World
Hello World

$ \e $PATH
/usr/local/bin
/usr/bin
/bin

$ ls users/
root youminava

$ cat users/root/shell
/bin/bash

$ \q
```

## CI/CD

Проект настроен для GitLab CI/CD с тремя этапами:
1. **build** — компиляция
2. **test** — запуск тестов
3. **package** — сборка deb-пакета

> Для прохождения VFS-тестов GitLab Runner должен быть настроен с `privileged = true`

## Структура проекта

```
├── src/
│   ├── main.cpp        # основной код шелла
│   └── vfs.cpp         # FUSE VFS реализация
├── kubsh-package/
│   └── DEBIAN/control  # метаданные deb-пакета
├── Makefile            # сборка
├── .gitlab-ci.yml      # CI/CD конфигурация
└── README.md
```

## Требования

- C++17
- libfuse3
- Linux (FUSE — только для Linux)
- Для VFS mkdir/rmdir: root права + доступ к /dev/fuse

## Лицензия

Учебный проект.
