// ◦ Xyz ◦

#pragma once
#include <Singletone.h>
#include "DataManager.h"

class ContentView;
class Rating;
class Calendar;
class Statistics;

class ViewManager final : public Singletone<ViewManager> {
public:
	const std::shared_ptr<ContentView>& GetCurrentView() const;
	const std::shared_ptr<Rating>& GetRatingView();
	const std::shared_ptr<Calendar>& GetCalendarView();
	const std::shared_ptr<Statistics>& GetStaticsticsView();

	void SetDrawRating(const DataManager::DayTime& dayTime);
	void SetDrawCalendar();
	void SetDrawStaticstics();

private:
	std::shared_ptr<ContentView> _currentView;
	std::shared_ptr<Rating> _ratingView;
	std::shared_ptr<Calendar> _calendarView;
	std::shared_ptr<Statistics> _staticsticsView;
};
