
#include <imgui.h>
#include <MainWindow.h>
#include "CalendarWindow.h"
#include "RatingWindow.h"
#include "StatisticsWindow.h"
#include "SelectorWindow.h"
#include "DataManager.h"

int MainInternal(MainWindow& window) {
    DataManager::Ptr dataManager = std::make_shared<DataManager> ("Test");
    std::vector<Window::Wptr> windows;

    auto ratingWindow = window.AddWindow(std::make_shared<RatingWindow>(dataManager));
    windows.emplace_back(ratingWindow);

    auto statisticsWindow = window.AddWindow(std::make_shared<StatisticsWindow>(dataManager));
    windows.emplace_back(statisticsWindow);
    statisticsWindow.lock()->SetVisible(false);
    
    auto calendarWindow = window.AddWindow(std::make_shared<CalendarWindow>(dataManager));
    windows.emplace_back(calendarWindow);
    calendarWindow.lock()->SetVisible(false);

    window.AddWindow(std::make_shared<SelectorWindow>(windows));

    window.Run();
    dataManager->Save();

    return 0;
}
