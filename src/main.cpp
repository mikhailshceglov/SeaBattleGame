// #include "ship.h"
// #include "shipManager.h"
// #include "field.h"
// #include "DoubleDamage.h"
// #include "Scanner.h"
// #include "GunBlaze.h"
// #include "abilityManager.h"
// #include "GameLoop.h"
// #include "GameState.h"
// #include "input_render.h"
// #include "game_controller.h"


// #include "game_render.h"
// #include "field_render.h"
// #include "message_render.h"

// #include <iostream>
// #include <tuple>
// #include <vector>
// #include <memory>

// #include "game_controller.hpp"
// #include "game_render.hpp"

// int main() {

//     try {
//         GameLoop game;
//         TerminalInputHandler input_handler; 
//         FieldRenderer field_renderer;
//         MessageRenderer message_renderer;

//         // Создаем контроллер и рендер
//         GameRenderer<FieldRenderer, MessageRenderer> game_renderer(game, field_renderer, message_renderer);
//         GameController<TerminalInputHandler, GameRenderer<FieldRenderer, MessageRenderer>> game_controller(game, input_handler, game_renderer);

//         std::cout << "Добро пожаловать в игру!" << std::endl;

//         while (true) {
//             std::cout << "Выберите действие:\n1. Загрузить игру\n2. Начать новую игру" << std::endl;
//             std::cout << "Введите 1 или 2: ";
//             int choice;
//             std::cin >> choice;

//             if (std::cin.fail() || (choice != 1 && choice != 2)) {
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 std::cerr << "Неверный ввод. Введите 1 для загрузки игры или 2 для начала новой игры." << std::endl;
//                 continue;
//             }

//             if (choice == 1) {
//                 try {
//                     game.loadGame();
//                     std::cout << "Игра успешно загружена!" << std::endl;
//                 } catch (const std::exception& e) {
//                     std::cerr << "Не удалось загрузить игру: " << e.what() << std::endl;
//                     std::cerr << "Начнем новую игру." << std::endl;
//                 }
//                 break;
//             } else if (choice == 2) {
//                 std::cout << "Перед началом игры нужно расставить свои корабли." << std::endl;
//                 game.initializeGame();
//                 break;
//             }
//         }

//         message_renderer.displayHelp();

//         // Основной игровой цикл
//         while (true) {
//             std::string command = game_controller.handleInput();

//             if (command == "exit") {
//                 game_controller.executeCommand(command);
//                 break;
//             } else {
//                 game_controller.executeCommand(command);
//             }

//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Ошибка: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }


//GUI

#include "ship.h"
#include "shipManager.h"
#include "field.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "GunBlaze.h"
#include "abilityManager.h"
#include "GameLoop.h"
#include "GameState.h"
#include "input_render.h"
#include "game_controller.h"

#include "game_render.h"
#include "field_render.h"
#include "message_render.h"

#include "gui_logger.h"

#include <iostream>
#include <tuple>
#include <vector>
#include <memory>

#include "game_controller.hpp"
#include "game_render.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

