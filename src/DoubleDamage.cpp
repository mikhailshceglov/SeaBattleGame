#include "DoubleDamage.h"

void DoubleDamage::setCoordinates(int x, int y) {
    x_ = x;
    y_ = y;
}

void DoubleDamage::useAbility(GameField& field, ShipManager& manager, GuiLogger& logger) {
    logger.addLog("Использована способность: Двойной урон!");
    if (field.isWithinBounds(x_, y_)) {
        field.attack(x_, y_, manager);
        logger.addLog("Первый урон нанесен по координатам (" + std::to_string(x_) + ", " + std::to_string(y_) + ").");
        field.attack(x_, y_, manager);
        logger.addLog("Второй урон нанесен по координатам (" + std::to_string(x_) + ", " + std::to_string(y_) + ").");
    } else {
        logger.addLog("Координаты вне поля. Способность не может быть применена.");
    }
}

std::string DoubleDamage::getName() const {
    return "Double Damage";
}

std::unique_ptr<Ability> DoubleDamage::clone() const {
    return std::make_unique<DoubleDamage>(*this);
}
