// ◦ Xyz ◦

#include "DataManager.h"
#include <chrono>
#include <ctime>
#include <Help.h>
#include <Log.h>

DataManager::DayTime DataManager::CurrentTime()
{
	const auto nowTime = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(nowTime);
	std::tm* currentTime = std::localtime(&time);

	return { currentTime->tm_mday, 1 + currentTime->tm_mon, 1900 + currentTime->tm_year };
}

bool DataManager::Load(std::string_view name)
{
	_fileNamePath = TO_STRING("{}.json", name);
	return help::loadJson(_fileNamePath, _value);
}

bool DataManager::Save() const
{
#ifdef _DEBUG
	static bool compact = false;

	if (compact) {
		return help::saveJson(_fileNamePath, _value, "");
	}
	else {
		return help::saveJson(_fileNamePath, _value);
	}
#else
	return help::saveJson(_fileNamePath, _value, "");
#endif
}

DataManager::Day DataManager::GetRating(DayTime time) const
{
	Day ratingsDay;

	const std::string yearKey = TO_STRING("{}", time.year);
	const std::string montKey = TO_STRING("{}", time.month);
	const std::string dayKey = TO_STRING("{}", time.day);

	const auto& dayValue = _value[yearKey][montKey][dayKey];
	if (dayValue.isNull() || !dayValue.isObject()) {
		return ratingsDay;
	}
	
	for (const auto& idStr : dayValue.getMemberNames()) {
		const auto& rateValue = dayValue[idStr]["r"];
		if (rateValue.isNull() || !rateValue.isInt()) {
			continue;
		}

		const int id = std::stoi(idStr.c_str());
		RatingData& ratingData = ratingsDay.emplace_back(id);
		ratingData.rate = rateValue.asInt();

		const auto& infoValue = dayValue[idStr]["i"];
		if (!infoValue.isNull() && infoValue.isString()) {
			ratingData.description = infoValue.asString();
		}
	}

	return ratingsDay;
}

void DataManager::SetRating(DayTime time, const Day& ratingsDay)
{
	if (ratingsDay.empty()) {
		return;
	}

	const std::string yearKey = TO_STRING("{}", time.year);
	const std::string montKey = TO_STRING("{}", time.month);
	const std::string dayKey = TO_STRING("{}", time.day);

	auto& ratingsValue = _value[yearKey][montKey][dayKey];

	for (const auto& rating : ratingsDay) {
		Json::Value& ratingValue = ratingsValue[std::to_string(rating.id)];
		ratingValue["r"] = rating.rate;

		if (!rating.description.empty()) {
			ratingValue["i"] = rating.description;
		}
	}
}

std::unordered_map<int, std::string> DataManager::GetDescriptions() const
{
	std::unordered_map<int, std::string> descriptions;

	const auto& descriptionsValue = _value["Description"];
	if (descriptionsValue.isNull() || !descriptionsValue.isObject()) {
		return descriptions;
	}

	for (const auto& idStr : descriptionsValue.getMemberNames()) {
		const auto descriptionValue = descriptionsValue[idStr];

		if (!descriptionValue.isNull() && descriptionValue.isString()) {
			const int id = std::stoi(idStr.c_str());
			descriptions.emplace(id, descriptionValue.asCString());
		}
	}

	return descriptions;
}
