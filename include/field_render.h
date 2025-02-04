#ifndef FIELD_RENDER_H
#define FIELD_RENDER_H

#include "GameLoop.h"
#include <iostream>
#include "imgui.h"

class FieldRenderer {
public:
    void drawField(const GameField& playerField, const GameField& enemyField) const;
};

#endif
