// ◦ Xyz ◦

#include "Calendar.h"
#include <iostream>
#include <ctime>
#include <imgui.h>
#include <Log.h>
#include <Help.h>
#include <ImGuiHelp.h>
#include "DataManager.h"
#include "ViewManager.h"
#include "WindowsManager.h"
#include "Rating.h"
#include "MainWindow.h"

Calendar::Calendar()
{
    MakeUi();
}

// Helper function to get number of days in a month
static int GetDaysInMonth(int month, int year) {
    if (month == 2) {
        // February: check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29;
        }
        return 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

// Helper function to get day of week for the first day of the month (0 = Sunday, 1 = Monday, etc.)
static int GetFirstDayOfWeek(int day, int month, int year) {
    std::tm time_in = {};
    time_in.tm_year = year - 1900;
    time_in.tm_mon = month - 1;
    time_in.tm_mday = 1;
    std::mktime(&time_in);
    return time_in.tm_wday; // 0 = Sunday, 1 = Monday, ..., 6 = Saturday
}

void Calendar::Render() {
    static int vertical = 0;

    {
        ImGuiFontHandler font(36);
        ImGui::TextColored({ 0.3f, 0.6f, 0.9f, 1.f }, _dayTimeStr.c_str());

        if (ImGui::Button("0##cal", { 30.f, 30.f })) {
            vertical = 0;
        }
        if (ImGui::Button("1##cal", { 30.f, 30.f })) {
            vertical = 1;
        }
        if (ImGui::Button("2##cal", { 30.f, 30.f })) {
            vertical = 2;
        }
        if (ImGui::Button("3##cal", { 30.f, 30.f })) {
            vertical = 3;
        }
    }
    ImGui::Separator();

    
    
    if (vertical == 0) {
        CalendarRender();
    }
    else if (vertical == 1) {
        if (ImGui::Button("-##cal", { 30.f, 30.f })) {
            _testOffsetMount -= 1;
        }
        
        ImGui::SameLine();
        
        ImGui::Separator();
        if (ImGui::Button("+##cal", { 30.f, 30.f })) {
            _testOffsetMount += 1;
        }
        ImGui::SameLine();
        CalendarRender();
    }
    else if (vertical == 2) {
        if (ImGui::Button("-##cal", { WindowsManager::width - 20.f, 30.f })) {
            _testOffsetMount -= 1;
        }

        ImGui::SameLine();

        CalendarRender();

        ImGui::SameLine();

        ImGui::Separator();
        if (ImGui::Button("+##cal", { WindowsManager::width - 20.f, 30.f })) {
            _testOffsetMount += 1;
        }
    }
}

void Calendar::CalendarRender()
{
    DataManager::DayTime currentTime = DataManager::CurrentTime();
    int currentYear = currentTime.year;
    int currentMonth = currentTime.month + _testOffsetMount;
    int currentDay = currentTime.day;

    // Month names
    const char* monthNames[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Day names (starting from Monday)
    const char* dayNames[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

    // Display month and year header
    {
        ImGuiFontHandler font(24);
        ImGui::TextColored({ 0.4f, 0.7f, 0.9f, 1.f }, "%s %d", monthNames[currentMonth - 1], currentYear);
    }
    ImGui::Spacing();

    // Calculate calendar data
    int daysInMonth = GetDaysInMonth(currentMonth, currentYear);
    int firstDayOfWeek = GetFirstDayOfWeek(1, currentMonth, currentYear);
    
    // Convert from Sunday-based (0=Sunday) to Monday-based (0=Monday)
    // Sunday (0) becomes 6, Monday (1) becomes 0, etc.
    int startOffset = (firstDayOfWeek == 0) ? 6 : firstDayOfWeek - 1;

    // Calendar grid
    const float cellSize = 60.0f;
    const float spacing = 2.0f;

    // Day names header - use invisible buttons for alignment
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, 0));
    {
        ImGuiFontHandler font(14);
        for (int i = 0; i < 7; ++i) {
            if (i > 0) ImGui::SameLine(0, spacing);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.6f, 0.6f, 0.6f, 1.f));
            ImGui::Button(dayNames[i], ImVec2(cellSize, cellSize * 0.5f));
            ImGui::PopStyleColor(4);
        }
    }
    ImGui::PopStyleVar();
    ImGui::Spacing();

    // Calendar days grid
    {
        ImGuiFontHandler font(34);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, spacing));
        int dayCounter = 1;
        bool monthStarted = false;

        for (int week = 0; week < 6; ++week) {
            for (int dayOfWeek = 0; dayOfWeek < 7; ++dayOfWeek) {
                if (dayOfWeek > 0) ImGui::SameLine(0, spacing);

                if (!monthStarted && dayOfWeek == startOffset) {
                    monthStarted = true;
                }

                if (monthStarted && dayCounter <= daysInMonth) {
                    bool isToday = (dayCounter == currentDay);
                    ImVec4 dayColor = isToday ? ImVec4(0.3f, 0.6f, 0.9f, 1.f) : ImVec4(1.f, 1.f, 1.f, 1.f);
                    ImVec4 bgColor = isToday ? ImVec4(0.2f, 0.4f, 0.6f, 0.3f) : ImVec4(0.1f, 0.1f, 0.1f, 0.2f);

                    ImGui::PushStyleColor(ImGuiCol_Button, bgColor);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(bgColor.x + 0.1f, bgColor.y + 0.1f, bgColor.z + 0.1f, bgColor.w));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(bgColor.x + 0.2f, bgColor.y + 0.2f, bgColor.z + 0.2f, bgColor.w));
                    ImGui::PushStyleColor(ImGuiCol_Text, dayColor);

                    char dayStr[4];
                    snprintf(dayStr, sizeof(dayStr), "%d", dayCounter);

                    if (ImGui::Button(dayStr, ImVec2(cellSize, cellSize))) {
                        if (const auto& ratingView = ViewManager::Instance().GetRatingView()) {
                            if (ratingView->IsValidDay()) {
                                ratingView->Save();
                            }

                            DataManager::DayTime dayTime{ dayCounter, currentMonth, currentYear };
                            ViewManager::Instance().SetDrawRating(dayTime);
                            LOG("Selected day: {}", dayCounter);
                        }
                    }

                    ImGui::PopStyleColor(4);
                    dayCounter++;
                }
                else {
                    // Empty cell
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.05f, 0.05f, 0.05f, 0.1f));
                    ImGui::Button(TO_STRING(".##{}{}", week, dayOfWeek).c_str(), ImVec2(cellSize, cellSize));
                    ImGui::PopStyleColor();
                }
            }
            if (dayCounter > daysInMonth) break;
        }
        ImGui::PopStyleVar();
    }
};

void Calendar::MakeUi()
{
    DataManager::DayTime dayTime = DataManager::CurrentTime();
    _dayTimeStr = TO_STRING("Day: {} {} {}", dayTime.day, dayTime.month, dayTime.year);


}
