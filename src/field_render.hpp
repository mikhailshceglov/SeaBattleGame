// #include "field_render.h"
// #include "field.h"
// #include "ship.h"

// void FieldRenderer::drawField(const GameField& playerField, const GameField& enemyField) const {
//     // Отрисовка поля игрока
//     std::cout << "Поле игрока:" << std::endl;

//     for (int y = 0; y < playerField.getHeight(); y++) {
//         for (int x = 0; x < playerField.getWidth(); x++) {
//             CellStatus cell = playerField.getCellStatus(x, y);

//             switch (cell) {
//                 case CellStatus::Empty:
//                     std::cout << "x ";
//                     break;
//                 case CellStatus::Ship:
//                     try {
//                         ShipSegmentStatus segmentStatus = playerField.getSegmentStatus(x, y);
//                         switch (segmentStatus) {
//                             case ShipSegmentStatus::Whole:
//                                 std::cout << "2 ";
//                                 break;
//                             case ShipSegmentStatus::Damaged:
//                                 std::cout << "1 ";
//                                 break;
//                             case ShipSegmentStatus::Destroyed:
//                                 std::cout << "~ ";
//                                 break;
//                         }
//                     } catch (const std::runtime_error&) {
//                         std::cout << "~ ";
//                     }
//                     break;
//                 case CellStatus::Unknown:
//                     std::cout << "~ ";
//                     break;
//                 default:
//                     std::cout << "~ ";
//             }
//         }
//         std::cout << std::endl;
//     }

//     // Отрисовка поля врага
//     std::cout << "\nПоле врага:" << std::endl;

//     for (int y = 0; y < enemyField.getHeight(); y++) {
//         for (int x = 0; x < enemyField.getWidth(); x++) {
//             CellStatus cell = enemyField.getCellStatus(x, y);

//             switch (cell) {
//                 case CellStatus::Unknown:
//                     std::cout << "# "; // Неизвестная клетка
//                     break;
//                 case CellStatus::Empty:
//                     std::cout << "~ "; // Вода
//                     break;
//                 case CellStatus::Ship:
//                     try {
//                         ShipSegmentStatus segmentStatus = enemyField.getSegmentStatus(x, y);
//                         switch (segmentStatus) {
//                             case ShipSegmentStatus::Whole:
//                                 std::cout << "# ";
//                                 break;
//                             case ShipSegmentStatus::Damaged:
//                                 std::cout << "1 ";
//                                 break;
//                             case ShipSegmentStatus::Destroyed:
//                                 std::cout << "~ ";
//                                 break;
//                         }
//                     } catch (const std::runtime_error&) {
//                         std::cout << "~ ";
//                     }
//                     break;
//                 default:
//                     std::cout << "~ ";
//             }
//         }
//         std::cout << std::endl;
//     }
// }


// GUI

// #include "field_render.h"
// #include "field.h"
// #include "ship.h"
// #include "imgui.h"

// void FieldRenderer::drawField(const GameField& playerField, const GameField& enemyField) const {
//     // Рисуем поле игрока
//     ImGui::Begin("Поле игрока");
//     for (int y = 0; y < playerField.getHeight(); ++y) {
//         for (int x = 0; x < playerField.getWidth(); ++x) {
//             CellStatus cell = playerField.getCellStatus(x, y);
//             const char* cellSymbol = "~";

//             switch (cell) {
//                 case CellStatus::Empty:
//                     cellSymbol = "x"; // Пустая клетка
//                     break;
//                 case CellStatus::Ship:
//                     try {
//                         ShipSegmentStatus segmentStatus = playerField.getSegmentStatus(x, y);
//                         switch (segmentStatus) {
//                             case ShipSegmentStatus::Whole:
//                                 cellSymbol = "2"; // Целый сегмент
//                                 break;
//                             case ShipSegmentStatus::Damaged:
//                                 cellSymbol = "1"; // Повреждённый сегмент
//                                 break;
//                             case ShipSegmentStatus::Destroyed:
//                                 cellSymbol = "~"; // Уничтоженный сегмент
//                                 break;
//                         }
//                     } catch (const std::runtime_error&) {
//                         cellSymbol = "~"; // Ошибка получения статуса
//                     }
//                     break;
//                 case CellStatus::Unknown:
//                     cellSymbol = "~"; // Неизвестная клетка
//                     break;
//             }

//             ImGui::Text("%s", cellSymbol);
//             if (x < playerField.getWidth() - 1) ImGui::SameLine();
//         }
//     }
//     ImGui::End();

//     // Рисуем поле врага
//     ImGui::Begin("Поле врага");
//     for (int y = 0; y < enemyField.getHeight(); ++y) {
//         for (int x = 0; x < enemyField.getWidth(); ++x) {
//             CellStatus cell = enemyField.getCellStatus(x, y);
//             const char* cellSymbol = "#"; // Неизвестная клетка

