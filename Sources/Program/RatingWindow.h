#pragma once

#include <AppWindow.h>
#include <string>
#include <memory>
#include <unordered_map>
#include "ContentWindow.h"

class DataManager;

class RatingWindow : public ContentWindow {
public:
	RatingWindow(std::shared_ptr<DataManager> data);
	void Render() override;
	void Save() override;

	void MakeUi();
	void RateButton(int& rate, int id, float& offset);

private:
	std::string _dayTimeStr;
	std::shared_ptr<DataManager> _dataManager;
	std::unordered_map<int, std::string> _descriptions;
};
