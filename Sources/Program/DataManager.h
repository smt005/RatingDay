// ◦ Xyz ◦

#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <json/json.h>
#include "Singletone.h"

class DataManager final : public Singletone<DataManager> {
public:
	using Ptr = std::shared_ptr<DataManager>;
	using Wptr = std::weak_ptr<DataManager>;

	struct DayTime
	{
		int day = 0;
		int month = 0;
		int year = 0;

		bool IsValid() const
		{
			return year > 0 && month > 0 && day > 0;
		}
	};

	struct RatingData {
		const int id;
		int rate;
		std::string description;
	};

	using Day = std::vector<RatingData>;
	using Days = std::vector<Day>;
	using Month = std::vector<Days>;
	using Months = std::vector<Month>;
	using Year = std::vector<std::pair<int, Months>>;
	
public:
	DataManager() = default;
	~DataManager() = default;

	static DayTime CurrentTime();

	bool Load(std::string_view name);
	bool Save() const;

	Day GetRating(DayTime time) const;
	void SetRating(DayTime time, const Day& ratingsDay);

	std::unordered_map<int, std::string> GetDescriptions() const;

private:
	std::string _fileNamePath;
	Json::Value _value;
};
