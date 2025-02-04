#ifndef INPUT_RENDER_H
#define INPUT_RENDER_H

#include <string>
#include <memory>
#include "imgui.h" // Подключение Dear ImGui

class InputHandler {
public:
    virtual ~InputHandler() = default;

    virtual std::string getInput() = 0; // Для общего ввода
    virtual void getCoordinates(int& x, int& y) = 0;
};


// Класс для терминального ввода
class TerminalInputHandler : public InputHandler {
public:
    std::string getInput() override;
    void getCoordinates(int &x, int &y);
};

// Класс для ввода с GUI
class GUIInputHandler : public InputHandler {
public:
    std::string getInput() override;
    void getCoordinates(int& x, int& y) override;
};

#endif
