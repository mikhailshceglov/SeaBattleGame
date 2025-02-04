#include <iostream>

#include "field.h"
#include "shipManager.h"
#include "ship.h"
#include "exceptions.h"
#include "GameState.h"

// Конструктор
GameField::GameField(int width, int height) 
    : width_(width), height_(height),
    field_(height, std::vector<CellStatus>(width, CellStatus::Unknown)),
    shipPointers_(height, std::vector<Ship*>(width, nullptr)) {

    if (width <= 0 || height <= 0 || (height != width)) {
        throw InvalidFieldSizeException();
    }
}

// Конструктор копирования
GameField::GameField(const GameField& other) {
    deepCopy(other);
}

// Конструктор перемещения
GameField::GameField(GameField&& other) noexcept 
    : width_(other.width_), height_(other.height_), 
    field_(std::move(other.field_)), 
    shipPointers_(std::move(other.shipPointers_)) {

    other.width_ = 0;
    other.height_ = 0;
}

// Оператор копирования
GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        deepCopy(other);
    }
    return *this;
}

// Оператор перемещения
GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        field_ = std::move(other.field_);
        shipPointers_ = std::move(other.shipPointers_);

        other.width_ = 0;
        other.height_ = 0;
    }
    return *this;
}

// Деструктор
GameField::~GameField() {}

// Глубокое копирование
void GameField::deepCopy(const GameField& other) {
    width_ = other.width_;
    height_ = other.height_;
    field_ = other.field_;
    shipPointers_ = other.shipPointers_;
}

// Размещение корабля на поле
bool GameField::placeShip(Ship& ship, int x, int y, ShipOrientation orientation) {
    if (canPlaceShip(ship, x, y, orientation)) {
        return false;
    }

    // Маркируем клетки, занятые кораблем
    markShipOnField(ship, x, y, orientation);
    return true;
}

// Проверка, можно ли разместить корабль
bool GameField::canPlaceShip(const Ship& ship, int x, int y, ShipOrientation orientation) const {
    int shipSize = ship.getSize();

    for (int i = 0; i < shipSize; ++i) {
        int currentX = x + (orientation == ShipOrientation::Horizontal ? i : 0);
        int currentY = y + (orientation == ShipOrientation::Vertical ? i : 0);

        if (!isWithinBounds(currentX, currentY) || field_[currentY][currentX] != CellStatus::Empty) {
            return false;
        }

        // Проверка соседних клеток
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int neighborX = currentX + dx;
                int neighborY = currentY + dy;
                if (isWithinBounds(neighborX, neighborY) && field_[neighborY][neighborX] == CellStatus::Ship) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Маркировка клеток, занятых кораблем
void GameField::markShipOnField(Ship& ship, int x, int y, ShipOrientation orientation) {
    int shipSize = ship.getSize();

    for (int i = 0; i < shipSize; i++) {
            int currentX, currentY;
            if (orientation == ShipOrientation::Horizontal) {
                currentX = x + i;
                currentY = y;
            } else if (orientation == ShipOrientation::Vertical) {
                currentX = x;
                currentY = y + i;
            }
        field_[currentY][currentX] = CellStatus::Ship;
        shipPointers_[currentY][currentX] = &ship;  // Привязываем корабль к клетке
    }
}

// Атака на клетку
bool GameField::attack(int x, int y, ShipManager& shipManager) {
    if (!isWithinBounds(x, y)) {
        throw OutOfBoundsAttackException();
    }

    if (field_[y][x] == CellStatus::Ship) {
        Ship* attackedShip = shipPointers_[y][x];

        if (attackedShip != nullptr) {

            attackedShip->damageAt(x, y);
            ShipSegmentStatus segmentStatus = attackedShip->getSegmentStatus(x, y);
            
            if (segmentStatus == ShipSegmentStatus::Destroyed) {
                
                field_[y][x] = CellStatus::deadship;
                shipPointers_[y][x] = nullptr;

                // Если корабль уничтожен, обновляем клетки вокруг него
                if (attackedShip->getShipStatus() == ShipStatus::dead) {
                    markSurroundingCellsAsEmpty(*attackedShip);
                }
            }
            return true;  // Попадание
        }
    }
    // если корабля нет, но надо поменять статус клетки
    field_[y][x] = CellStatus::Empty;
    return false;
}

// Получение статуса клетки
CellStatus GameField::getCellStatus(int x, int y) const {
    if (!isWithinBounds(x, y)) {
        throw CoordinatesOutOfBoundsException();
    }
    return field_[y][x];
}

// Проверка на выход за границы поля
bool GameField::isWithinBounds(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

void GameField::printField_segments() const {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (shipPointers_[y][x] != nullptr) {
                Ship* ship = shipPointers_[y][x];
                ShipSegmentStatus segmentStatus = ship->getSegmentStatus(y, x);
                // Выводим состояние здоровья сегмента
                if (segmentStatus == ShipSegmentStatus::Destroyed) {
                    std::cout << -1 << " ";  // Сегмент уничтожен
                } else if (segmentStatus == ShipSegmentStatus::Damaged) {
                    std::cout << 1 << " ";  // Сегмент повреждён (здоровье 1)
                } else if (segmentStatus == ShipSegmentStatus::Whole) {
                    std::cout << 2 << " ";  // Сегмент целый (здоровье 2)
                }
            } else {
                std::cout << 0 << " ";  // Клетка пуста
            }
        }
        std::cout << std::endl;
    }
}

void GameField::printField() const {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            // Выводим числовое значение статуса клетки (unknow=0, empty=1, ship=2)
            std::cout << static_cast<int>(field_[y][x]) << " ";
        }
        std::cout << std::endl;
    }
}

