// #include "message_render.h"
// #include "GameState.h"
// #include "abilityManager.h"
// #include <iostream>
// #include <string>

// void MessageRenderer::renderMessage(const std::string& message) {
//     std::cout << message << std::endl;
// }

// void MessageRenderer::attackMessage(GameLoop& game) {
//     std::cout << "Атака произведена!" << std::endl;
// }

// void MessageRenderer::applyAbility(GameLoop& game) {
//     std::cout << "Способность применена!" << std::endl;
// }

// void MessageRenderer::getAbility(GameLoop& game) {
//     AbilityManager& ability_manager = game.getAbilityManager();
//     std::cout << "Получена новая способность!" << std::endl;
// }

// void MessageRenderer::displayHelp() {
//     std::cout << "Доступные команды:" << std::endl;
//     std::cout << "  attack (a)      - Атаковать вражеское поле" << std::endl;
//     std::cout << "  save (s)        - Сохранить текущую игру" << std::endl;
//     //std::cout << "  load (l)        - Загрузить сохраненную игру" << std::endl;
//     std::cout << "  help (h)        - Показать список команд" << std::endl;
//     std::cout << "  exit (e)        - Выйти из игры" << std::endl;
// }

#include "message_render.h"
#include "GameState.h"
#include "abilityManager.h"
#include <string>

void MessageRenderer::renderMessage(const std::string& message) {
    lastMessage = message;

    // GUI: отображение сообщения
    ImGui::Begin("Сообщения");
    ImGui::Text("%s", lastMessage.c_str());
    ImGui::End();
}

void MessageRenderer::attackMessage(GameLoop& game) {
    renderMessage("Атака произведена!");
}

void MessageRenderer::applyAbility(GameLoop& game) {
    renderMessage("Способность применена!");
}

void MessageRenderer::getAbility(GameLoop& game) {
    AbilityManager& ability_manager = game.getAbilityManager();
    renderMessage("Получена новая способность!");
}

void MessageRenderer::displayHelp() {
    ImGui::Begin("Справка");

    ImGui::Text("Доступные команды:");
    ImGui::BulletText("attack (a)      - Атаковать вражеское поле");
    ImGui::BulletText("save (s)        - Сохранить текущую игру");
    // ImGui::BulletText("load (l)        - Загрузить сохраненную игру");
    ImGui::BulletText("help (h)        - Показать список команд");
    ImGui::BulletText("exit (e)        - Выйти из игры");

    ImGui::End();
}
