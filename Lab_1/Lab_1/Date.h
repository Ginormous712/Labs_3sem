#pragma once
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <random>
#include <string>

using namespace std;
class Date
{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	friend std::ostream& operator<< (std::ostream& out, const Date& date);
public:
	Date(int year = 0, int month = 0, int day = 0, int hour = 0, int minute = 0, int second = 0)
	{
		this->year = year;
		this->month = month;
		this->day = day;
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}
	bool isLeapYear();
	int daysInMonth();
	bool checkDate(const bool year = true, const bool month = true, const bool day = true,
		const bool hour = true, const bool minute = true, const bool second = true);
	int biggerThenDate(const Date& compared_date);
	Date differenceWithDate(Date& compared_date);
	unsigned long long numberOfUnitsOfTime(const char mode);
	unsigned long long numberOfUnitsOfTime(const char mode, Date& initial_date);
	void addTime(int time, const char mode);
	void subtractTime(int time, const char mode);
	int dayOfWeek();
	int weekOfMonth();
	int weekOfYear();
};

#endif // !DATE_H

