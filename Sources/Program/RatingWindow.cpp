
#include "RatingWindow.h"
#include <iostream>
#include <imgui.h>
#include <Log.h>
#include <Help.h>
#include "DataManager.h"

DataManager::Day day;

RatingWindow::RatingWindow(DataManager::Ptr dataManager)
    : _dataManager(dataManager)
{
    MakeUi();
}

void RatingWindow::Render() {
    ImGui::TextColored({ 0.3f, 0.6f, 0.9f, 1.f }, _dayTimeStr.c_str());
    ImGui::Separator();

    for (const auto& ratings : day) {
        if (_descriptions.contains(ratings.id)) {
            ImGui::Text(_descriptions[ratings.id].c_str());
        }
        else {
            ImGui::Text(std::to_string(ratings.id).c_str());
        }

        ImGui::SameLine(200);
        ImGui::Text(std::to_string(ratings.rate).c_str());
        
        ImGui::SameLine();
        ImGui::PushID(ratings.id);
        if (ImGui::Button(":", ImVec2(20.f, 20.f))) {
            LOG("TEST: set rating {}", ratings.id);
        }
        ImGui::PopID();

        ImGui::Separator();
    }
};

void RatingWindow::MakeUi()
{
    DataManager::DayTime dayTime = DataManager::CurrentTime();
    _dayTimeStr = TO_STRING("Day: {} {} {}", dayTime.day, dayTime.month, dayTime.year);

    day = _dataManager->GetRating(dayTime);
    _descriptions = _dataManager->GetDescriptions();
}
