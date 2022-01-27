#pragma once
#ifndef AvailTable_H
#define AvailTable_H
#include "Date.h"
#include "AvailTableDatabase.h"
#include <vector>
class AvailTable {
public:

	void initializeAvailSeats(vector< AvailTable >& availSeats) {
		DATE datedays;
		Date currentDate;
		datedays.computeCurrentDate(currentDate);

		Date date;
		AvailTable seat;
		date = currentDate;
		if (availSeats.size() == 0)
		{
			for (int i = 0; i <= 30; i++)
			{
				seat.date.year = date.year;
				seat.date.month = date.month;
				seat.date.day = date.day;
				date.day++;
				if (date.day > days[date.month])
				{
					date.month++;
					date.day = 1;
					if (date.month > 12)
					{
						date.year++;
						date.month = 1;
					}
					else
						date.year = date.year;
				}
				else {
					date.month = date.month;
					date.year = date.year;
				}
				for (int i = 1; i <= 3; i++) {
					for (int j = 1; j <= 5; j++) {
						seat.numAvailTables[i][j] = 2;
					}
				}
				availSeats.push_back(seat);
			}
		}
		else
		{
			if (datedays.earlier(availSeats[availSeats.size() - 1].date, currentDate))
			{
				for (int i = 0; i <= 30; i++)
				{
					availSeats[i].date.year = date.year;
					availSeats[i].date.month = date.month;
					availSeats[i].date.day = date.day;
					date.day++;
					if (date.day > days[date.month])
					{
						date.month++;
						date.day = 1;
						if (date.month > 12)
						{
							date.year++;
							date.month = 1;
						}
						else
							date.year = date.year;
					}
					else {
						date.month = date.month;
						date.year = date.year;
					}
					for (int k = 1; k <= 3; k++) {
						for (int j = 1; j <= 5; j++) {
							availSeats[i].numAvailTables[k][j] = 2;
						}
					}

				}

			}
			else if (datedays.earlier(availSeats[0].date, currentDate))
			{
				for (int i = 0; i <= 30; i++)
				{
					availSeats[i] = availSeats[i + 1];

				}
				availSeats[30].date.day = availSeats[29].date.day + 1;
				if (availSeats[30].date.day > days[availSeats[30].date.month])
				{
					availSeats[30].date.month++;
					availSeats[30].date.day = 1;
					if (availSeats[30].date.month > 12)
					{
						availSeats[30].date.year++;
						availSeats[30].date.month = 1;
					}
					else
						availSeats[30].date.year = availSeats[29].date.year;
				}
				else {
					availSeats[30].date.month = availSeats[29].date.month;
					availSeats[30].date.year = availSeats[29].date.year;
				}
				for (int k = 1; k <= 3; k++) {
					for (int j = 1; j <= 5; j++) {
						availSeats[30].numAvailTables[k][j] = 2;
					}
				}

			}
		}
	}

	Date date;
	int numAvailTables[4][6]; // the number of available tables, specifically,
	 // numAvailTables[ 1 ][ i ] is  the number of available type i tables on 11:30
	 // numAvailTables[ 2 ][ i ] is  the number of available type i tables on 14:30
	 // numAvailTables[ 3 ][ i ] is  the number of available type i tables on 17:30
};
#endif