#pragma once

#include <WindowsManager.h>
#include <vector>
#include "ContentWindow.h"
#include "DataManager.h"

class SelectorWindow final : public Window {

public:
	SelectorWindow(std::vector<ContentWindow::Ptr>& windows);
	void Render() override;
	void OnClose() override;

	void ViewRatingWindow(const DataManager::DayTime& dayTime);

private:
	std::vector<ContentWindow::Ptr> _windows;
	std::vector<ContentWindow::Ptr>::iterator _currentWindow;
};
