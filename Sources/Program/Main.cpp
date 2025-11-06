
//#include <Windows.h>
#include <iostream>
#include <imgui.h>
#include <MainWindow.h>
#include "CalendarWindow.h"
#include "DataManager.h"

int main() {
    //FreeConsole();

    MainWindow window;
    if (!window.Initialize()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return 1;
    }

    DataManager::Ptr dataManager = std::make_shared<DataManager> ("Test");
    window.AddWindow(std::make_unique<CalendarWindow>(dataManager));

    window.Run();
    dataManager->Save();

    return 0;
}
