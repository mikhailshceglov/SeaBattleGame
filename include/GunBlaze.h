#ifndef GUNBLAZE_H
#define GUNBLAZE_H

#include "abilities.h"
#include <iostream>
#include <random>

class GunBlaze : public Ability {
public:
    void useAbility(GameField& field, ShipManager& manager, GuiLogger& logger) override;

    std::string getName() const override;

    // Реализация метода клонирования
    std::unique_ptr<Ability> clone() const override;
};

#endif
