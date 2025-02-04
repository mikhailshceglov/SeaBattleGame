#ifndef GAME_MESSAGE_ENUM_H
#define GAME_MESSAGE_ENUM_H

enum class GameMessageEnum {
    // Общие сообщения
    UNKNOWN,                 
    INVALID_INPUT,           

    // Ввод данных
    INPUT_WIDTH,             
    INPUT_HEIGHT,            
    INPUT_COORDINATE,        
    RE_ENTER_COORDINATE,     
    OPTION_LOAD_GAME,     

    // Координаты
    INVALID_COORDINATE,             
    COORDINATE_OUT_OF_RANGE,        // Координаты за пределами поля
    ATTACK_COORDINATE,              // Координаты для атаки
    SCANNER_COORDINATE,             // Координаты для сканера
    INVALID_COORDINATE_FOR_ATTACK,  // Некорректные координаты для атаки

    // Состояние игры
    LOST,                   
    WIN,                  
    PROMPT_START_NEW_GAME,  // Вопрос о начале новой игры
    START_NEW_GAME,         // Начало новой игры
    PROMPT_START_NEW_ROUND, // Вопрос о начале нового раунда
    START_NEW_ROUND         // Начало нового раунда
};

#endif
