// ◦ Xyz ◦

#include <WindowsManager.h>
#include "DataManager.h"
#include "MainWindow.h"

bool Initialize()
{
    if (MainWindow::Ptr mainWindow = std::make_shared<MainWindow>()) {
        WindowsManager& windowsManager = WindowsManager::Instance();

        auto& properties = windowsManager.properties;
        properties.title = L"Рейтинг дня";
        properties.width = 450;
        properties.height = 800;

        windowsManager.AddWindow(mainWindow);
        return true;
    }

    return false;
}
