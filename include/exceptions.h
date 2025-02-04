#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class GameException : public std::exception {
public:
    explicit GameException(const std::string& message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

// СоБаКа
class sobaka : public GameException {
public:
    sobaka() : GameException("СОБАКА (dog)") {}
};
 
// Исключение: попытка разместить корабль вплотную к другому кораблю
class ShipOverlapException : public GameException {
public:
    ShipOverlapException() : GameException("Ошибка: попытка разместить корабль вплотную или на пересечении с другим кораблем!") {}
};

// Исключение: попытка атаки за границы поля
class OutOfBoundsAttackException : public GameException {
public:
    OutOfBoundsAttackException() : GameException("Ошибка: попытка атаки за пределы поля!") {}
};

// Исключение для некорректного размера корабля
class InvalidShipSizeException : public GameException {
public:
    InvalidShipSizeException() : GameException("Размер корабля должен быть от 1 до 4") {}
};

// Исключение для недопустимого индекса сегмента корабля
class InvalidSegmentIndexException : public GameException {
public:
    InvalidSegmentIndexException() : GameException("Индекс сегмента корабля за границей") {}
};

// Исключение для недопустимого индекса корабля
class InvalidShipIndexException : public GameException {
public:
    InvalidShipIndexException() : GameException("Индекс корабля за границей!") {}
};

// Исключение для некорректных размеров игрового поля
class InvalidFieldSizeException : public GameException {
public:
    InvalidFieldSizeException() : GameException("Неверные размеры поля, прямоугольные или отрицательные") {}
};

// Исключение для координат, выходящих за границы игрового поля
class CoordinatesOutOfBoundsException : public GameException {
public:
    CoordinatesOutOfBoundsException() : GameException("Coordinates are out of bounds!") {}
};

#endif
