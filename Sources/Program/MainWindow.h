// ◦ Xyz ◦

#pragma once

#include <WindowsManager.h>
#include <vector>
#include "ContentView.h"
#include "DataManager.h"

class MainWindow final : public Window {
public:
	using Ptr = std::shared_ptr<MainWindow>;
	using Wptr = std::weak_ptr<MainWindow>;

public:
	MainWindow();
	void Render() override;
	void OnClose() override;

	void Init();

private:
};
