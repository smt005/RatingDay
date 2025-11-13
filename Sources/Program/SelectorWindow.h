#include <AppWindow.h>
#include <vector>

class SelectorWindow final : public Window {

public:
	SelectorWindow(std::vector<Window::Wptr>& windows);
	void Render() override;

private:
	std::vector<Window::Wptr> _windows;
	std::vector<Window::Wptr>::iterator _currentWindow;
};
