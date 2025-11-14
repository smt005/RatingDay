
#include "RatingWindow.h"
#include <iostream>
#include <imgui.h>
#include <Log.h>
#include <Help.h>
#include "AppWindow.h"
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

    const static float buttonSpaceWistrh = 200.f;
    const float widthDescription = AppWindow::width - buttonSpaceWistrh;

    for (const auto& ratings : day) {
        if (_descriptions.contains(ratings.id)) {
            ImGui::Text(_descriptions[ratings.id].c_str());
        }
        else {
            ImGui::Text(std::to_string(ratings.id).c_str());
        }

        ImGui::SameLine(widthDescription);
        RateButton(ratings.rate, ratings.id);

        ImGui::SameLine();
        ImGui::PushID(&ratings);
        if (ImGui::Button(":", ImVec2(20.f, 20.f))) {
            LOG("TEST: edit rating {}", ratings.id);
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

void RatingWindow::RateButton(int rate, int id)
{
    const static std::array<ImVec4, 6> colorButtons = { ImVec4(1.0f, 1.0f, 1.0f, 0.05f), ImVec4(0.9f, 0.0f, 0.0f, 1.f) , ImVec4(0.9f, 0.0f, 0.9f, 1.f) , ImVec4(0.0f, 0.0f, 0.9f, 1.f), ImVec4(0.0f, 0.9f, 0.9f, 1.f), ImVec4(0.0f, 0.9f, 0.0f, 1.f) };

    for (int i = 1; i <= 5; ++i) {
        const auto& colorButton = rate == i ? colorButtons[i] : colorButtons[0];

        ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
        if (ImGui::Button(TO_STRING("{}##{}", i, id).c_str(), ImVec2(20.f, 20.f))) {
            LOG("TEST: set rating {} -> {}", rate, i);
        }
        ImGui::PopStyleColor();
        ImGui::SameLine();
    }
}
