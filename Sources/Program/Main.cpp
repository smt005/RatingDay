#include "MainWindow.h"
#include <iostream>

int main() {
    MainWindow window;
    
    if (!window.Initialize()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return 1;
    }

    window.Run();

    return 0;
}
