// ◦ Xyz ◦

#include "ViewManager.h"
#include "Rating.h"
#include "Statistics.h"
#include "Calendar.h"

const ContentView::Ptr& ViewManager::GetCurrentView() const
{
	return _currentView;
}

const Rating::Ptr& ViewManager::GetRatingView()
{
	if (!_ratingView) {
		_ratingView = std::make_shared<Rating>();
	}
	return _ratingView;
}

const Calendar::Ptr& ViewManager::GetCalendarView()
{
	if (!_calendarView) {
		_calendarView = std::make_shared<Calendar>();
	}

	return _calendarView;
}

const Statistics::Ptr& ViewManager::GetStaticsticsView()
{
	if (!_staticsticsView) {
		_staticsticsView = std::make_shared<Statistics>();
	}

	return _staticsticsView;
}

void ViewManager::SetDrawRating(const DataManager::DayTime& dayTime)
{
	GetRatingView()->SelectDay(dayTime);
	_currentView = _ratingView;
}

void ViewManager::SetDrawCalendar()
{

	GetCalendarView();
	_currentView = _calendarView;
}

void ViewManager::SetDrawStaticstics()
{
	GetStaticsticsView();
	_currentView = _staticsticsView;
}
