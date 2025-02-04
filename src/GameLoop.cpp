#include "GameLoop.h"
#include "exceptions.h"
#include "GameState.h"
#include "gui_logger.h"

#include <iostream>
#include <random>
#include <sstream>

GameLoop::GameLoop(GuiLogger& logger) : currentRound(1), isPlayerTurn(true), logger(logger) {}

void GameLoop::initializeGame() {
    playerField = std::make_unique<GameField>(10, 10);
    enemyField = std::make_unique<GameField>(10, 10);

    // Инициализация кораблей игрока
    std::vector<std::tuple<int, int, int, ShipOrientation>> playerShipsDetails;
    std::vector<int> shipSizes = {1, 1};

    for (size_t i = 0; i < shipSizes.size(); ++i) {
        int size = shipSizes[i];
        int x, y;
        char orientationChar;
        ShipOrientation orientation;
        bool mainloop = true;

        while (mainloop) {
            try {
                std::cout << "Введите начальные координаты для корабля длины " << size << " (формат: 'x y'): ";
                std::cin >> x >> y;

                if (std::cin.fail() || !playerField->isWithinBounds(x, y)) {
                    throw std::invalid_argument("Некорректные координаты.");
                }

                std::cout << "Введите ориентацию корабля (h - горизонтальная, v - вертикальная): ";
                std::cin >> orientationChar;

                if (orientationChar == 'h') {
                    orientation = ShipOrientation::Horizontal;
                } else if (orientationChar == 'v') {
                    orientation = ShipOrientation::Vertical;
                } else {
                    throw std::invalid_argument("Некорректный ввод ориентации.");
                }

                auto tempShip = std::make_unique<Ship>(size, x, y, orientation);
                if (!playerField->placeShip(*tempShip, x, y, orientation)) {
                    throw std::runtime_error("Невозможно разместить корабль в указанных координатах.");
                }

                playerShipsDetails.emplace_back(size, x, y, orientation);
                break; 

            } catch (const std::exception& e) {
                std::cerr << "Ошибка: " << e.what() << " Попробуйте снова." << std::endl;
            }
        }
    }

    playerShips = std::make_unique<ShipManager>(playerShipsDetails, *playerField);

    std::vector<std::tuple<int, int, int, ShipOrientation>> enemyShipsDetails = {
        {4, 0, 0, ShipOrientation::Horizontal},
        {3, 0, 9, ShipOrientation::Horizontal},
        {3, 9, 0, ShipOrientation::Vertical},
        {2, 5, 9, ShipOrientation::Horizontal},
        {2, 8, 9, ShipOrientation::Horizontal},
        {2, 5, 5, ShipOrientation::Vertical},
        {1, 5, 0, ShipOrientation::Horizontal},
        {1, 2, 5, ShipOrientation::Vertical},
        {1, 2, 2, ShipOrientation::Horizontal},
        {1, 9, 5, ShipOrientation::Vertical},
    };

    enemyShips = std::make_unique<ShipManager>(enemyShipsDetails, *enemyField);
    abilities = std::make_unique<AbilityManager>();

    abilities->addRandomAbility(1);
}

void GameLoop::resetComputer() {
    enemyField.reset();
    enemyShips.reset();
    abilities.reset();

    enemyField = std::make_unique<GameField>(10, 10);

    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    std::vector<std::tuple<int, int, int, ShipOrientation>> enemyShipsDetails;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> coordDist(0, 9);
    std::uniform_int_distribution<> orientationDist(0, 1); 

    for (int size : shipSizes) {
        bool placed = false;

        while (!placed) {
            int x = coordDist(gen);
            int y = coordDist(gen);
            ShipOrientation orientation = static_cast<ShipOrientation>(orientationDist(gen));

            try {
                auto tempShip = std::make_unique<Ship>(size, x, y, orientation);
                if (enemyField->placeShip(*tempShip, x, y, orientation)) {
                    enemyShipsDetails.emplace_back(size, x, y, orientation);
                    placed = true;
                }
            } catch (const std::exception&) {
                continue;
            }
        }
    }

    enemyShips = std::make_unique<ShipManager>(enemyShipsDetails, *enemyField);
    abilities = std::make_unique<AbilityManager>();

    std::cout << "Состояние компьютера обновлено!" << std::endl;
}

