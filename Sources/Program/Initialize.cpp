// ◦ Xyz ◦

#include <WindowsManager.h>
#include "DataManager.h"
#include "MainWindow.h"

bool Initialize()
{
    DataManager::Instance().Load("Test");

    if (MainWindow::Ptr mainWindow = std::make_shared<MainWindow>()) {
        WindowsManager::Instance().AddWindow(mainWindow);
    }

    return true;
}
