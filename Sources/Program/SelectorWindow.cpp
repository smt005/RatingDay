
#include "SelectorWindow.h"
#include <iostream>
#include <imgui.h>
#include <Log.h>
#include "DataManager.h"
#include "ContentWindow.h"

SelectorWindow::SelectorWindow(std::vector<ContentWindow::Ptr>& windows)
    : Window("SelectorWindow")
    , _windows(windows)
    , _currentWindow(_windows.begin())
{}

void SelectorWindow::Render() {
    static bool needBorder = false;
    static const float border = 20.f;
    static const float heightButtons = 40.f;
    const float heightList = static_cast<float>(AppWindow::height) - heightButtons - border;
    const float widthList = static_cast<float>(AppWindow::width) - border;

    ImGui::BeginChild("List", { widthList, heightList }, needBorder);

    if (_currentWindow != _windows.end() && *_currentWindow) {
        (*_currentWindow)->Render();
    }

    ImGui::EndChild();
    ImGui::Separator();

    if (ImGui::Button("<<", { 100.f, 30.f })) {
        if (_currentWindow != _windows.end()) {
            if (_currentWindow != _windows.begin()) {
                _currentWindow = std::prev(_currentWindow);
            }
            else {
                _currentWindow = std::prev(_windows.end());
            }
        }
    }
    
    ImGui::SameLine();

    if (ImGui::Button("<>", { 100.f, 30.f })) {
        _currentWindow = _windows.begin();
    }

    ImGui::SameLine();

    if (ImGui::Button(">>", { 100.f, 30.f })) {
        if (_currentWindow != _windows.end()) {
            _currentWindow = std::next(_currentWindow);

            if (_currentWindow == _windows.end()) {
                _currentWindow = _windows.begin();
            }
        }
    }
}
