#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <memory>
#include "field.h"
#include "shipManager.h"
#include "abilityManager.h"
#include "GameState.h"
#include "gui_logger.h"

class GameLoop {
public:
    //GameLoop();
    GameLoop(GuiLogger& logger);

    GuiLogger& logger; // Поле для логгера

    void startGame();

    void saveGame();
    void loadGame();

    int currentRound; 
    bool isPlayerTurn;

    std::unique_ptr<GameField> playerField;     // Поле игрока
    std::unique_ptr<GameField> enemyField;      // Поле компьютера
    std::unique_ptr<ShipManager> playerShips;   // Менеджер кораблей игрока
    std::unique_ptr<ShipManager> enemyShips;    // Менеджер кораблей компьютера
    std::unique_ptr<AbilityManager> abilities;  // Менеджер способностей игрока


    void initializeGame();      // Инициализация игры
    void resetComputer();       // Сброс состояния компьютера для нового раунда
    void playRound();           // Проведение текущего раунда

    //  обновленный
    void playPlayerTurn(bool useAbility, int abilityX, int abilityY, int attackX, int attackY);

    void playEnemyTurn();       // Ход компьютера
    AbilityManager& getAbilityManager() const { return *abilities; }

    void checkAbilityQueue(GuiLogger& logger);

    bool isAbilityQueueEmptyLogged = false; // Флаг для контроля логирования пустой очереди
};

#endif
