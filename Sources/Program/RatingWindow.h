#pragma once

#include <WindowsManager.h>
#include <string>
#include <memory>
#include <unordered_map>
#include "ContentWindow.h"
#include "DataManager.h"

class DataManager;

class RatingWindow : public ContentWindow {
public:
	RatingWindow();
	void Render() override;
	void Save() override;

	void SelectDay(const DataManager::DayTime& dayTime);
	void RateButton(int& rate, int id, float& offset);

private:
	std::string _dayTimeStr;
	std::unordered_map<int, std::string> _descriptions;
	DataManager::Day _day;
};
