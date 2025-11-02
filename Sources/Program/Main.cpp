
#include <iostream>
#include <imgui.h>
#include "MainWindow.h"

class FirstWindow : public Window
{
public:
    FirstWindow()
        : Window("FirstWindow")
    {}
    FirstWindow(std::string_view name)
        : Window(name)
    {}

    void Render() override {
        ImGui::Text("RatingDay Application");
        ImGui::Text("This is a sample window.");
        if (ImGui::Button("Close")) {
            std::cout << "Is " << GetName() << " window" << std::endl;
        }
    };
};

int main() {
    MainWindow window;
    
    if (!window.Initialize()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return 1;
    }

    window.AddWindow(std::make_unique<FirstWindow>());
    window.AddWindow(std::make_unique<FirstWindow>("SecondWindow"));

    window.Run();
    return 0;
}
