#include "gui_logger.h"

void GuiLogger::addLog(const std::string& message) {
    logs.push_back(message);
}

void GuiLogger::clear() {
    logs.clear();
}

void GuiLogger::render() {
    ImGui::Begin("Лог");
    if (ImGui::Button("Очистить лог")) {
        clear();
    }
    ImGui::Separator();

    for (const auto& log : logs) {
        ImGui::TextWrapped("%s", log.c_str());
    }

    ImGui::End();
}
