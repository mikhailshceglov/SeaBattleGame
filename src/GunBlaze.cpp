#include "GunBlaze.h"

void GunBlaze::useAbility(GameField& field, ShipManager& manager, GuiLogger& logger) {
    logger.addLog("Использована способность: Обстрел!");
    
    // Собираем список всех доступных для атаки сегментов кораблей
    std::vector<std::pair<int, int>> targetSegments;
    for (int y = 0; y < field.getHeight(); y++) {
        for (int x = 0; x < field.getWidth(); x++) {
            if (field.getCellStatus(x, y) == CellStatus::Ship) {
                targetSegments.emplace_back(x, y);
            }
        }
    }

    if (!targetSegments.empty()) {
        // Генерируем случайный индекс сегмента
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, targetSegments.size() - 1);
        
        // Получаем случайный сегмент из targetSegments
        auto target = targetSegments[dis(gen)];
        int randomX = target.first;
        int randomY = target.second;

        // Выполняем атаку
        field.attack(randomX, randomY, manager);
        logger.addLog("Урон нанесен по сегменту корабля на координатах (" + std::to_string(randomX) + ", " + std::to_string(randomY) + ").");
    } else {
        logger.addLog("На поле нет кораблей для атаки.");
    }
}

std::string GunBlaze::getName() const {
    return "Gun Blaze";
}

std::unique_ptr<Ability> GunBlaze::clone() const {
    return std::make_unique<GunBlaze>(*this);
}
