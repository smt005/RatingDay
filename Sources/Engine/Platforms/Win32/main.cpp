
//#include <Windows.h>
#include <iostream>
#include <MainWindow.h>

int MainInternal(MainWindow& window);
	
int main() {
    //FreeConsole();
    
    MainWindow window;
    if (!window.Initialize()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return 1;
    }
	
	MainInternal(window);

    return 0;
}
