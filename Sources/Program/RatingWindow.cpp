// ◦ Xyz ◦

#include "RatingWindow.h"
#include <iostream>
#include <imgui.h>
#include <Log.h>
#include "AppWindow.h"
#include <Help.h>
#include <ImGuiHelp.h>

RatingWindow::RatingWindow(DataManager::Ptr dataManager)
    : _dataManager(dataManager)
{
    DataManager::DayTime dayTime = DataManager::CurrentTime();
    SelectDay(dayTime);
}

void RatingWindow::Render() {
    {
        ImGuiFontHandler font(36);
        ImGui::TextColored({ 0.3f, 0.6f, 0.9f, 1.f }, _dayTimeStr.c_str());
    }
    ImGui::Separator();

    const static float buttonSpaceWistrh = 110.f;
    const float widthDescription = AppWindow::width - buttonSpaceWistrh;
    

    for (auto& ratings : _day) {
        ImGuiFontHandler font(AppWindow::GetFont(24));

        if (_descriptions.contains(ratings.id)) {
            ImGui::Text(_descriptions[ratings.id].c_str());
        }
        else {
            ImGui::Text(std::to_string(ratings.id).c_str());
        }

        float offset = widthDescription;
        RateButton(ratings.rate, ratings.id, offset);

        {
            offset += 10.f;
            ImGui::SameLine(offset);

            ImGuiIdHandler idHandler(&ratings);
            ImGuiFontHandler font(14);

            if (ImGui::Button(":", ImVec2(20.f, 20.f))) {
                LOG("TEST: edit rating {}", ratings.id);
            }
        }

        ImGui::Separator();
    }
};

void RatingWindow::Save()
{
    DataManager::DayTime dayTime = DataManager::CurrentTime();
    _dataManager->SetRating(dayTime, _day);
}

void RatingWindow::SelectDay(const DataManager::DayTime& dayTime)
{
    _dayTimeStr = TO_STRING("Day: {}.{}.{}", dayTime.day, dayTime.month, dayTime.year);
    _descriptions = _dataManager->GetDescriptions();

    _day.clear();
    _day.reserve(_descriptions.size());
    _day = _dataManager->GetRating(dayTime);

    for (const auto& [id, description] : _descriptions) {
        if (std::find_if(_day.begin(), _day.end(), [id](const auto& ratingData) { return ratingData.id == id; }) == _day.end()) {
            _day.emplace_back(id, 0);
        }
    }
}

void RatingWindow::RateButton(int& rate, int id, float& offset)
{
    const static ImVec4 defColor = { 0.5f, 0.5f, 0.5f, 0.5f };
    const static std::array<ImVec4, 3> colorButtons = { ImVec4(0.9f, 0.3f, 0.3f, 1.f) , ImVec4(0.3f, 0.3f, 0.9f, 1.f), ImVec4(0.3f, 0.9f, 0.3f, 1.f) };
    
    ImGuiFontHandler font(14);

    for (int i = 0; i < colorButtons.size(); ++i) {
        ImGui::SameLine(offset);
        offset += 20.f;

        const auto& colorButton = (rate >= 0 || rate < colorButtons.size()) && i == rate ? colorButtons[rate] : defColor;
        ImGui::PushStyleColor(ImGuiCol_Button, colorButton);

        if (ImGui::Button(TO_STRING("{}##{}", i, id).c_str(), ImVec2(20.f, 20.f))) {
            LOG("TEST: set rating {} -> {}", rate, i);
            rate = i;
        }

        ImGui::PopStyleColor();
    }
}
