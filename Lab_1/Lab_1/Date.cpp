#include "Date.h"

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << "Date(" << date.day << "." << date.month << "." << date.year 
		<< "\t" << date.hour << ":" << date.minute << ":" << date.second << ")";
	return out;
}

/*
	Necessary method to avoid repetitive code
*/
bool Date::isLeapYear()
{
	return ((this->year % 4 == 0) && (this->year % 100 != 0) && (this->year % 400 == 0));
}

/*
	Nessary method to avoid repetitive code
*/
int Date::daysInMonth()
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
		if (isLeapYear())
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
bool Date::checkDate(const bool year = true, const bool month = true, const bool day = true,
	const bool hour = true, const bool minute = true, const bool second = true)
{
	if (year)
	{
		if (this->year < 0)
		{
			return false;
		}
	}
	if (month)
	{
		if (this->month < 1 || this->month > 12)
		{
			return false;
		}
	}
	if (day)
	{
		if (this->day < 1 || this->day > daysInMonth())
		{
			return false;
		}
	}
	if (hour)
	{
		if (this->hour < 0 || this->hour > 23)
		{
			return false;
		}
	}
	if (minute)
	{
		if (this->minute < 0 || this->minute > 59)
		{
			return false;
		}
	}
	if (second)
	{
		if (this->second < 0 || this->second > 59)
		{
			return false;
		}
	}
	return true;
}

