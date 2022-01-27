#pragma once
#ifndef DATE_H
#define DATE_H
#include <string>
#include <iomanip>
#include <iostream>
#include<ctime>
using namespace std;

struct Date
{
	int year = 2000;
	int month = 0;
	int day = 0;	
};

class DATE{
public:
	bool earlier(const Date& date1, const Date& date2);
	int difference(const Date& date1, const Date& date2);
	bool leapYear(int year);
	Date addition(const Date& currentDate, int numDays);
	void computeCurrentDate(Date& currentDate);
};

// array of days per month
int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool DATE::earlier(const Date& date1, const Date& date2)
{
	if (date1.year < date2.year)
		return true;
	else if (date1.year > date2.year)
		return false;
	else {
		if (date1.month < date2.month)
			return true;
		else if (date1.month > date2.month)
			return false;
		else {
			if (date1.day < date2.day)
				return true;
			else
				return false;
		}
	}
}

int DATE::difference(const Date& date1, const Date& date2)
{
	int y, m, d, t = 0;
	Date date3;
	date3 = date2;
	while (1)
	{
		if (date3.year == date1.year && date3.month == date1.month && date3.day == date1.day)
			return t;
		else
		{
			t++;
			date3.day++;
			if (date3.day > days[date3.month])
			{
				date3.day = 1;
				date3.month++;
				if (date3.month > 12)
				{
					date3.month = 1;
					date3.year++;
				}
			}
		}
	}
}

bool DATE::leapYear(int year)
{
	return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

Date DATE::addition(const Date& currentDate, int numDays)
{
	Date date;
	date.year = currentDate.year;
	date.month = currentDate.month;
	date.day = currentDate.day + numDays;
	while (date.day > days[date.month])
	{
		date.day -= days[date.month];
		date.month++;
		if (date.month > 13)
		{
			date.month = 1;
			date.year++;
		}
	}
	return date;
}

void DATE::computeCurrentDate(Date& currentDate)
{
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int remainingSeconds = static_cast<int>(time(0)) + 8 * 60 * 60;

	currentDate.year = 1970;

	int secondsPerYear = 365 * 24 * 60 * 60;
	if (leapYear(currentDate.year))
		secondsPerYear += 24 * 60 * 60;

	while (remainingSeconds >= secondsPerYear)
	{
		remainingSeconds -= secondsPerYear;
		currentDate.year++;

		secondsPerYear = 365 * 24 * 60 * 60;
		if (leapYear(currentDate.year))
			secondsPerYear += 24 * 60 * 60;
	}
	
	if (leapYear(currentDate.year))
		days[2] = 29;

	currentDate.month = 1;
	while (remainingSeconds >= days[currentDate.month] * 24 * 60 * 60)
	{
		remainingSeconds -= days[currentDate.month] * 24 * 60 * 60;
		currentDate.month++;
	}

	currentDate.day = remainingSeconds / (24 * 60 * 60) + 1;
}
#endif