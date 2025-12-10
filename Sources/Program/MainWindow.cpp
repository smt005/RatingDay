// ◦ Xyz ◦

#include "MainWindow.h"
#include <ImGuiHelp.h>
#include <Help.h>
#include <Log.h>
#include "DataManager.h"
#include "ContentView.h"
#include "Rating.h"
#include "Calendar.h"
#include "Statistics.h"
#include "ViewManager.h"

MainWindow::MainWindow()
    : Window(help::GetClassName<MainWindow>())
{
    Init();
}

void MainWindow::Render() {
    auto& properties = WindowsManager::Instance().properties;

    static bool needBorder = false;
    static const float border = 20.f;
    static const float heightButtons = 40.f;
    const float heightList = static_cast<float>(properties.height) - heightButtons - border;
    const float widthList = static_cast<float>(properties.width) - border;

    ImGui::BeginChild("List", { widthList, heightList }, needBorder);
    
    if (auto view = ViewManager::Instance().GetCurrentView()) {
        view->Render();
    }

    ImGui::EndChild();
    ImGui::Separator();

    constexpr float countButton = 3.f;
    constexpr float spacingButton = 11.f;
    const float widthButton = static_cast<float>(properties.width) / countButton - spacingButton;
    const ImVec2 sizeButton(widthButton, 30.f);
    
    if (ImGui::Button("|||", sizeButton)) {
        ViewManager::Instance().SetDrawCalendar();
    }

    ImGui::SameLine();

    if (ImGui::Button("=", sizeButton)) {
        ViewManager::Instance().SetDrawRating(DataManager::CurrentTime());
    }

    ImGui::SameLine();

    if (ImGui::Button("~", sizeButton)) {
        ViewManager::Instance().SetDrawStaticstics();
    }
}

void MainWindow::OnClose()
{
    if (const auto& ratingView = ViewManager::Instance().GetRatingView()) {
        if (ratingView->IsValidDay()) {
            ratingView->Save();
        }
    }
}

void MainWindow::Init()
{
    DataManager::Instance().Load("Test");
    ViewManager::Instance().SetDrawRating(DataManager::CurrentTime());
}