/*
	Method that returns:
		"0": if compared date is bigger;
		"1": if this date is bigger;
		"2": if dates are equal.
*/
int Date::biggerThenDate(const Date& compared_date)
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
Date Date::differenceWithDate(Date& compared_date)
{
	Date difference;
	/*
		Algorithm is simple: starting from seconds to years
		we subtract from the bigger date the lower one.
		If it is less then 0, then we decrement elder rank of date
		(f.e.: month <- day) and add the maximum of rank (f.e.: 60 for minutes).
		As a result we get a date, that is a difference
	*/
	if (biggerThenDate(compared_date) == 0)
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
			difference.day = difference.day + daysInMonth();
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
	else if (biggerThenDate(compared_date) == 1)
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
			difference.day = difference.day + compared_date.daysInMonth();
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
	Methods for counting chosen units of time (with initial date
	for counting days/hours/minutes/seconds and without for years/months)
*/
unsigned long long Date::numberOfUnitsOfTime(const char mode)
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

unsigned long long Date::numberOfUnitsOfTime(const char mode, Date& initial_date)
{
	/*
		We make a copy of date to avoid any changes in variable
	*/
	Date copy_of_date{ this->year, initial_date.month, this->day, this->hour, this->minute, this->second };

	/*
		Counting months
	*/
	int months = this->month + this->year * 12;

	/*
		Counting days, adding days in month on every step
	*/
	for (; months > 0; months--)
	{
		copy_of_date.day += copy_of_date.daysInMonth();
		copy_of_date.month++;
		if (copy_of_date.month == 13)
		{
			copy_of_date.month = 1;
		}
	}

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
	Methods for adding/substracting chosen units of date to the date
*/
void Date::addTime(int time, const char mode)
{
	if (mode == 'y')
	{
		this->year += time;
	}
	else if (mode == 'M')
	{
		this->month += time;
		if (this->month > 12)
		{
			this->year += this->month / 12;
			this->month = (this->month % 12) + 1;
		}
	}
	else if (mode == 'd')
	{
		while (time > (daysInMonth() - this->day))
		{
			time -= daysInMonth();
			this->month++;
			if (this->month > 12)
			{
				this->month = 1;
				this->year++;
			}
		}
		this->day += time;
		if (this->day > daysInMonth())
		{
			this->day = daysInMonth();
		}
	}
	else if (mode == 'h')
	{
		while (time > (23 - this->hour))
		{
			this->day++;
			if (this->day > daysInMonth())
			{
				this->day = 1;
				this->month++;
				if (this->month > 12)
				{
					this->month = 1;
					this->year++;
				}
			}
			time -= 24;
		}
		this->hour += time;
	}
	else if (mode == 'm')
	{
		while (time > (59 - this->minute))
		{
			this->hour++;
			if (this->hour > 23)
			{
				this->hour = 0;
				this->day++;
				if (this->day > daysInMonth())
				{
					this->day = 1;
					this->month++;
					if (this->month > 12)
					{
						this->month = 1;
						this->year++;
					}
				}
			}
			time -= 60;
		}
		this->minute += time;
	}
	else
	{
		while (time > (59 - this->second))
		{
			this->minute++;
			if (this->minute > 59)
			{
				this->hour++;
				if (this->hour > 23)
				{
					this->hour = 0;
					this->day++;
					if (this->day > daysInMonth())
					{
						this->day = 1;
						this->month++;
						if (this->month > 12)
						{
							this->month = 1;
							this->year++;
						}
					}
				}
			}
			time -= 60;
		}
		this->second += time;
	}
}

void Date::subtractTime(int time, const char mode)
{

	if (mode == 'y')
	{
		this->year -= time;
	}
	else if (mode == 'M')
	{
		while (time >= this->month)
		{
			this->year--;
			if (time >= 12)
			{
				time -= 12;
			}
			else
			{
				this->month += (12 - time);
				return;
			}
		}
		this->month -= time;
	}
	else if (mode == 'd')
	{
		while (time >= this->day)
		{
			this->month--;
			if (checkDate(false, true, false, false, false, false) == false)
			{
				this->year--;
				this->month = 12;
			}

			if (time >= daysInMonth())
			{
				time -= daysInMonth();
			}
			else
			{
				this->day += (daysInMonth() - time);
				return;
			}
		}
		this->day -= time;
	}
	else if (mode == 'h')
	{
		while (time >= this->hour)
		{
			this->day--;
			if (checkDate(false, false, true, false, false, false) == false)
			{
				this->month--;
				if (checkDate(false, true, false, false, false, false) == false)
				{
					this->year--;
					this->month = 12;
				}
				this->day = daysInMonth();
			}

			if (time >= 24)
			{
				time -= 24;
			}
			else
			{
				this->hour += (24 - time);
				return;
			}
		}
	}
	else if (mode == 'm')
	{
		while (time >= this->minute)
		{
			this->hour--;
			if (checkDate(false, false, false, true, false, false) == false)
			{
				this->day--;
				if (checkDate(false, false, true, false, false, false) == false)
				{
					this->month--;
					if (checkDate(false, true, false, false, false, false) == false)
					{
						this->year--;
						this->month = 12;
					}
					this->day = daysInMonth();
				}
				this->hour = 23;
			}

			if (this->minute >= 60)
			{
				time -= 60;
			}
			else
			{
				this->minute += (60 - time);
				return;
			}
		}
		this->minute -= time;
	}
	else
	{
		while (time >= this->second)
		{
			this->minute--;
			if (checkDate(false, false, false, false, true, false) == false)
			{
				this->hour--;
				if (checkDate(false, false, false, true, false, false) == false)
				{
					this->day--;
					if (checkDate(false, false, true, false, false, false) == false)
					{
						this->month--;
						if (checkDate(false, true, false, false, false, false) == false)
						{
							this->year--;
							this->month = 12;
						}
						this->day = daysInMonth();
					}
					this->hour = 23;
				}
				this->minute = 59;
			}

			if (this->second >= 60)
			{
				time -= 60;
			}
			else
			{
				this->second += (60 - time);
				return;
			}
		}
		this->second -= time;
	}

}
/*
	Method for defining day of the week
*/
int Date::dayOfWeek()
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

	return (index_of_week + 1);
	/*
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
	*/
}

/*
	Method for counting week of month
*/
int Date::weekOfMonth()
{
	Date start_point(this->year, this->month, 1, this->hour, this->minute, this->second);

	if (start_point.dayOfWeek() >= dayOfWeek())
	{
		return ((this->day - 1) / 7 + 1);
	}
	else
	{
		return ((this->day - 1) / 7 + 2);
	}
}

/*
	Method for counting week of year
*/
int Date::weekOfYear()
{
	Date start_point(this->year, 1, 1, this->hour, this->minute, this->second);

	if (start_point.dayOfWeek() >= dayOfWeek())
	{
		return (differenceWithDate(start_point).day) / 7 + 1;
	}
	return (differenceWithDate(start_point).day) / 7 + 2;
}
