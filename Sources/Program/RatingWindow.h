#pragma once

#include <AppWindow.h>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "ContentWindow.h"

class DataManager;

class RatingWindow : public ContentWindow {
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
	RatingWindow(std::shared_ptr<DataManager> data);
	void Render() override;
	void MakeUi();

private:
	std::shared_ptr<DataManager> _dataManager;
	std::string _dayTimeStr;
	Element* _editElement = nullptr;
	std::vector<Element> _texts;
};
