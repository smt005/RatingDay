#pragma once

#include <AppWindow.h>
#include <vector>
#include "ContentWindow.h"

class SelectorWindow final : public Window {

public:
	SelectorWindow(std::vector<ContentWindow::Ptr>& windows);
	void Render() override;

private:
	std::vector<ContentWindow::Ptr> _windows;
	std::vector<ContentWindow::Ptr>::iterator _currentWindow;
};
