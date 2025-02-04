#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum class ShipOrientation : int {
    Horizontal = 0,
    Vertical = 1
};

enum class ShipStatus : int {
    dead = 0,
    alive = 1
};

enum class ShipSegmentStatus : int {
    Whole = 0,
    Damaged = 1,
    Destroyed = 2
};

class Ship {
public:
    // Конструктор, задающий размер корабля, начальные координаты и ориентацию
    explicit Ship(int size, int startX, int startY, ShipOrientation orientation);
    Ship() = default;

    // Запрет копирования и присваивания
    Ship(const Ship&) = delete;
    Ship& operator=(const Ship&) = delete;

    // Получение начальных координат корабля
    int getStartX() const { return startX_; }
    int getStartY() const { return startY_; }

    // Получение ориентации корабля
    ShipOrientation getOrientation() const { return orientation_; }

    // Получение размера корабля
    int getSize() const noexcept;

    ~Ship() = default;

    // Получение статуса сегмента по координатам
    ShipSegmentStatus getSegmentStatus(int x, int y) const;
    
    // Проверка, живой корабль или уничтожен (все сегменты уничтожены)
    ShipStatus getShipStatus() const noexcept;

    // Нанесение урона сегменту корабля по индексу
    void damageSegment(int index);

    // Нанесение урона сегменту корабля по координатам
    void damageAt(int x, int y);

    // Минимальный и максимальный размер корабля
    static const int kMinSize = 1;
    static const int kMaxSize = 4;

    json toJson() const;
    void fromJson(const json& j);

    std::unique_ptr<Ship> clone() const;

private:
    int size_;         // Размер корабля (1-4)
    int startX_;       // Начальная координата X
    int startY_;       // Начальная координата Y
    ShipOrientation orientation_; // Ориентация корабля

    class ShipSegment {
    public:
        ShipSegment();
        ~ShipSegment() = default;

        // Нанести урон сегменту
        void takeDamage();
        
        ShipSegmentStatus getStatus() const;

    private:
        ShipSegmentStatus status_ = ShipSegmentStatus::Whole;  // Изначально целый
    };

    std::vector<ShipSegment> segments_;  // Сегменты корабля
};

#endif 
