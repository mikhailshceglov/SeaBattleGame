#ifndef GAME_RENDERER_HPP
#define GAME_RENDERER_HPP

#include "game_render.h"
#include "field_render.hpp"
#include <iostream>


// Конструктор, принимающий игру и рендереры
template<typename FieldRenderer, typename MessageRenderer>
GameRenderer<FieldRenderer, MessageRenderer>::GameRenderer(GameLoop& game, FieldRenderer field_renderer, MessageRenderer message_renderer)
    : game(game), field_renderer(field_renderer), message_renderer(message_renderer) {}

// Метод для отображения игрового поля
template<typename FieldRenderer, typename MessageRenderer>
void GameRenderer<FieldRenderer, MessageRenderer>::renderField() {
    field_renderer.drawField(*game.playerField, *game.enemyField); // Передача полей игрока и врага в рендерер
}

// Метод для отображения сообщения
template<typename FieldRenderer, typename MessageRenderer>
void GameRenderer<FieldRenderer, MessageRenderer>::displayMessage(const std::string& message) {
    message_renderer.renderMessage(message); // Вызов метода рендера сообщения
}


template<typename FieldRenderer, typename MessageRenderer>
void GameRenderer<FieldRenderer, MessageRenderer>::displayHelp() {
    message_renderer.displayHelp();
}


// Метод для обновления отображения
template<typename FieldRenderer, typename MessageRenderer>
void GameRenderer<FieldRenderer, MessageRenderer>::update() {
    renderField();
}

#endif
