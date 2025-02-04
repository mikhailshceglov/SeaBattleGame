#include <iostream>
#include <tuple>
#include "ShipManager.h"
#include "ship.h"
#include "field.h"
#include "exceptions.h"
#include "GameState.h"

// Основной конструктор
ShipManager::ShipManager(const std::vector<std::tuple<int, int, int, ShipOrientation>>& shipDetails, GameField& field) {
    for (const auto& details : shipDetails) {
        int size = std::get<0>(details);
        int startX = std::get<1>(details);
        int startY = std::get<2>(details);
        ShipOrientation orientation = std::get<3>(details);

        auto ship = std::make_unique<Ship>(size, startX, startY, orientation);

        if (!field.placeShip(*ship, startX, startY, orientation)) {
            throw ShipOverlapException();
        }
        ships_.emplace_back(std::move(ship));
    }
}

// Конструктор копирования
ShipManager::ShipManager(const ShipManager& other) {
    for (const auto& ship : other.ships_) {
        ships_.emplace_back(ship->clone()); // Используем метод clone
    }
}

// Получение корабля по индексу
const Ship& ShipManager::getShip(int index) const {
    if (index < 0 || index >= static_cast<int>(ships_.size())) {
        throw InvalidShipIndexException();
    }
    return *ships_[index];
}

// Подсчет количества кораблей
int ShipManager::getShipCount() const noexcept {
    return static_cast<int>(ships_.size());
}

// Получение указателя на корабль по координатам
Ship* ShipManager::getShipAt(int x, int y) {
    for (const auto& shipPtr : ships_) {
        Ship& ship = *shipPtr;

        int startX = ship.getStartX();
        int startY = ship.getStartY();
        int size = ship.getSize();
        ShipOrientation orientation = ship.getOrientation();

        if (orientation == ShipOrientation::Horizontal) {
            if (y == startY && x >= startX && x < startX + size) {
                return shipPtr.get();
            }
        } else {
            if (x == startX && y >= startY && y < startY + size) {
                return shipPtr.get();
            }
        }
    }
    return nullptr;
}

// Подсчет количества живых кораблей
int ShipManager::getAliveShipCount() const {
    int aliveCount = 0;
    for (const auto& shipPtr : ships_) {
        if (shipPtr->getShipStatus() == ShipStatus::alive) {
            aliveCount++;
        }
    }
    return aliveCount;
}

// Сериализация в JSON
json ShipManager::toJson() const {
    json j;
    j["ships"] = json::array();

    for (const auto& ship : ships_) {
        j["ships"].push_back(ship->toJson()); // Преобразуем каждый корабль в JSON
    }

    return j;
}

// Десериализация из JSON
void ShipManager::fromJson(const json& j) {
    ships_.clear();

    for (const auto& shipJson : j.at("ships")) {
        auto ship = std::make_unique<Ship>();
        ship->fromJson(shipJson); // Восстанавливаем объект Ship из JSON
        ships_.emplace_back(std::move(ship));
    }
}
