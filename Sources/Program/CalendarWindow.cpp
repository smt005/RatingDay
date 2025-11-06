
#include "CalendarWindow.h"
#include <iostream>
#include <imgui.h>
#include <Log.h>
#include "DataManager.h"

//std::vector<std::string> CalendarWindow::_days = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

CalendarWindow::CalendarWindow(DataManager::Ptr dataManager)
    : Window("CalendarWindow")
    , _dataManager(dataManager)
{
    MakeUi();
}

void CalendarWindow::Render() {
    ImGui::Text(("Day: {}", _dayTimeStr).c_str());

    int guiId = 0;
    ImGui::Separator();

    for (auto& element : _texts) {
        ImGui::InputText(TO_STRING("id##{}", guiId).c_str(), element.id.chars, element.id.size);
        ImGui::InputText(TO_STRING("rate##{}", guiId).c_str(), element.rate.chars, element.rate.size);
        ImGui::InputText(TO_STRING("des##{}", guiId).c_str(), element.description.chars, element.description.size);
        
        ImGui::Separator();

        ++guiId;
    }

    if (!_editElement) {
        if (ImGui::Button("Add", { 100, 30 })) {
            _editElement = &_texts.emplace_back();
        }
    }

    if (_editElement) {
        if (ImGui::Button("Save", { 100, 30 })) {
            DataManager::Day day;

            for (auto& element : _texts) {
                auto& newRating = day.emplace_back();
                
                {
                    std::string str = (element.id.chars);
                    int id = std::stoi(str.c_str());
                    newRating.id = id;
                }
                {
                    std::string str = (element.rate.chars);
                    int rate = std::stoi(str.c_str());
                    newRating.rate = rate;
                }
                newRating.description = element.description.chars;
            }

            DataManager::DayTime dayTime = DataManager::CurrentTime();
            LOG("Add dayTime: {} {} {}", dayTime.year, dayTime.month, dayTime.day);

            _dataManager->SetRating(dayTime, day);
        }
    }
};

void CalendarWindow::MakeUi()
{
    DataManager::DayTime dayTime = DataManager::CurrentTime();
    _dayTimeStr = TO_STRING("Day: {} {} {}", dayTime.day, dayTime.month, dayTime.year);

    DataManager::Day day = _dataManager->GetRating(dayTime);

    for (const auto& ratings : day) {
        Element& element = _texts.emplace_back();

        {
            const std::string str = TO_STRING("{}", ratings.id);
            memcpy(element.id.chars, str.data(), str.size());
        }
        {
            const std::string str = TO_STRING("{}", ratings.rate);
            memcpy(element.rate.chars, str.data(), str.size());
        }
        {
            const std::string str = TO_STRING("{}", ratings.rate);
            memcpy(element.description.chars, str.data(), str.size());
        }
    }
}
