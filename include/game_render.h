#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include "GameLoop.h"
#include <string>
#include "imgui.h"

// Шаблонный класс для визуализации игры
template<typename FieldRenderer, typename MessageRenderer>
class GameRenderer {
private:
    GameLoop& game;
    FieldRenderer field_renderer;
    MessageRenderer message_renderer; 

public:
    // Конструктор, принимающий игру и экземпляры рендереров
    GameRenderer(GameLoop& game, FieldRenderer field_renderer, MessageRenderer message_renderer);

    void renderField();
    void displayMessage(const std::string& message);
    void displayHelp();
    void update();
};

#include "../src/game_render.hpp"

#endif 
