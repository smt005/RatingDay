
#include <iostream>
#include <AppWindow.h>
#include <Windows.h>

int MainInternal(AppWindow& window);
	
int main() {
    FreeConsole();
    
    AppWindow window;
    if (!window.Initialize()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return 1;
    }
	
	MainInternal(window);

    return 0;
}
