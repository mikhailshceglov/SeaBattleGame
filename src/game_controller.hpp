#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <map>
#include <functional>
#include <string>
#include <iostream>
#include "GameLoop.h"
#include "game_render.h"
#include "field_render.h"

// Шаблонный класс управления игрой
template<typename InputMethod, typename Renderer>
class GameController {
private:
    GameLoop& game; // Ссылка на основной игровой класс
    InputMethod input_handler; // Объект для обработки ввода
    Renderer renderer; // Объект для отображения игры
    std::map<std::string, std::function<void()>> commands; // Карта доступных команд

    void initializeCommands(); // Метод для инициализации доступных команд

public:
    GameController(GameLoop& game, InputMethod input, Renderer render);
    void executeCommand(const std::string& command, bool useAbility = false, int abilityX = 0, int abilityY = 0, int attackX = 0, int attackY = 0);
};

template<typename InputMethod, typename Renderer>
GameController<InputMethod, Renderer>::GameController(GameLoop& game, InputMethod input, Renderer render)
    : game(game), input_handler(input), renderer(render) {
    initializeCommands();
}

template<typename InputMethod, typename Renderer>
void GameController<InputMethod, Renderer>::initializeCommands() {
    commands["s"] = [&]() { game.saveGame(); };
    commands["l"] = [&]() { game.loadGame(); };
    commands["h"] = [&]() { renderer.displayHelp(); };
    commands["e"] = [&]() { std::exit(0); };
}

template<typename InputMethod, typename Renderer>
void GameController<InputMethod, Renderer>::executeCommand(const std::string& command, bool useAbility, int abilityX, int abilityY, int attackX, int attackY) {
    if (command == "a") {
        game.playPlayerTurn(useAbility, abilityX, abilityY, attackX, attackY);
    } else {
        auto it = commands.find(command);
        if (it != commands.end()) {
            it->second();
        } else {
            std::cerr << "Неизвестная команда: " << command << std::endl;
        }
    }
}

#endif
