
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
    if (_currentWindow != _windows.end() && *_currentWindow) {
        (*_currentWindow)->Render();
    }

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

    if (ImGui::Button(">>", { 100.f, 30.f })) {
        if (_currentWindow != _windows.end()) {
            _currentWindow = std::next(_currentWindow);

            if (_currentWindow == _windows.end()) {
                _currentWindow = _windows.begin();
            }
        }
    }
}
