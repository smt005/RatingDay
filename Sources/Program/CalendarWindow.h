#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "ContentWindow.h"

//class SelectorWindow;
class RatingWindow;

class CalendarWindow final : public ContentWindow {
private:
	struct TextData {
		inline static const size_t size = 128;
		char chars[size];
	};

	struct Element {
		TextData id;
		TextData rate;
		TextData description;
	};

public:
	CalendarWindow(/*const std::weak_ptr<SelectorWindow>& selectorWindow,*/ const std::weak_ptr<RatingWindow>& ratingWindow);
	void Render() override;
	void CalendarRender();
	void MakeUi();

private:
	//std::weak_ptr<SelectorWindow> _selectorWindow;
	std::weak_ptr<RatingWindow> _ratingWindow;
	std::string _dayTimeStr;
	Element* _editElement = nullptr;
	std::vector<Element> _texts;
	int _testOffsetMount = 0;
};
