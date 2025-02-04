#include "abilityManager.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "GunBlaze.h"
#include "GameState.h"

#include <iostream>
#include <random>
#include <algorithm>

// Конструктор: создаем случайную очередь способностей
AbilityManager::AbilityManager() {
    std::random_device rd;
    std::mt19937 gen(rd());

    abilities.push_back(std::make_unique<DoubleDamage>());
    abilities.push_back(std::make_unique<Scanner>());
    abilities.push_back(std::make_unique<GunBlaze>());

    std::shuffle(abilities.begin(), abilities.end(), gen);

    abilityCount = abilities.size();
}

// Получение очереди способностей
const std::deque<std::unique_ptr<Ability>>& AbilityManager::getAbilities() const {
    return abilities;
}

// Получение количества способностей
int AbilityManager::getAbilityCount() const {
    return abilityCount;
}


void AbilityManager::useAbility(GameField& field, ShipManager& manager, GuiLogger& logger, int x, int y) {
    if (!abilities.empty()) {
        SetCoordinates* coordAbility = dynamic_cast<SetCoordinates*>(abilities.front().get());
        if (coordAbility) {
            coordAbility->setCoordinates(x, y);
        }
        abilities.front()->useAbility(field, manager, logger); // Передаём logger
        abilities.pop_front();
        abilityCount = abilities.size();
    } else {
        logger.addLog("Нет доступных способностей для использования!");
    }
}

// Добавление случайной способности в очередь, если корабль уничтожен
void AbilityManager::addRandomAbility(int shipDestroyed) {
    if (shipDestroyed == 1 || shipDestroyed == 0) { // Условие включает ручное добавление
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 2);

        int randomNum = dis(gen);
        switch (randomNum) {
            case 0:
                abilities.push_back(std::make_unique<DoubleDamage>());
                break;
            case 1:
                abilities.push_back(std::make_unique<Scanner>());
                break;
            case 2:
                abilities.push_back(std::make_unique<GunBlaze>());
                break;
        }
        std::cout << "Добавлена новая случайная способность!" << std::endl;
        abilityCount = abilities.size();
    }
}


json AbilityManager::toJson() const {
    json j;
    j["abilities"] = json::array(); // Создаем пустой массив JSON
    for (const auto& ability : abilities) {
        if (ability) {
            j["abilities"].push_back(ability->getName()); // Сохраняем только имя способности
        }
    }
    return j;
}


void AbilityManager::fromJson(const json& j) {
    if (j.contains("abilities") && j["abilities"].is_array()) {
        abilities.clear();
        for (const auto& abilityName : j["abilities"]) {
            if (abilityName == "DoubleDamage") {
                abilities.push_back(std::make_unique<DoubleDamage>());
            } else if (abilityName == "Scanner") {
                abilities.push_back(std::make_unique<Scanner>());
            } else if (abilityName == "GunBlaze") {
                abilities.push_back(std::make_unique<GunBlaze>());
            }
        }
        abilityCount = abilities.size();
    }
}

AbilityManager::AbilityManager(const AbilityManager& other) {
    for (const auto& ability : other.abilities) {
        abilities.emplace_back(ability->clone());
    }
}
