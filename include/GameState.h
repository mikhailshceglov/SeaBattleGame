#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#include "field.h"
#include "ShipManager.h"
#include "abilityManager.h"

using json = nlohmann::json;

class GameState {
public:
    int currentRound;
    std::unique_ptr<GameField> playerField;
    std::unique_ptr<GameField> enemyField;
    std::unique_ptr<ShipManager> playerShips;
    std::unique_ptr<ShipManager> enemyShips;
    std::unique_ptr<AbilityManager> abilities;

    GameState();
    GameState(GameState&&) = default;
    GameState& operator=(GameState&&) = default;

    GameState(int round, 
              std::unique_ptr<GameField> playerField, 
              std::unique_ptr<GameField> enemyField, 
              std::unique_ptr<ShipManager> playerShips, 
              std::unique_ptr<ShipManager> enemyShips, 
              std::unique_ptr<AbilityManager> abilities);

    // Получение данных
    int getRound() const;
    const GameField& getPlayerField() const;
    const GameField& getEnemyField() const;
    const ShipManager& getPlayerShips() const;
    const ShipManager& getEnemyShips() const;
    const AbilityManager& getAbilities() const;

    // Сохранение состояния игры
    void saveToFile(const std::string& filename) const;

    // Загрузка состояния игры
    void loadFromFile(const std::string& filename);

    // Переопределение операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
    friend std::istream& operator>>(std::istream& is, GameState& state);

    json toJson() const;            // Преобразование в JSON
    void fromJson(const json& j);   // Восстановление из JSON

    GameState load(const std::string& filename);
    void save(const GameState& state, const std::string& filename);
};

#endif
