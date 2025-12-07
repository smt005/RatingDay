// ◦ Xyz ◦

#include "Rating.h"
#include <imgui.h>
#include "WindowsManager.h"
#include <ImGuiHelp.h>
#include <Help.h>
#include <Log.h>
#include "MainWindow.h"

Rating::Rating()
{
    DataManager::DayTime dayTime = DataManager::CurrentTime();
    SelectDay(dayTime);
}

void Rating::Render() {
    {
        ImGuiFontHandler font(36);
        ImGui::TextColored({ 0.3f, 0.6f, 0.9f, 1.f }, _dayTimeStr.c_str());
        ImGui::Separator();
    }

    constexpr ImVec4 backColorWindow(0.0824f, 0.0863f, 0.0902f, 1.f);
    constexpr float buttonSpaceWistrh = 150.f;
    const float widthDescription = WindowsManager::width - buttonSpaceWistrh;
    
    const size_t countSize = _day.size();
    for (size_t iDay = 0; iDay < countSize; ++iDay) {
        auto& ratings = _day[iDay];

        {
            ImGuiFontHandler font(WindowsManager::GetFont(24));

            if (_descriptions.contains(ratings.id)) {
                ImGui::Text(_descriptions[ratings.id].c_str());
            }
            else {
                ImGui::Text(std::to_string(ratings.id).c_str());
            }
        }

        float offset = widthDescription;
        RateButton(ratings.rate, ratings.id, offset);

        {
            ImGui::SameLine(offset);

            ImGuiIdHandler idHandler(&ratings);
            ImGuiFontHandler font(14);
            ImGuiColorHandler style(ImGuiCol_Button, backColorWindow);

            if (ImGui::Button("X", ImVec2(20.f, 20.f))) {
                ratings.rate = -1;
                ratings.description.clear();
                _charsInputs[iDay].Clear();
            }
        }

        {
            ImGuiFontHandler font(WindowsManager::GetFont(12));
            ImGui::Dummy(ImVec2(0.f, 0.f));

                ImGuiIdHandler idHandler(&ratings);
                ImGuiColorHandler colorHandler(ImGuiCol_FrameBg, backColorWindow);
                ImGuiWidthHandler widthHandler(offset);

                if (ImGui::InputText("", _charsInputs[iDay].chars, _charsInputs[iDay].size)) {
                    ratings.description = _charsInputs[iDay].chars;
                }
            
        }

        ImGui::Separator();
    }
};

void Rating::Save()
{
    auto& dataManager = DataManager::Instance();
    dataManager.SetRating(_dayTime, _day);
    dataManager.Save();
}

bool Rating::IsValidDay()
{
    return _dayTime.IsValid();
}

void Rating::SelectDay(const DataManager::DayTime& dayTime)
{
    _dayTime = dayTime;
    _dayTimeStr = TO_STRING("Day: {}.{}.{}", _dayTime.day, _dayTime.month, _dayTime.year);

    if (_descriptions.empty()) {
        _descriptions = DataManager::Instance().GetDescriptions();
    }

    _day.clear();
    _day.reserve(_descriptions.size());
    _day = DataManager::Instance().GetRating(dayTime);

    for (const auto& [id, description] : _descriptions) {
        if (std::find_if(_day.begin(), _day.end(), [id](const auto& ratingData) { return ratingData.id == id; }) == _day.end()) {
            _day.emplace_back(id, -1);
        }
    }

    _charsInputs.clear();
    _charsInputs.reserve(_day.size());

    for (const auto& rating : _day) {
        _charsInputs.emplace_back(rating.description);
    }
}

void Rating::RateButton(int& rate, int id, float& offset)
{
    const static ImVec4 defColor = { 0.999f, 0.999f, 0.999f, 0.25f };
    const static std::array<ImVec4, 5> colorButtons = {
            ImVec4(1.f, 0.f, 0.f, 1.f),
            ImVec4(1.f, 0.5f, 0.f, 1.f),
            ImVec4(1.f, 1.f, 0.f, 1.f),
            ImVec4(0.75f, 1.f, 0.f, 1.f),
            ImVec4(0.f, 1.f, 0.f, 1.f) };

    ImGuiFontHandler font(14);
    ImGuiColorHandler colorHandler(ImGuiCol_Text, ImVec4(0.f, 0.f, 0.f, 1.f));

    for (int i = 0; i < colorButtons.size(); ++i) {
        ImGui::SameLine(offset);
        offset += 20.f;
        
        const auto colorButton = (rate < 0 || rate >= colorButtons.size()) ? colorButtons[i] : (i == rate) ? colorButtons[rate] : defColor;
        ImGuiColorHandler colorHandler(ImGuiCol_Button, colorButton);

        if (ImGui::Button(TO_STRING("{}##{}", i, id).c_str(), ImVec2(20.f, 20.f))) {
            rate = i;
        }
    }
}
