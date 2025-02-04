#ifndef SCANNER_H
#define SCANNER_H

#include "abilities.h"
#include <iostream>
#include "gui_logger.h"

class Scanner : public SetCoordinates {
private:
    int x_;
    int y_;

public:
    void setCoordinates(int x, int y) override;
    
    void useAbility(GameField& field, ShipManager& manager, GuiLogger& logger) override;

    std::string getName() const override;

    // Клонирование
    std::unique_ptr<Ability> clone() const override;
};

#endif
