// #ifndef GAME_CONTROLLER_H
// #define GAME_CONTROLLER_H

// #include <map>
// #include <functional>
// #include <string>
// #include <fstream>
// #include <nlohmann/json.hpp>
// #include "GameLoop.h"
// #include "input_render.h"
// #include "game_render.h"

// using json = nlohmann::json;

// // Шаблонный класс управления игрой
// template<typename InputMethod, typename Renderer>
// class GameController {
// private:
//     GameLoop& game; // Ссылка на основной игровой класс
//     InputMethod input_handler; // Объект для обработки ввода
//     Renderer renderer; // Объект для отображения игры
//     std::map<std::string, std::function<void()>> commands; // Карта доступных команд
//     std::map<char, std::string> commandMap; // Соответствие символов и команд

//     void initializeCommands(); // Метод для инициализации доступных команд
//     void loadCommandsFromJson(const std::string& filename); // Загрузка команд из JSON
//     void setDefaultCommands(); // Установка команд по умолчанию

// public:
//     GameController(GameLoop& game, InputMethod input, Renderer render);

//     void run(); // Основной цикл управления игрой
//     std::string handleInput(); // Метод для обработки пользовательского ввода
//     void executeCommand(const std::string& command); // Метод для выполнения команды
// };

// #include "../src/game_controller.hpp"

// #endif // GAME_CONTROLLER_H
