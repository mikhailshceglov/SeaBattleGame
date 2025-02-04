#include "input_render.h"
#include <iostream>
#include <limits>
#include "input_render.h"
#include <imgui.h>


std::string TerminalInputHandler::getInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void TerminalInputHandler::getCoordinates(int& x, int& y) {
    bool inputik = true;
    while (inputik) {
        std::cout << "Введите координаты (x y): ";
        std::cin >> x >> y;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Ошибка ввода. Введите два целых числа через пробел." << std::endl;
        } else {
            break;
        }
    }
}

// GUI
std::string GUIInputHandler::getInput() {
    // Пример: ввод текста через ImGui
    static char inputBuffer[128] = "";
    ImGui::InputText("Command Input", inputBuffer, IM_ARRAYSIZE(inputBuffer));
    return std::string(inputBuffer);
}

void GUIInputHandler::getCoordinates(int& x, int& y) {
    // Пример: ввод координат через ImGui
    static int tempX = 0, tempY = 0;
    ImGui::InputInt("X Coordinate", &tempX);
    ImGui::InputInt("Y Coordinate", &tempY);

    // Передача значений через параметры
    x = tempX;
    y = tempY;
}

