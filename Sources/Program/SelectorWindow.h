#pragma once

#include <AppWindow.h>
#include <vector>
#include "ContentWindow.h"
#include "DataManager.h"

/*template <typename T>
class Singlitone {
	static Singlitone& Instance()
	{
		static T* instance = nullptr;
		if (!instance) {
			instance = new T();
		}
		return *instance;
	}
	void Destroy()
	{
		delete instance;
		instance = nullptr;
	}
}*/

class SelectorWindow final : public Window {

public:
	SelectorWindow(std::vector<ContentWindow::Ptr>& windows);
	void Render() override;
	void ViewRatingWindow(const DataManager::DayTime& dayTime);

private:
	std::vector<ContentWindow::Ptr> _windows;
	std::vector<ContentWindow::Ptr>::iterator _currentWindow;
};
