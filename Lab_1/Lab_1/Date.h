#pragma once
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


	/*
		Nessary method to avoid repetitive code
	*/
	bool is_leap_year()
	{
		return ((this->year % 4 == 0) && (this->year % 100 != 0) && (this->year % 400 == 0));
	}

	/*
		Nessary method to avoid repetitive code
	*/
	int days_in_month()
	{
		if (this->month == 1 || this->month == 3 || this->month == 5 || this->month == 7 || this->month == 8 || this->month == 10 || this->month == 12)
		{
			return 31;
		}
		else if (this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11)
		{
			return 30;
		}
		else
		{
			if (is_leap_year)
			{
				return 29;
			}
			else
			{
				return 28;
			}
		}
	}

	/*
		Method for checking the rightness of date
	*/
	bool check_date()
	{
		if (this->year < 0)
		{
			return false;
		}
		
		if (this->month < 1 || this->month > 12)
		{
			return false;
		}
		if (this->day < 0 || this->day > days_in_month())
		{
			return false;
		}
		if (this->hour < 0 || this->hour > 23)
		{
			return false;
		}
		if (this->minute < 0 || this->minute > 59)
		{
			return false;
		}
		if (this->second < 0 || this->second > 59)
		{
			return false;
		}
		return true;
	}

	/*
		Method that returns:
			"0": if compared date is bigger; 
			"1": if this date is bigger;
			"2": if dates are equal.
	*/
	int bigger_then_date(const Date& compared_date)
	{
		if (this->year > compared_date.year)
		{
			return 1;
		}
		else if (this->year < compared_date.year)
		{
			return 0;
		}
		else
		{
			if (this->month > compared_date.month)
			{
				return 1;
			}
			else if (this->month < compared_date.month)
			{
				return 0;
			}
			else
			{
				if (this->day > compared_date.day)
				{
					return 1;
				}
				else if (this->day < compared_date.day)
				{
					return 0;
				}
				else
				{
					if (this->hour > compared_date.hour)
					{
						return 1;
					}
					else if (this->hour < compared_date.hour)
					{
						return 0;
					}
					else
					{
						if (this->minute > compared_date.minute)
						{
							return 1;
						}
						else if (this->minute < compared_date.minute)
						{
							return 0;
						}
						else
						{
							if (this->second > compared_date.second)
							{
								return 1;
							}
							else if (this->second < compared_date.second)
							{
								return 0;
							}
							else
							{
								return 2;
							}
						}
					}
				}
			}
		}
	}

	/*
		Method for defining differnce with some date and returns it as a some date
	*/
	Date difference_with_date(const Date &compared_date)
	{
		Date difference;
		/*
			Algorithm is simple: starting from seconds to years
			we subtract from the bigger date the lower one.
			If it is less then 0, then we decrement elder rank of date 
			(f.e.: month <- day) and add the maximum of rank (f.e.: 60 for minutes).
			As a result we get a date, that is a difference 
		*/
		if (bigger_then_date(compared_date) == 0)
		{
			difference.second = compared_date.second - this->second; 
			if (difference.second < 0) 
			{
				difference.second = difference.second + 60;
				difference.minute--;
			}
			
			difference.minute = difference.minute + compared_date.minute - this->minute;
			if (difference.minute < 0)
			{
				difference.minute = difference.minute + 60;
				difference.hour--;
			}

			difference.hour = difference.hour + compared_date.hour - this->hour;
			if (difference.hour < 0)
			{
				difference.hour = difference.hour + 24;
				difference.day--;
			}

			difference.day = difference.day + compared_date.day - this->day;
			if (difference.day < 0)
			{
				difference.day = difference.day + days_in_month();
				difference.month--;
			}
			difference.month = difference.month + compared_date.month - this->month;
			if (difference.month < 0)
			{
				difference.month = difference.month + 12;
				difference.year--;
			}
			difference.year = difference.year + compared_date.year - this->year;
		}
		else if (bigger_then_date(compared_date) == 1)
		{
			difference.second = this->second - compared_date.second;
			if (difference.second < 0)
			{
				difference.second = difference.second + 60;
				difference.minute--;
			}

			difference.minute = difference.minute + this->minute - compared_date.minute;
			if (difference.minute < 0)
			{
				difference.minute = difference.minute + 60;
				difference.hour--;
			}

			difference.hour = difference.hour + this->hour - compared_date.hour;
			if (difference.hour < 0)
			{
				difference.hour = difference.hour + 24;
				difference.day--;
			}

			difference.day = difference.day + this->day - compared_date.day;
			if (difference.day < 0)
			{
				difference.day = difference.day + compared_date.days_in_month();
				difference.month--;
			}
			difference.month = difference.month + this->month - compared_date.month;
			if (difference.month < 0)
			{
				difference.month = difference.month + 12;
				difference.year--;
			}
			difference.year = difference.year + this->year - compared_date.year;
		}
		else
		{

		}
		return difference;
	}

	/*
		Method for counting chosen units of time 
		(with initial date for counting days/hours/minutes/seconds
	*/
	unsigned long long number_of_units_of_time(const char mode, const Date& initial_date)
	{
		/*
			We make a copy of date to avoid any changes in variable
		*/
		Data copy_of_date {this->year, this->month, this->day, this->hour, this->minute, this->second};
		//int months = this->month + this->year * 12;

		/*
			Counting months
		*/
		//copy_of_date.month += copy_of_month.year * 12;

		/*
			Counting days, that's a main problem, because we have different 
			number of days in different months and years (leap year)
		*/
		/*
		do
		{
			for (size_t i = 0; i < months; i++)
			{

			}
			while (copy_of_date.months > 0)
			{
				

				copy_of_date.day += .days_in_month()

					copy_of_date.month--;
			}
			copy_of_date.year--;
		} while (copy_of_date.year > 0)
		*/

		if (mode == 'd')
		{
			return copy_of_date.day;
		}
		else if (mode == 'h')
		{
			return copy_of_date.day * 24 + copy_of_date.hour;
		}
		else if (mode == 'm')
		{
			return (copy_of_date.day * 24 + copy_of_date.hour) * 60;
		}
		else if (mode == 's')
		{
			return (copy_of_date.day * 24 + copy_of_date.hour) * 3600;
		}
	}
	
	/*
		Method for counting chosen units of time
	*/
	unsigned long long number_of_units_of_time(const char mode)
	{
		if (mode == 'y')
		{
			return this->year;
		}
		else
		{
			return this->year * 12 + this->month;
		}
	}

	/*
		Method for defining day of the week
	*/
	string day_of_week()
	{
		/*
			Kim Larson's formula of defining the day of week:
			W = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) mod 7
		*/
		if (this->month == 1 || this->month == 2) 
		{
			/*
				New variables to avoid changes in variable
			*/
			int month = this->month + 12;
			int year = this->year - 1;
		}
		unsigned int index_of_week = (this->day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
		switch (index_of_week)
		{
		case 0: return "Monday"; break;
		case 1: return "Tuesday"; break;
		case 2: return "Wednesday"; break;
		case 3: return "Thursday"; break;
		case 4: return "Friday"; break;
		case 5: return "Saturday"; break;
		case 6: return "Sunday"; break;
		}
	}
};
