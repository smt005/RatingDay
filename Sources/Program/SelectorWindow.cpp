
#include "SelectorWindow.h"
#include <iostream>
#include <imgui.h>
#include <Log.h>
#include "DataManager.h"

SelectorWindow::SelectorWindow(std::vector<Window::Wptr>& windows)
    : Window("SelectorWindow")
    , _windows(windows)
    , _currentWindow(_windows.begin())
{}

void SelectorWindow::Render() {
    if (ImGui::Button("<<", { 100.f, 30.f })) {
        _currentWindow->lock()->SetVisible(false);

        if (_currentWindow != _windows.begin()) {
            _currentWindow = std::prev(_currentWindow);
        }
        else {
            _currentWindow = std::prev(_windows.end());
        }
        
        _currentWindow->lock()->SetVisible(true);
    }

    ImGui::SameLine();

    if (ImGui::Button(">>", { 100.f, 30.f })) {
        _currentWindow->lock()->SetVisible(false);

        _currentWindow = std::next(_currentWindow);

        if (_currentWindow == _windows.end()) {
            _currentWindow = _windows.begin();
        }

        _currentWindow->lock()->SetVisible(true);
    }
}
