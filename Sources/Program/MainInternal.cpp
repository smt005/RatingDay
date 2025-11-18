
#include <imgui.h>
#include <AppWindow.h>
#include "ContentWindow.h"
#include "CalendarWindow.h"
#include "RatingWindow.h"
#include "StatisticsWindow.h"
#include "SelectorWindow.h"
#include "DataManager.h"

int MainInternal(AppWindow& window) {
    DataManager::Ptr dataManager = std::make_shared<DataManager> ("Test");
    std::vector<ContentWindow::Ptr> windows;

    windows.emplace_back(std::make_shared<RatingWindow>(dataManager));
    windows.emplace_back(std::make_shared<StatisticsWindow>(dataManager));
    windows.emplace_back(std::make_shared<CalendarWindow>(dataManager));

    window.AddWindow(std::make_shared<SelectorWindow>(windows));
    window.Run();

    (*windows.begin())->Save();
    dataManager->Save();
    return 0;
}