void GameLoop::playPlayerTurn(bool useAbility, int abilityX, int abilityY, int attackX, int attackY) {
    std::cout << "Ваш ход!" << std::endl;

    if (useAbility && abilities->getAbilityCount() > 0) {
        try {
            if (!enemyField->isWithinBounds(abilityX, abilityY)) {
                throw CoordinatesOutOfBoundsException();
            }

            abilities->useAbility(*enemyField, *enemyShips, logger, abilityX, abilityY);
            std::cout << "Способность использована!" << std::endl;
        } catch (const CoordinatesOutOfBoundsException&) {
            std::cerr << "Ошибка: координаты находятся вне игрового поля для способности." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка применения способности: " << e.what() << std::endl;
        }
    }

    try {
        if (!enemyField->isWithinBounds(attackX, attackY)) {
            throw CoordinatesOutOfBoundsException();
        }

        if (enemyField->attack(attackX, attackY, *enemyShips)) {
            std::cout << "Попадание! Осталось вражеских кораблей: " << enemyShips->getAliveShipCount() << std::endl;
        } else {
            std::cout << "Промах!" << std::endl;
        }
    } catch (const CoordinatesOutOfBoundsException&) {
        std::cerr << "Ошибка: координаты находятся вне игрового поля для атаки." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void GameLoop::playEnemyTurn() {
    std::cout << "Ход врага!" << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, playerField->getWidth() - 1);
    std::uniform_int_distribution<> disY(0, playerField->getHeight() - 1);

    int x, y;
    int attempts = 0;

    do {
        x = disX(gen);
        y = disY(gen);
        attempts++;
    } while (playerField->getCellStatus(x, y) != CellStatus::Unknown && attempts < 100);

    if (playerField->attack(x, y, *playerShips)) {
        std::cout << "Враг попал в ваш корабль на координатах (" << x << ", " << y << ")!" << std::endl;
    } else {
        std::cout << "Враг промахнулся на координатах (" << x << ", " << y << ")!" << std::endl;
    }
}

void GameLoop::saveGame() {
    GameState state(
        currentRound,
        std::make_unique<GameField>(*playerField),
        std::make_unique<GameField>(*enemyField),
        std::make_unique<ShipManager>(*playerShips),
        std::make_unique<ShipManager>(*enemyShips),
        std::make_unique<AbilityManager>(*abilities)
    );
    state.saveToFile("./savegame.dat");
    std::cout << "Игра сохранена!" << std::endl;
}

void GameLoop::loadGame() {
    GameState state;
    state.loadFromFile("savegame.dat");

    currentRound = state.getRound();
    playerField = std::move(state.playerField);
    enemyField = std::move(state.enemyField);
    playerShips = std::move(state.playerShips);
    enemyShips = std::move(state.enemyShips);
    abilities = std::move(state.abilities);

    if (!playerField || !enemyField) {
        std::cerr << "Ошибка: поля не загружены корректно!" << std::endl;
        return;
    }
    if (!playerShips || !enemyShips) {
        std::cerr << "Ошибка: менеджеры кораблей не загружены корректно!" << std::endl;
        return;
    }

    try {
        playerField->updateShipPointers(*playerShips);
        enemyField->updateShipPointers(*enemyShips);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при обновлении указателей кораблей: " << e.what() << std::endl;
    }
}

void GameLoop::checkAbilityQueue(GuiLogger& logger) {
    if (abilities->getAbilityCount() == 0 && !isAbilityQueueEmptyLogged) {
        logger.addLog("Очередь способностей пуста.");
        isAbilityQueueEmptyLogged = true;
    } else if (abilities->getAbilityCount() > 0) {
        isAbilityQueueEmptyLogged = false;
    }
}
