#pragma once
#include"Date.h"
#include"AvailTableDatabase.h"
#include"Reservation.h"
#include <vector>

class MakeReservation {
public:

	void domakeReservation(vector< Reservation >& reservations,
		vector< AvailTable >& availSeats)
	{
		DATE dateday;
		Reservation newReservation;
		cout << endl;
		do cout << "Enter the number of customers (1 - 7, 10 - 12): ";
		while ((newReservation.numCustomers = inputAnInteger(1, 12)) == -1);

		cout << "\nChoose a date:\n";
		Date currentDate;
		dateday.computeCurrentDate(currentDate);
		inputDate(availSeats, newReservation.date, currentDate,
			newReservation.numCustomers);

		inputTimeCode(availSeats, newReservation.date, newReservation.time,
			newReservation.numCustomers);

		cout << "\nEnter name: ";
		cin >> newReservation.name;

		cout << "\nEnter phone Number: ";
		cin >> newReservation.mobileNumber;
		cin.ignore();

		cout << "\nEnter email address: ";
		cin >> newReservation.email;
		cin.ignore();

		cout << "\nEnter reservation password: ";
		cin >> newReservation.password;
		cin.ignore();

		srand(time(NULL));
		int i = 0;
		for (i; i < 8; ++i)
			newReservation.reservationNumber[i] = rand() % 10 + '0';
		newReservation.reservationNumber[8] = '\0';

		cout << endl;
		newReservation.displayReservationInfo(reservations, newReservation.numCustomers,
			currentDate, newReservation.time,newReservation.name,
			newReservation.mobileNumber,newReservation.email,newReservation.password, newReservation.reservationNumber);

		cout << "\n\nReservation Completed.\n\n";

		reservations.push_back(newReservation);

		decreaseAvailSeats(availSeats, newReservation.date, newReservation.time,
			newReservation.numCustomers);
	}

	void decreaseAvailSeats(vector< AvailTable >& availSeats, const Date date,
		int timeCode, int requiredSeats)
	{
		int pos = findAvailSeat(availSeats, date);
		int j = tablecode(requiredSeats);
		if (pos >= 0) // found
			availSeats[pos].numAvailTables[timeCode][j]--;
	}


	void inputDate(vector< AvailTable >& availSeats, Date& date,
		const Date& currentDate, int numCustomers)
	{
		int a[31];
		int j = tablecode(numCustomers);
		for (int i = 1; i <= 30; i++)
		{
			if (availSeats[i].numAvailTables[1][j] == 0 && availSeats[i].numAvailTables[2][j] == 0 && availSeats[i].numAvailTables[3][j] == 0)
			{
				a[i] = 0;
				continue;
			}
			cout << setw(2) << i << ". " << availSeats[i].date.year << "/" << availSeats[i].date.month << "/" << availSeats[i].date.day << "   ";
			a[i] = 1;
			if (i % 4 == 0)
				cout << endl;
		}
		cout << endl;
		int choice;
		do {
			cout << "?";
			choice = inputAnInteger(1, 30);
		} while (a[choice] == 0 || choice == -1);

		date.year = availSeats[choice].date.year;
		date.month = availSeats[choice].date.month;
		date.day = availSeats[choice].date.day;
	}

	void inputTimeCode(const vector< AvailTable >& availSeats, const Date date,
		int& timeCode, int numCustomers)
	{
		cout << "\nChoose a time:\n";
		int i = findAvailSeat(availSeats, date), a[4] = {};
		int k = tablecode(numCustomers);
		for (int j = 1; j <= 3; j++)
			if (hasAvailableSeats(availSeats, date, j, numCustomers))
			{
				if (j == 1) {
					cout << setw(2) << j << ". 11:30\n";
					a[1] = 1;
				}

				if (j == 2) {
					cout << setw(2) << j << ". 14:30\n";
					a[2] = 1;
				}

				if (j == 3)
				{
					a[3] = 1;
					cout << setw(2) << j << ". 17:30\n";
				}
			}

		int choice;
		do {
			cout << "?";
			choice = inputAnInteger(1, 3);
		} while (a[choice] == 0 || choice == -1);

		timeCode = choice;
	}

	bool hasAvailableSeats(const vector< AvailTable >& availSeats, const Date date,
		int requiredSeats)
	{
		int j = tablecode(requiredSeats);
		for (int i = 1; i <= 30; i++) {
			if (availSeats[i].date.day == date.day && availSeats[i].date.month == date.month && availSeats[i].date.year == date.year)
				if (availSeats[i].numAvailTables[1][j] > 0 || availSeats[i].numAvailTables[2][j] > 0 || availSeats[i].numAvailTables[3][j] > 0)
					return true;
		}
		return false;
	}

	bool hasAvailableSeats(const vector< AvailTable >& availSeats, const Date date,
		int timeCode, int requiredSeats)
	{
		int i = findAvailSeat(availSeats, date);
		int j = tablecode(requiredSeats);
		if (availSeats[i].numAvailTables[timeCode][j] > 0)
			return true;

		return false;
	}

	int findAvailSeat(const vector< AvailTable >& availSeats, Date date)
	{
		for (int i = 0; i < availSeats.size(); i++)
		{
			if (availSeats[i].date.day == date.day && availSeats[i].date.month == date.month && availSeats[i].date.year == date.year)
				return i;
		}
		return -1;
	}

	int inputAnInteger(int begin, int end)
	{
		char code[3];
		int intcode;

		cin.getline(code, 3, '\n');

		if (code[0] == '0' && code[1] != '\0')
			return -1;
		int i = 0;
		while (code[i] != '\0')
		{
			if (!isdigit(code[i]))
				return -1;
			i++;
		}

		intcode = atoi(code);

		for (int j = begin; j <= end; j++)
		{
			if (intcode == j)
				return j;
		}
		return -1;

	}


	int tablecode(int requiredSeats) {
		int TableCode = 0;
		if (requiredSeats == 1 || requiredSeats == 2) {
			TableCode = 1;
		}
		else if (requiredSeats == 3 || requiredSeats == 4) {
			TableCode = 2;
		}
		else if (requiredSeats == 5) {
			TableCode = 3;
		}
		else if (requiredSeats == 6 || requiredSeats == 7) {
			TableCode = 4;
		}
		else if (requiredSeats == 10 || requiredSeats == 11 || requiredSeats == 12) {
			TableCode = 5;
		}
		return TableCode;
	}

};
