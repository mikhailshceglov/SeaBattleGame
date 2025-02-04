# Sea Battle Game

## Описание
Это консольная игра "Морской бой с модификациями", разработанная на C++ в рамках лабораторных работ. В игре реализованы механики кораблей, способностей и сохранения/загрузки состояния.

## Требования
- Компилятор C++ (GCC/G++)
- Make
- CMake (если используется для сборки)
- Библиотека nlohmann/json (для работы с JSON)
- Библиотека GLFW (если используется графический интерфейс)
- Библиотека GLEW (для работы с OpenGL)

## Установка
1. **Клонирование репозитория:**
   ```sh
   git clone https://github.com/mikhailshceglov/SeaBattleGame.git
   cd SeaBattleGame
   ```

2. **Сборка проекта (если используется CMake):**
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
   Или вручную скомпилировать основные файлы:
   ```sh
   g++ -o SeaBattleGame src/*.cpp -Iinclude -std=c++17
   ```

## Запуск
После успешной компиляции выполните:
```sh
./SeaBattleGame
```

## Функционал игры
- Расстановка кораблей на поле
- Атаки по вражескому полю
- Использование способностей (двойной урон, сканер, обстрел)
- Сохранение и загрузка игры

## Управление
- `a` — атака
- `s` — сохранить игру
- `l` — загрузить игру
- `h` — помощь
- `e` — выход

## Разработка
- Код разделён на классы: `Ship`, `GameField`, `AbilityManager`, `GameLoop` и другие
- Реализованы исключения для обработки ошибок
- Используется сериализация в JSON для сохранения состояния

## Лицензия
Проект распространяется под лицензией MIT.

---

Если возникли вопросы или предложения, пишите в Issues! 🚀

