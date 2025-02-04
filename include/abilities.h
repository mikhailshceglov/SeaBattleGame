#ifndef ABILITIES_H
#define ABILITIES_H

#include <string>
#include "field.h"
#include "shipManager.h"
#include "gui_logger.h"

class Ability {
public:
    virtual ~Ability() = default;
    //virtual void useAbility(GameField& field, ShipManager& manager) = 0;
    virtual void useAbility(GameField& field, ShipManager& manager, GuiLogger& logger) = 0;

    virtual std::string getName() const = 0;

    // Метод клонирования
    virtual std::unique_ptr<Ability> clone() const = 0;
};

class SetCoordinates : public Ability {
public:
    virtual void setCoordinates(int x, int y) = 0;
};

#endif
