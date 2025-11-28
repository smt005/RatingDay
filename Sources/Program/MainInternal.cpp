
#include <WindowsManager.h>
#include "ContentWindow.h"
#include "CalendarWindow.h"
#include "RatingWindow.h"
#include "StatisticsWindow.h"
#include "SelectorWindow.h"
#include "DataManager.h"

bool Initialize()
{
    DataManager::Instance().Load("Test");
    std::vector<ContentWindow::Ptr> windows;

    const std::shared_ptr<RatingWindow> ratingWindow = std::make_shared<RatingWindow>();
    windows.emplace_back(ratingWindow);
    windows.emplace_back(std::make_shared<StatisticsWindow>());
    windows.emplace_back(std::make_shared<CalendarWindow>(ratingWindow));

    WindowsManager::Instance().AddWindow(std::make_shared<SelectorWindow>(windows));

    return true;
}