int GameField::getWidth() const {
    return width_;
}

int GameField::getHeight() const {
    return height_;
}

json GameField::toJson() const {
    json j;
    j["width"] = width_;
    j["height"] = height_;
    j["field"] = field_;
    return j;
}

void GameField::fromJson(const json& j) {
    try {
        width_ = j.at("width").get<int>();
        height_ = j.at("height").get<int>();

        // Сохраняем field_ как целостный объект
        field_ = j.at("field").get<std::vector<std::vector<CellStatus>>>(); 

        shipPointers_.resize(height_, std::vector<Ship*>(width_, nullptr));
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при загрузке игрового поля: " << e.what() << std::endl;
        throw;
    }
}

void GameField::updateShipPointers(const ShipManager& manager) {
    // Очищаем существующие указатели
    for (auto& row : shipPointers_) {
        std::fill(row.begin(), row.end(), nullptr);
    }

    // Обновляем указатели на основе расположения кораблей
    for (int i = 0; i < manager.getShipCount(); ++i) {
        const Ship& ship = manager.getShip(i);
        int x = ship.getStartX();
        int y = ship.getStartY();
        int size = ship.getSize();
        ShipOrientation orientation = ship.getOrientation();

        for (int j = 0; j < size; ++j) {
            if (orientation == ShipOrientation::Horizontal) {
                shipPointers_[y][x + j] = const_cast<Ship*>(&ship);
            } else {
                shipPointers_[y + j][x] = const_cast<Ship*>(&ship);
            }
        }
    }
}

ShipSegmentStatus GameField::getSegmentStatus(int x, int y) const {
    Ship* ship = shipPointers_[y][x]; // Указатель на корабль в данной клетке
    if (ship) {
        return ship->getSegmentStatus(x, y); // Метод внутри Ship для получения статуса сегмента
    }
    throw std::runtime_error("Нет корабля в данной клетке");
}

void GameField::markSurroundingCellsAsEmpty(const Ship& ship) {
    int startX = ship.getStartX();
    int startY = ship.getStartY();
    int size = ship.getSize();
    ShipOrientation orientation = ship.getOrientation();

    // Обрабатываем клетки вокруг корабля
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int i = 0; i < size; ++i) {
                int x = startX + (orientation == ShipOrientation::Horizontal ? i : 0) + dx;
                int y = startY + (orientation == ShipOrientation::Vertical ? i : 0) + dy;

                if (isWithinBounds(x, y)) {
                    if (field_[y][x] == CellStatus::Unknown || field_[y][x] == CellStatus::Empty) {
                        field_[y][x] = CellStatus::Empty;
                    }
                }
            }
        }
    }
}
