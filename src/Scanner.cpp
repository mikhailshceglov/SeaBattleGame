// #include "Scanner.h"

// void Scanner::setCoordinates(int x, int y) {
//     x_ = x;
//     y_ = y;
// }

// void Scanner::useAbility(GameField& field, ShipManager& manager) {
//     std::cout << "Использована способность: сканер!" << std::endl;
//     for (int dx = 0; dx <= 1; dx++) {
//         for (int dy = 0; dy <= 1; dy++) {
//             int currentX = x_ + dx;
//             int currentY = y_ + dy;
//             if (field.isWithinBounds(currentX, currentY) && field.getCellStatus(currentX, currentY) == CellStatus::Ship) {
//                 std::cout << "Корабль найден на клетке (" << currentX << ", " << currentY << ")" << std::endl;
//             } else {
//                 std::cout << "В клетке (" << currentX << ", " << currentY << ") ничего нет" << std::endl;
//             }
//         }
//     }
// }

// std::string Scanner::getName() const {
//     return "Scanner";
// }

// // Клонирование объекта
// std::unique_ptr<Ability> Scanner::clone() const {
//     return std::make_unique<Scanner>(*this);
// }

#include "Scanner.h"

void Scanner::setCoordinates(int x, int y) {
    x_ = x;
    y_ = y;
}

void Scanner::useAbility(GameField& field, ShipManager& manager, GuiLogger& logger) {
    logger.addLog("Использована способность: Сканер!");
    for (int dx = 0; dx <= 1; dx++) {
        for (int dy = 0; dy <= 1; dy++) {
            int currentX = x_ + dx;
            int currentY = y_ + dy;
            if (field.isWithinBounds(currentX, currentY) && field.getCellStatus(currentX, currentY) == CellStatus::Ship) {
                logger.addLog("Корабль найден на клетке (" + std::to_string(currentX) + ", " + std::to_string(currentY) + ").");
            } else {
                logger.addLog("В клетке (" + std::to_string(currentX) + ", " + std::to_string(currentY) + ") ничего нет.");
            }
        }
    }
}

std::string Scanner::getName() const {
    return "Scanner";
}

// Клонирование объекта
std::unique_ptr<Ability> Scanner::clone() const {
    return std::make_unique<Scanner>(*this);
}
