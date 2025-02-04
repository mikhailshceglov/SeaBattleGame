#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <stdexcept>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


#include "ship.h"
#include "ShipManager.h"

enum class CellStatus {
    Unknown = 0,
    Empty = 1,
    Ship = 2,
    deadship = 3
};

class GameField {
public:
    GameField(int width, int height); // Конструктор с параметрами
    GameField() : width_(0), height_(0) {} // Конструктор по умолчанию

    // Конструкторы копирования и перемещения
    GameField(const GameField& other);
    GameField(GameField&& other) noexcept;

    // Операторы присваивания
    GameField& operator=(const GameField& other);
    GameField& operator=(GameField&& other) noexcept;

    ~GameField();

    // Метод для размещения корабля
    bool placeShip(Ship& ship, int x, int y, ShipOrientation orientation);

    // Метод для проверки возможности размещения корабля
    bool canPlaceShip(const Ship& ship, int x, int y, ShipOrientation orientation) const;

    // Метод для атаки на клетку
    bool attack(int x, int y, ShipManager& shipManager);

    // Получение статуса клетки
    CellStatus getCellStatus(int x, int y) const;

    // Методы для вывода поля на экран
    void printField_segments() const;
    void printField() const;

    bool isWithinBounds(int x, int y) const;
    void markShipOnField(Ship& ship, int x, int y, ShipOrientation orientation);

    int getWidth() const;
    int getHeight() const;

    json toJson() const;
    void fromJson(const json& j);

    void updateShipPointers(const ShipManager& shipManager);

    ShipSegmentStatus getSegmentStatus(int x, int y) const;

    void markSurroundingCellsAsEmpty(const Ship& ship);
private:
    int width_;
    int height_;
    std::vector<std::vector<CellStatus>> field_; // Массив статусов клеток
    std::vector<std::vector<Ship*>> shipPointers_; // Указатели на корабли каждой клетки

    void deepCopy(const GameField& other);  // Для глубокого копирования
};

#endif
