#ifndef MESSAGE_RENDER_H
#define MESSAGE_RENDER_H

#include "GameLoop.h"
#include <iostream>
#include <string>
#include "imgui.h"

class MessageRenderer {
public:
    void renderMessage(const std::string& message);
    void attackMessage(GameLoop& game);
    // void showJson(GameLoop& game);
    void applyAbility(GameLoop& game);
    // void nextAbility(GameLoop& game);
    void getAbility(GameLoop& game);
    void displayHelp();
private:
    std::string lastMessage; // Последнее сообщение для отображения

};

#endif // MESSAGE_RENDER_H
