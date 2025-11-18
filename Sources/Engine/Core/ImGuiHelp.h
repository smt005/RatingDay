// ◦ Xyz ◦

#pragma once

#include <imgui.h>
#include <AppWindow.h>

struct ImGuiFontHandler {
    ImGuiFontHandler(ImFont* _font)
        : font(_font)
    {
        if (font) {
            ImGui::PushFont(font);
        }
    }

    ImGuiFontHandler(int size)
        : font(AppWindow::GetFont(size))
    {
        if (font) {
            ImGui::PushFont(font);
        }
    }

    ~ImGuiFontHandler() {
        if (font) {
            ImGui::PopFont();
        }
    }

    ImFont* font;
};

struct ImGuiIdHandler {
    ImGuiIdHandler(void* _id)
        : id(_id)
    {
        if (id) {
            ImGui::PushID(id);
        }
    }

    ~ImGuiIdHandler() {
        if (id) {
            ImGui::PopID();
        }
    }

    void* id;
};
