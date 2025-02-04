#ifndef DOUBLE_DAMAGE_H
#define DOUBLE_DAMAGE_H

#include "abilities.h"
#include <iostream>
#include <memory>
#include "gui_logger.h"

class DoubleDamage : public SetCoordinates {
private:
    int x_{0}, y_{0};

public:
    void setCoordinates(int x, int y) override;
    void useAbility(GameField& field, ShipManager& manager, GuiLogger& logger) override;
    std::string getName() const override;

    // Клонирование объекта способности
    std::unique_ptr<Ability> clone() const override;
};

#endif
