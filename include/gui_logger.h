#ifndef GUI_LOGGER_H
#define GUI_LOGGER_H

#include <vector>
#include <string>
#include "imgui.h"

class GuiLogger {
public:
    void addLog(const std::string& message);
    void clear();
    void render();

private:
    std::vector<std::string> logs;
};

#endif
