
#include "WindowsManager.h"
//#include <windows.h>
//#include <GL/gl.h>
#include "imgui.h"
//#include "imgui_impl_win32.h"
//#include "imgui_impl_opengl3.h"
//#include <array>
#include <filesystem>
#include <Help.h>

int WindowsManager::width = 400;
int WindowsManager::height = 800;
std::map<int, ImFont*> WindowsManager::_largeFonts;

int width;
int height;
bool m_bFullscreen;

void WindowsManager::Render() {
    for (const auto& window : _windows) {
        if (window && window->IsVisible()) {
            if (window->IsFullScreen()) {
                ImGui::SetNextWindowPos(ImVec2(0, 0));
                ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)));
                ImGui::Begin(window->GetName().c_str(), nullptr, 
                    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
                    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | 
                    ImGuiWindowFlags_NoBringToFrontOnFocus);
            } else {
                ImGui::Begin(window->GetName().c_str());
            }
            window->Render();
            ImGui::End();
        }
    }
}

Window::Wptr WindowsManager::AddWindow(Window::Ptr window)
{
    if (!window) {
        return {};
    }
    
    return _windows.emplace_back(std::move(window));
}

void WindowsManager::RemoveWindow(std::string_view nameWindow)
{
    const auto it = std::find_if(_windows.begin(), _windows.end(), [nameWindow](const auto& window) {
        return window->GetName() == nameWindow;
    });

    if (it != _windows.end()) {
        _windows.erase(it);
    }
}

ImFont* WindowsManager::GetFont(int size)
{
    if (!_largeFonts.contains(size)) {
#ifdef _DEBUG
        static std::string fontPath = "Sans.ttf";

        if (fontPath.empty()) {
            static std::vector<std::string> fontPaths = { "Font01.otf", "Font02.otf", "Font03.otf", "Font04.otf", "Font05.otf", "Font06.otf", "Font01.ttf", "Font02.ttf", "Font03.ttf", "Font04.ttf", "Font05.ttf", "Font06.ttf", "Font07.ttf" };

            Json::Value objectValue;
            help::loadJson("Font.json", objectValue);
            int num = 0;
            if (!objectValue.isNull()) {
                num = objectValue["num"].asInt();
                if (num >= fontPaths.size()) {
                    num = 0;
                }
            }
            
            fontPath = fontPaths[num];
            objectValue["lastIndex"] = num;
            objectValue["lastFont"] = fontPath;

            ++num;
            objectValue["num"] = num;
            objectValue["lastFont"] = fontPath;
            help::saveJson("Font.json", objectValue);
        }
#else
        static const std::string fontPath = "Sans.ttf";
#endif
        if (!std::filesystem::exists(fontPath)) {
            return nullptr;
        }
        
        ImFontConfig fontCfg;
        fontCfg.SizePixels = size;

        ImGuiIO& io = ImGui::GetIO();
        ImFont*  font = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), fontCfg.SizePixels, &fontCfg, io.Fonts->GetGlyphRangesCyrillic());

        if (!font) {
            return nullptr;
        }

        _largeFonts.emplace(size, font);
    }

    return _largeFonts[size];
}
