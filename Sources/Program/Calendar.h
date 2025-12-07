// ◦ Xyz ◦

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "ContentView.h"

class SelectorWindow;

class Calendar final : public ContentView {
public:
	using Ptr = std::shared_ptr<Calendar>;
	using Wptr = std::weak_ptr<Calendar>;

public:
	Calendar();
	void Render() override;
	void CalendarRender();
	void MakeUi();

private:
	std::string _dayTimeStr;

private: // Для отладки
	int _testOffsetMount = 0;
};
