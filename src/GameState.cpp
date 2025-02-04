#include "GameState.h"

#include <iostream>
#include <fstream>

GameState::GameState() : currentRound(1) {}

GameState::GameState(int round, 
        std::unique_ptr<GameField> playerField, 
        std::unique_ptr<GameField> enemyField, 
        std::unique_ptr<ShipManager> playerShips, 
        std::unique_ptr<ShipManager> enemyShips, 
        std::unique_ptr<AbilityManager> abilities)
    : currentRound(round), 
    playerField(std::move(playerField)), 
    enemyField(std::move(enemyField)), 
    playerShips(std::move(playerShips)), 
    enemyShips(std::move(enemyShips)), 
    abilities(std::move(abilities)) {}

int GameState::getRound() const { return currentRound; }

const GameField& GameState::getPlayerField() const { return *playerField; }

const GameField& GameState::getEnemyField() const { return *enemyField; }

const ShipManager& GameState::getPlayerShips() const { return *playerShips; }

const ShipManager& GameState::getEnemyShips() const { return *enemyShips; }

const AbilityManager& GameState::getAbilities() const { return *abilities; }

void GameState::saveToFile(const std::string& filename) const {
    json j = toJson();
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    }

    outFile << j.dump(4); // 4 - пробела
    outFile.close();

}


// тут исключение
// void GameState::loadFromFile(const std::string& filename) {
//     std::ifstream inFile(filename);
//     if (!inFile.is_open()) {
//         throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
//     }
//     json j;
//     inFile >> j;
//     inFile.close();
//     fromJson(j);
// }

void GameState::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
    }

    json j;
    try {
        inFile >> j;
        inFile.close();
    } catch (const json::parse_error& e) {
        throw std::runtime_error("Ошибка парсинга JSON: " + std::string(e.what()));
    }

    // Проверка структуры данных
    if (!j.contains("playerField") || !j.contains("enemyField")) {
        throw std::runtime_error("Ошибка: файл не содержит необходимых данных!");
    }

    // Дополнительная проверка на соответствие ожидаемым типам данных
    if (!j["playerField"].is_object() || !j["enemyField"].is_object()) {
        throw std::runtime_error("Ошибка: данные в файле имеют некорректный формат.");
    }

    // Передача данных в объект
    fromJson(j);
}




GameState GameState::load(const std::string& filename) {
    GameState state;
    state.loadFromFile(filename);
    return state;
}

void GameState::save(const GameState& state, const std::string& filename) {
    state.saveToFile(filename);
}

// Преобразование в JSON
json GameState::toJson() const {
    json j;
    j["currentRound"] = currentRound;
    j["playerField"] = playerField->toJson();
    j["enemyField"] = enemyField->toJson();
    j["playerShips"] = playerShips->toJson();
    j["enemyShips"] = enemyShips->toJson();
    j["abilities"] = abilities->toJson();
    return j;
}

// Восстановление из JSON
void GameState::fromJson(const json& j) {
    try {
        currentRound = j.at("currentRound").get<int>();
        // std::cout << "Текущий раунд: " << currentRound << std::endl;

        playerField = std::make_unique<GameField>();
        playerField->fromJson(j.at("playerField"));

        enemyField = std::make_unique<GameField>();
        enemyField->fromJson(j.at("enemyField"));

        playerShips = std::make_unique<ShipManager>();
        playerShips->fromJson(j.at("playerShips"));

        enemyShips = std::make_unique<ShipManager>();
        enemyShips->fromJson(j.at("enemyShips"));

        abilities = std::make_unique<AbilityManager>();
        abilities->fromJson(j.at("abilities"));

    } catch (const std::exception& e) {
        std::cerr << "Ошибка при загрузке состояния игры: " << e.what() << std::endl;
        throw;
    }
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const GameState& state) {
    os << state.toJson().dump(4);
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, GameState& state) {
    json j;
    is >> j;
    state.fromJson(j);
    return is;
}