int main() {
    GuiLogger logger;

    try {
        // Инициализация GLFW
        if (!glfwInit())
            throw std::runtime_error("Не удалось инициализировать GLFW!");

        // Создание окна
        GLFWwindow* window = glfwCreateWindow(1280, 720, "Морской Бой", nullptr, nullptr);
        if (!window)
            throw std::runtime_error("Не удалось создать окно GLFW!");

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        // Инициализация Dear ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //ImFont* largeFont = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 10.0f); 

        if (!io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic())) {
            throw std::runtime_error("Не удалось загрузить шрифт!");
        }

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        // Настройки стиля
        ImGuiStyle& style = ImGui::GetStyle();
        style.ItemSpacing = ImVec2(0.0f, 0.0f); 
        style.FramePadding = ImVec2(0.0f, 0.0f);

        GameLoop game(logger); // Передаём logger в конструктор GameLoop

        GUIInputHandler input_handler;
        FieldRenderer field_renderer;
        MessageRenderer message_renderer;

        GameRenderer<FieldRenderer, MessageRenderer> game_renderer(game, field_renderer, message_renderer);
        GameController<GUIInputHandler, GameRenderer<FieldRenderer, MessageRenderer>> game_controller(game, input_handler, game_renderer);

        bool show_main_menu = true;
        bool show_attack_window = false;
        static char command_buffer[128] = "";
        static int attack_x = 0, attack_y = 0;
        static int ability_x = 0, ability_y = 0;
        static bool use_ability = false;
        static std::string selected_ability;

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Меню игры
            if (show_main_menu) {
                ImGui::Begin("Меню игры", &show_main_menu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

                ImGui::Text("Добро пожаловать в игру Морской Бой!");


                if (ImGui::Button("Загрузить игру")) {
                    try {
                        game.loadGame();
                        logger.addLog("Игра успешно загружена!");


                        // Вручную добавляем способности
                        auto& abilityManager = game.getAbilityManager();
                        abilityManager.addRandomAbility(1); // Добавляем случайную способность
                        abilityManager.addRandomAbility(1); // Ещё одну
                        abilityManager.addRandomAbility(1); // И ещё одну

                        // Логируем способности
                        const auto& abilities = abilityManager.getAbilities();
                        if (abilities.empty()) {
                            logger.addLog("Ошибка: способности не добавлены.");
                        } else {
                            logger.addLog("Текущие способности:");
                            for (const auto& ability : abilities) {
                                logger.addLog("- " + ability->getName());
                            }
                        }



                        show_main_menu = false;
                    } catch (const std::exception& e) {
                        logger.addLog(std::string("Ошибка загрузки: ") + e.what());
                    }
                }


                if (ImGui::Button("Начать новую игру")) {
                    game.initializeGame();

                    // Вручную добавляем способности
                    auto& abilityManager = game.getAbilityManager();
                    abilityManager.addRandomAbility(1); // Добавляем случайную способность
                    abilityManager.addRandomAbility(1); // Ещё одну
                    abilityManager.addRandomAbility(1); // И ещё одну

                    // Логируем количество способностей после добавления
                    const auto& abilities = abilityManager.getAbilities();
                    if (abilities.empty()) {
                        logger.addLog("Ошибка: способности не добавлены.");
                    } else {
                        logger.addLog("Способности успешно добавлены. Текущие способности:");
                        for (const auto& ability : abilities) {
                            logger.addLog("- " + ability->getName());
                        }
                    }

                    logger.addLog("Началась новая игра!");
                    show_main_menu = false;
                }

                if (ImGui::Button("Выход")) {
                    break;
                }

                ImGui::End();
            }

            // Логика игры
            if (!show_main_menu) {
                ImGui::Begin("Игра");
                ImGui::Text("Текущий ход: %s", game.isPlayerTurn ? "Игрок" : "Компьютер");

                ImGui::InputText("Введите команду", command_buffer, IM_ARRAYSIZE(command_buffer));
                if (ImGui::Button("Выполнить команду")) {
                    std::string command = command_buffer;
                    if (command == "attack" || command == "a") {
                        show_attack_window = true;
                        logger.addLog("Открывается окно для атаки и использования способности.");
                    } else {
                        try {
                            game_controller.executeCommand(command);
                            logger.addLog("Команда выполнена: " + command);
                        } catch (const std::exception& e) {
                            logger.addLog(std::string("Ошибка выполнения команды: ") + e.what());
                        }
                    }
                }
                ImGui::End();

                ImGui::Begin("Поле игрока");
                field_renderer.drawField(*game.playerField, *game.enemyField);
                ImGui::End();

                // Переменная для отображения окна способности
                static bool show_ability_window = false;

                if (show_attack_window) {
                    ImGui::Begin("Введите координаты атаки");

                    // Координаты для атаки
                    static int attackX = 0, attackY = 0;

                    // Координаты для способности
                    static int abilityX = 0, abilityY = 0;

                    // Флаг для использования способности
                    static bool use_ability = false; // Здесь используется правильное имя переменной
                    static std::string selected_ability;

                    // Ввод координат для атаки
                    ImGui::InputInt("Координата X (атака)", &attackX);
                    ImGui::InputInt("Координата Y (атака)", &attackY);

                    // Кнопка "Использовать способность"
                    if (ImGui::Button("Использовать способность")) {
                        if (game.getAbilityManager().getAbilityCount() > 0) {
                            show_ability_window = true; // Показываем окно выбора способности
                            use_ability = true;
                            logger.addLog("Открывается окно для выбора способности.");
                        } else {
                            logger.addLog("У вас нет доступных способностей.");
                        }
                    }

                    // Завершение хода
                    if (ImGui::Button("Подтвердить ход")) {
                        if (use_ability/* && !selected_ability.empty()*/) {
                            // Применяем способность, если она выбрана
                            try {

                                // game.getAbilityManager().useAbility(*game.enemyField, *game.enemyShips, abilityX, abilityY);
                                // logger.addLog("Способность \"" + selected_ability + "\" успешно использована на координатах (" +
                                //             std::to_string(abilityX) + ", " + std::to_string(abilityY) + ").");
                                // selected_ability.clear(); // Сбрасываем выбранную способность
                                // use_ability = false;       // Сбрасываем флаг использования способности
                                auto& abilityManager = game.getAbilityManager();
                                abilityManager.addRandomAbility(1); 
                                const auto& abilities = abilityManager.getAbilities();
                                //abilityManager.useAbility(*game.enemyField, *game.enemyShips, logger, 0, 0);
                                game.getAbilityManager().useAbility(*game.enemyField, *game.enemyShips, logger, abilityX, abilityY);
                                use_ability = false;

                            } catch (const std::exception& e) {
                                logger.addLog(std::string("Ошибка применения способности: ") + e.what());
                            }
                        } else {
                            // Обычная атака, если способность не выбрана
                            try {
                                if (game.playerField->isWithinBounds(attackX, attackY)) {
                                    // game.getAbilityManager().useAbility(*game.enemyField, *game.enemyShips, abilityX, abilityY);
                                    bool hit = game.enemyField->attack(attackX, attackY, *game.enemyShips);
                                    if (hit) {
                                        logger.addLog("Попадание по координатам (" + std::to_string(attackX) + ", " + std::to_string(attackY) + ").");
                                    } else {
                                        logger.addLog("Промах по координатам (" + std::to_string(attackX) + ", " + std::to_string(attackY) + ").");
                                    }
                                } else {
                                    logger.addLog("Координаты вне поля.");
                                }
                            } catch (const std::exception& e) {
                                logger.addLog(std::string("Ошибка атаки: ") + e.what());
                            }
                        }

                        // Завершаем окно атаки и передаём ход врагу
                        show_attack_window = false;
                        logger.addLog("Ход врага!");
                        game.playEnemyTurn();
                    }

                    ImGui::End();
                }

                // Окно выбора способности
                if (show_ability_window) {
                    ImGui::Begin("Выбор способности", &show_ability_window, ImGuiWindowFlags_AlwaysAutoResize);

                    const auto& abilities = game.getAbilityManager().getAbilities();
                    for (const auto& ability : abilities) {
                        if (ImGui::Button(ability->getName().c_str())) {
                            selected_ability = ability->getName(); // Устанавливаем выбранную способность
                            use_ability = true; // Устанавливаем флаг использования способности
                            logger.addLog("Выбрана способность: " + selected_ability);
                            show_ability_window = false; // Закрываем окно выбора способности
                        }
                    }

                    ImGui::End();
                }





                logger.render();
            }

            // Рендеринг
            ImGui::Render();
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();

    } catch (const std::exception& e) {
        logger.addLog(e.what());
        return 1;
    }

    return 0;
}
