
#include <Windows.h>
#include <iostream>
#include <imgui.h>
#include <MainWindow.h>
#include "CalendarWindow.h"
#include "Data.h"

int main() {
    FreeConsole();

    MainWindow window;
    if (!window.Initialize()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return 1;
    }

    Data data("Test");;
    window.AddWindow(std::make_unique<CalendarWindow>(data));

    window.Run();
    data.Save();

    return 0;
}
