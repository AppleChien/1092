#pragma once
#ifndef ReservationInquiry_H
#define ReservationInquiry_H
#include"AvailTable.h"
#include"ReservationDatabase.h"
#include"MakeReservation.h"
#include <vector>
class ReservationInquiry {
public:
	void doviewReservation(vector< Reservation >& reservations, vector< AvailTable >& availSeats)
	{
		ReservationDatabase reservationdatabase;
		AvailTable at;
		reservationdatabase.loadReservations(reservations);
		if (reservations.size() == 0)
		{
			cout << "\nNo reservations!\n";
			return;
		}
		else {
			for (int i = 0; i < reservations.size(); i++) {
				if (reservations[i].numCustomers != 0)
					break;
				if (i == reservations.size() - 1 && reservations[i].numCustomers == 0) {
					cout << "\nNo reservations!\n";
					return;
				}

			}
		}

		char reservationNumber[12];
		cout << "\nEnter reservation number: ";
		cin >> reservationNumber;
		cin.ignore();

		if (!exist(reservations, reservationNumber)) {
			cout << "\nNo reservations with this reservation number!\n";
			return;
		}

		char password[12];
		cout << "\nEnter reservation password: ";
		cin >> password;
		cin.ignore();

		if (!exist(reservations, reservationNumber, password))
		{
			cout << "\nYou have no reservations!\n";
			return;
		}
		reservationdatabase.displayReservationInfo(reservations, reservationNumber);
		
		MakeReservation m;
		int i = 0;
		for (i; i < reservations.size(); i++) {
			if (strcmp(reservations[i].reservationNumber, reservationNumber) == 0) {
				break;
			}
		}

		cout << "\n\nCancel this reservation? ( y/n )";
		char a;
		cin >> a;
		if (a == 'y') {
			reservationdatabase.findSeat(availSeats, reservations[i], 1);
			cout << "\nThis reservation has been cancelled.\n";
			reservations[i] = Reservation();
			return;
		}
		else if (a == 'n') {
			return;
		}
	}

	bool exist(const vector< Reservation >& reservations, char reservationNumber[], char password[])
	{
		for (int i = 0; i <= reservations.size() - 1; i++)
		{
			if (strcmp(reservations[i].reservationNumber, reservationNumber) == 0 && strcmp(reservations[i].password, password) == 0)
				return true;
		}
		return false;
	}

	bool exist(const vector< Reservation >& reservations, char reservationNumber[])
	{
		for (int i = 0; i <= reservations.size() - 1; i++)
		{
			if (strcmp(reservations[i].reservationNumber, reservationNumber) == 0)
				return true;
		}
		return false;
	}

	
};
#endif