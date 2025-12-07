// ◦ Xyz ◦

#pragma once

#include <WindowsManager.h>
#include <string>
#include <memory>
#include <unordered_map>
#include "ContentView.h"
#include "DataManager.h"

class DataManager;

class Rating : public ContentView {
public:
	using Ptr = std::shared_ptr<Rating>;
	using Wptr = std::weak_ptr<Rating>;

	struct Chars
	{
		Chars() = default;
		Chars(const std::string& text)
		{
			const size_t size = text.size();
			std::memcpy(chars, text.c_str(), size);
			chars[size] = '\0';
		}
		void Clear() {
			chars[0] = '\0';
		}
		static const size_t size = 256;
		char chars[256];
	};

public:
	Rating();
	void Render() override;
	void Save() override;

	bool IsValidDay();
	void SelectDay(const DataManager::DayTime& dayTime);
	void RateButton(int& rate, int id, float& offset);

private:
	DataManager::DayTime _dayTime;
	DataManager::Day _day;
	std::unordered_map<int, std::string> _descriptions;
	std::string _dayTimeStr;
	std::vector<Chars> _charsInputs;
};
