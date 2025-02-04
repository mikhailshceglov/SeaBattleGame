#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "ship.h"

// Перекрестное обращение в .h файлах
class GameField;

class ShipManager {
public:
    // Конструктор, принимающий размеры кораблей, координаты и поле
    ShipManager(const std::vector<std::tuple<int, int, int, ShipOrientation>>& shipDetails, GameField& field); // Основной конструктор

    ShipManager() = default; // Конструктор по умолчанию

    // Конструктор копирования
    ShipManager(const ShipManager& other);

    // Методы получения информации о кораблях
    const Ship& getShip(int index) const;
    int getShipCount() const noexcept;
    int getAliveShipCount() const; // Подсчет живых кораблей
    Ship* getShipAt(int x, int y);

    // Сериализация
    json toJson() const;
    void fromJson(const json& j);

private:
    // Используем std::unique_ptr для хранения указателей на Ship
    std::vector<std::unique_ptr<Ship>> ships_;
};

#endif