//             switch (cell) {
//                 case CellStatus::Unknown:
//                     cellSymbol = "#"; // Неизвестная клетка
//                     break;
//                 case CellStatus::Empty:
//                     cellSymbol = "~"; // Вода
//                     break;
//                 case CellStatus::Ship:
//                     try {
//                         ShipSegmentStatus segmentStatus = enemyField.getSegmentStatus(x, y);
//                         switch (segmentStatus) {
//                             case ShipSegmentStatus::Whole:
//                                 cellSymbol = "#"; // Корабль (скрыт)
//                                 break;
//                             case ShipSegmentStatus::Damaged:
//                                 cellSymbol = "1"; // Повреждённый сегмент
//                                 break;
//                             case ShipSegmentStatus::Destroyed:
//                                 cellSymbol = "~"; // Уничтоженный сегмент
//                                 break;
//                         }
//                     } catch (const std::runtime_error&) {
//                         cellSymbol = "~"; // Ошибка получения статуса
//                     }
//                     break;
//                 default:
//                     cellSymbol = "~";
//             }

//             ImGui::Text("%s", cellSymbol);
//             if (x < enemyField.getWidth() - 1) ImGui::SameLine();
//         }
//     }
//     ImGui::End();
// }

// Great GUI

#include "field_render.h"
#include "field.h"
#include "ship.h"
#include "imgui.h"

void FieldRenderer::drawField(const GameField& playerField, const GameField& enemyField) const {
    // Рисуем поле игрока
    ImGui::Begin("Поле игрока");
    for (int y = 0; y < playerField.getHeight(); ++y) {
        for (int x = 0; x < playerField.getWidth(); ++x) {
            CellStatus cell = playerField.getCellStatus(x, y);

            // Определяем цвет клетки
            ImVec4 color;
            switch (cell) {
                case CellStatus::Empty:
                    color = ImVec4(0.0f, 0.5f, 1.0f, 1.0f); // Голубой
                    break;
                case CellStatus::Ship:
                    try {
                        ShipSegmentStatus segmentStatus = playerField.getSegmentStatus(x, y);
                        if (segmentStatus == ShipSegmentStatus::Whole)
                            color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Серый!!!!
                        else if (segmentStatus == ShipSegmentStatus::Damaged)
                            color = ImVec4(1.0f, 0.65f, 0.0f, 1.0f); // Оранжевый
                        else if (segmentStatus == ShipSegmentStatus::Destroyed)
                            color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Красный
                    } catch (...) {
                        color = ImVec4(0.0f, 0.5f, 1.0f, 1.0f); // Голубой
                    }
                    break;
                case CellStatus::Unknown:
                    color = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Серый
                    break;
                default:
                    color = ImVec4(0.0f, 0.5f, 1.0f, 1.0f); // Голубой
                    break;
            }

            // Рисуем цветную кнопку для клетки с уникальным идентификатором
            char label[16];
            snprintf(label, sizeof(label), "%d,%d", x, y);
            ImGui::PushStyleColor(ImGuiCol_Button, color);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);

            ImGui::Button(label, ImVec2(60, 60)); // Размер клетки увеличен

            ImGui::PopStyleColor(3);

            if (x < playerField.getWidth() - 1) {
                ImGui::SameLine(0.0f, 0.0f); // Убираем зазор между клетками
            }
        }
    }
    ImGui::End();

    // Рисуем поле врага
    ImGui::Begin("Поле врага");
    for (int y = 0; y < enemyField.getHeight(); ++y) {
        for (int x = 0; x < enemyField.getWidth(); ++x) {
            CellStatus cell = enemyField.getCellStatus(x, y);

            // Определяем цвет клетки
            ImVec4 color;
            switch (cell) {

                case CellStatus::Unknown:
                    color = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Серый
                    break;

                case CellStatus::Empty:
                    color = ImVec4(0.0f, 0.5f, 1.0f, 1.0f); // Голубой
                    break;

                // dead ship
                case CellStatus::deadship:
                    color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // красный
                    break;


                case CellStatus::Ship:
                    try {
                        ShipSegmentStatus segmentStatus = enemyField.getSegmentStatus(x, y);
                        if (segmentStatus == ShipSegmentStatus::Whole)
                            color = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Серый (скрытые корабли)
                        else if (segmentStatus == ShipSegmentStatus::Damaged)
                            color = ImVec4(1.0f, 0.65f, 0.0f, 1.0f); // Оранжевый
                    } catch (...) {
                        color = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Серый
                    }
                    break;
            }

            // Рисуем цветную кнопку для клетки с уникальным идентификатором
            char label[16];
            snprintf(label, sizeof(label), "%d,%d", x, y);
            ImGui::PushStyleColor(ImGuiCol_Button, color);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);

            ImGui::Button(label, ImVec2(60, 60)); // Размер клетки увеличен

            ImGui::PopStyleColor(3);

            if (x < enemyField.getWidth() - 1) {
                ImGui::SameLine(0.0f, 0.0f); // Убираем зазор между клетками
            }
        }
    }
    ImGui::End();
}
