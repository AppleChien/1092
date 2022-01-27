#pragma once
#ifndef Reservation_H
#define Reservation_H
#include "Date.h"
#include <vector>
#include <fstream>

class Reservation {
public:
	void displayReservationInfo(vector< Reservation >& reservations,int numCustomers, Date date, int time, char name[], char mobileNumber[], char email[], char password[], char reservationNumber[])
	{	
		cout << " Mobile No.      Name          Date     Time                         Email    No of Customers    Password    Reservation No.";
		cout << "     " << mobileNumber << "        " << name;

		cout << "    " << date.year << "/";
		if (date.month < 10)
			cout << '0';
		cout << date.month << "/";
		if (date.day < 10)
			cout << '0';
		cout << date.day;

		char times[4][8] = { "", "11:30", "14:30", "17:30" };
		cout << "     " << times[time] << "                            ";
		cout << email << "                  " << numCustomers;
		cout << "          " << password << "           ";
		cout << reservationNumber;
	}

	int numCustomers = 0;             // number of customers
	Date date = Date();               // reservation date
	int time = 0;                     // reservation time code
	char name[8] = "";                // name
	char mobileNumber[12] = "";       // mobile phone number
	char email[40] = "";              // email address
	char password[12] = "";           // reservation password
	char reservationNumber[12] = "";  // reservation numberR
};
#endif