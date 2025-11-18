
#include "CalendarWindow.h"
#include <iostream>
#include <imgui.h>
#include <Log.h>
#include <Help.h>
#include <ImGuiHelp.h>
#include "DataManager.h"

//std::vector<std::string> CalendarWindow::_days = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

CalendarWindow::CalendarWindow(DataManager::Ptr dataManager)
    : _dataManager(dataManager)
{
    MakeUi();
}

void CalendarWindow::Render() {
    {
        ImGuiFontHandler font(36);
        ImGui::TextColored({ 0.3f, 0.6f, 0.9f, 1.f }, _dayTimeStr.c_str());
    }
    ImGui::Separator();
};

void CalendarWindow::MakeUi()
{
    DataManager::DayTime dayTime = DataManager::CurrentTime();
    _dayTimeStr = TO_STRING("Day: {} {} {}", dayTime.day, dayTime.month, dayTime.year);


}
