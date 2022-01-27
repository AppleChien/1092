#pragma once
#ifndef ReservationDatabase_H
#define ReservationDatabase_H
#include"Reservation.h"
#include <vector>
#include <fstream>
class ReservationDatabase {
public:
	void loadReservations(vector< Reservation >& reservations)
	{
		ifstream inreservation("Reservations.dat", ios::binary);
		if (!inreservation)
		{
			cout << "Reservations can not open";
			system("pause");
		}
		Reservation i;
		while (!inreservation.eof())
		{
			inreservation.read(reinterpret_cast<char*>(&i), sizeof(i));
			if (i.date.year == 2000)
				continue;
			reservations.push_back(i);
		}
		inreservation.close();
	}

	void storeReservations(vector< Reservation >& reservations)
	{
		ofstream outreservation("Reservations.dat", ios::binary);
		if (!outreservation)
			cout << "No";
		if (reservations.size() != 0)
			for (int i = 0; i <= reservations.size() - 1; i++) {
				outreservation.write(reinterpret_cast<char*>(&reservations[i]), sizeof(reservations[i]));
			}
		outreservation.close();
	}


	void displayReservationInfo(vector< Reservation >& reservations,
		char reservationNumber[])
	{
		Reservation k;
		cout << endl;
		int count = 0;
		for (size_t i = 0; i < reservations.size(); ++i)
			if (strcmp(reservations[i].reservationNumber, reservationNumber) == 0)
			{
				cout << setw(2) << ++count << ". ";
				k.displayReservationInfo(reservations, reservations[i].numCustomers,
					reservations[i].date, reservations[i].time, reservations[i].name,
					reservations[i].mobileNumber, reservations[i].email, reservations[i].password, reservationNumber);
			}
	}

	void findSeat(vector< AvailTable >& availSeats, Reservation newreservation, int number)
	{
		MakeReservation m;
		int location = m.findAvailSeat(availSeats, newreservation.date);
		int TableCode = 0;
		if (newreservation.numCustomers == 1 || newreservation.numCustomers == 2) {
			TableCode = 1;
		}
		else if (newreservation.numCustomers == 3 || newreservation.numCustomers == 4) {
			TableCode = 2;
		}
		else if (newreservation.numCustomers == 5) {
			TableCode = 3;
		}
		else if (newreservation.numCustomers == 6 || newreservation.numCustomers == 7) {
			TableCode = 4;
		}
		else if (newreservation.numCustomers == 10 || newreservation.numCustomers == 11 || newreservation.numCustomers == 12) {
			TableCode = 5;
		}

		if (location >= 0)
			availSeats[location].numAvailTables[newreservation.time][TableCode] += number;

	}

};
#endif