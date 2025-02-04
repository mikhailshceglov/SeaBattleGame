#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include <deque>
#include <algorithm>
#include <memory>
#include <random>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "abilities.h"

class AbilityManager {
private:
    std::deque<std::unique_ptr<Ability>> abilities;  // Очередь способностей
    int abilityCount;

public:
    AbilityManager();

    // Получение очереди способностей
    const std::deque<std::unique_ptr<Ability>>& getAbilities() const;

    AbilityManager(const AbilityManager& other);

    // Получение количества способностей
    int getAbilityCount() const;

    // Применение первой способности из очереди
    void useAbility(GameField& field, ShipManager& manager, GuiLogger& logger, int x = 0, int y = 0);


    // Добавление случайной способности в очередь
    void addRandomAbility(int shipDestroyed);
    
    json toJson() const; // Преобразование в JSON
    void fromJson(const json& j); // Восстановление из JSON
};

#endif
