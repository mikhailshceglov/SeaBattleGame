#include <stdexcept>
#include <iostream>

#include "ship.h"
#include "exceptions.h"

// Конструктор с размером, координатами и ориентацией
Ship::Ship(int size, int startX, int startY, ShipOrientation orientation) : size_(size), startX_(startX), startY_(startY), orientation_(orientation) {

    if (size < kMinSize || size > kMaxSize) {
        throw InvalidShipSizeException();
    }

    segments_.resize(size_);
    // std::cout << "Проверка инициализации сегментов:\n";
    // for (size_t i = 0; i < segments_.size(); ++i) {
    //     std::cout << "Сегмент " << i << " статус: " << static_cast<int>(segments_[i].getStatus()) << '\n';
    // }
}
 
// Получение размера корабля
int Ship::getSize() const noexcept {
    return size_;
}

// Проверка статуса корабля (жив или уничтожен)
ShipStatus Ship::getShipStatus() const noexcept {
    for (const auto& segment : segments_) {
        if (segment.getStatus() != ShipSegmentStatus::Destroyed) {
            return ShipStatus::alive;
        }
    }
    return ShipStatus::dead;
}

// Нанесение урона сегменту по индексу
void Ship::damageSegment(int index) {
    //std::cout << "Изменение статуса сегмента. Индекс сегмента: " << index << ", текущий статус: " << static_cast<int>(segments_[index].getStatus()) << std::endl;
    if (index < 0 || index >= size_) {
        throw InvalidSegmentIndexException();
    }

    // std::cout << "Изменение статуса сегмента:" << std::endl;
    // std::cout << "  Адрес сегмента: " << &segments_[index] << std::endl;
    // std::cout << "  Статус до атаки: " << static_cast<int>(segments_[index].getStatus()) << std::endl;

    segments_[index].takeDamage();

    // std::cout << "  Статус после атаки: " << static_cast<int>(segments_[index].getStatus()) << std::endl;
}


// Нанесение урона сегменту по координатам
void Ship::damageAt(int x, int y) {
    int index;
    if (orientation_ == ShipOrientation::Horizontal) {
        index = x - startX_;
    } else {
        index = y - startY_;    
    }

    // Проверка, что индекс внутри диапазона сегментов корабля
    if (index >= 0 && index < size_) {
        damageSegment(index);
    } else {
        throw InvalidSegmentIndexException();
    }
}

// Конструктор сегмента (сегмент целый изначально)
Ship::ShipSegment::ShipSegment() : status_(ShipSegmentStatus::Whole) {
    // std::cout << "Создание ShipSegment по адресу: " << this << ", Статус: " << static_cast<int>(status_) << '\n';
}

// Получение статуса сегмента (целый=0, поврежденный=1, уничтоженный=2)
ShipSegmentStatus Ship::ShipSegment::getStatus() const{

    // std::cout << static_cast<int>(status_) << std::endl;

    return status_;
}

// Нанесение урона сегменту
void Ship::ShipSegment::takeDamage() {
    if (status_ == ShipSegmentStatus::Whole) {
        status_ = ShipSegmentStatus::Damaged;
    } else if (status_ == ShipSegmentStatus::Damaged) {
        status_ = ShipSegmentStatus::Destroyed;
    }
}

ShipSegmentStatus Ship::getSegmentStatus(int x, int y) const {
    int index;
    if (orientation_ == ShipOrientation::Horizontal) {
        index = x - startX_;
    } else {
        index = y - startY_;
    }

    if (index >= 0 && index < size_) {
        return segments_[index].getStatus();;

    } else {
        throw InvalidSegmentIndexException();
    }
}

json Ship::toJson() const {
    json j;
    j["size"] = size_;
    j["startX"] = startX_;
    j["startY"] = startY_;
    j["orientation"] = static_cast<int>(orientation_);
    j["segments"] = std::vector<int>();
    for (const auto& segment : segments_) {
        j["segments"].push_back(static_cast<int>(segment.getStatus()));
    }
    return j;
}

void Ship::fromJson(const json& j) {
    size_ = j.at("size").get<int>();
    startX_ = j.at("startX").get<int>();
    startY_ = j.at("startY").get<int>();
    orientation_ = static_cast<ShipOrientation>(j.at("orientation").get<int>());
    segments_.resize(size_);
    if (j.contains("segments")) {
        auto segmentStatuses = j.at("segments").get<std::vector<int>>();
        for (size_t i = 0; i < segmentStatuses.size(); ++i) {
            if (segmentStatuses[i] == static_cast<int>(ShipSegmentStatus::Damaged)) {
                segments_[i].takeDamage();
            } else if (segmentStatuses[i] == static_cast<int>(ShipSegmentStatus::Destroyed)) {
                segments_[i].takeDamage();
                segments_[i].takeDamage();
            }
        }
    }
}

std::unique_ptr<Ship> Ship::clone() const {
    return std::make_unique<Ship>(size_, startX_, startY_, orientation_);
}
