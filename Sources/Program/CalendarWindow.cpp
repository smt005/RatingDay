
#include "CalendarWindow.h"
#include <iostream>
#include <imgui.h>
#include <Log.h>
#include "Data.h"

std::vector<std::string> CalendarWindow::_days = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

CalendarWindow::CalendarWindow(Data& data)
    : Window("CalendarWindow")
    , _data(data)
{
    MakeUi();
}

void CalendarWindow::Render() {
    ImGui::Text("RatingDay Application");

    for (const auto& dayName: _days) {
        TextData& textData = _texts[dayName];
        if (ImGui::InputText(TO_STRING("{}##{}", dayName, dayName).c_str(), textData.chars, textData.size)) {
            _data._value["2025"][dayName] = textData.chars;
        }
    }
};

void CalendarWindow::MakeUi()
{
    for (const auto& dayName : _days) {
        auto it = _texts.emplace(dayName, TextData());
        TextData& textData = it.first->second;

        if (_data._value["2025"][dayName].isString()) {
            const std::string_view textInfo = _data._value["2025"][dayName].asCString();
            memcpy(textData.chars, textInfo.data(), textInfo.size());
        }
    }
}
