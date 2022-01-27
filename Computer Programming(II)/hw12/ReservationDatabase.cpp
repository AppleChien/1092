#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace::std;

#include "ReservationDatabase.h" // ReservationDatabase class definition

extern Date computeCurrentDate();

// call loadReservations and removes outdated reservation informations
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
   Date d;
   d = computeCurrentDate();
   d = d + 1;
   for (int i = 0; i < reservations.size(); i++) {
	   if (reservations[i].getDate() < d) {
		   cancelReservation(reservations[i].getReservationNumber());
	   }
   }

}//hw

// call storeReservations
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

// returns true if there is a Reservation object containing specified reservationNumber
bool ReservationDatabase::exist( string reservationNumber )
{
	for (int i = 0; i < reservations.size(); i++) {
		if (reservations[i].getReservationNumber() == reservationNumber)
			return true;
	}
	return false;
}//hw

// returns true if there is a Reservation object containing specified reservationNumber and password
bool ReservationDatabase::legal( string reservationNumber, string password )
{
	for (int i = 0; i < reservations.size(); i++) {
		if (reservations[i].getReservationNumber() == reservationNumber)
			if (reservations[i].getPassword() == password)
				return true;
			else
				return false;
	}
	return false;

}//hw

// returns numCustomers in the Reservation object containing specified reservationNumber
int ReservationDatabase::getNumCustomers( string reservationNumber )
{
   vector< Reservation >::iterator it = getReservation( reservationNumber );
   return it->getNumCustomers();
}

// returns date in the Reservation object containing specified reservationNumber
Date ReservationDatabase::getDate( string reservationNumber )
{
   vector< Reservation >::iterator it = getReservation( reservationNumber );
   return it->getDate();
}

// returns time in the Reservation object containing specified reservationNumber
int ReservationDatabase::getTime( string reservationNumber )
{
   vector< Reservation >::iterator it = getReservation( reservationNumber );
   return it->getTime();
}

// cancels the Reservation object containing specified reservationNumber,
void ReservationDatabase::cancelReservation( string reservationNumber )
{
   vector< Reservation >::iterator it = getReservation( reservationNumber );
   reservations.erase( it );
}

// for the Reservation object containing specified reservationNumber,
// displays all the reservation informations
void ReservationDatabase::displayReservationInfo( string reservationNumber )
{
   cout << setfill( ' ' ) << setw( 11 ) << "Mobile No." << setw( 10 ) << "Name"
        << setw( 14 ) << "Date" << setw( 9 ) << "Time" << setw( 30 ) << "Email"
        << setw( 19 ) << "No of Customers" << setw( 12 ) << "Password"
        << setw( 19 ) << "Reservation No." << endl;

   vector< Reservation >::iterator it = getReservation( reservationNumber );
   it->displayReservationInfo();
}

// adds newReservation at the end of reservations
void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

// loads reservations from the file Reservations.dat
void ReservationDatabase::loadReservations()
{
	ifstream infile("Reservations.dat", ios::in | ios::binary);

	if (!infile)
	{
		cout << "Can't open reservation file!";
		system("pause");
		exit(0);
	}
	Reservation a;
	while (infile.read(reinterpret_cast<char*>(&a), sizeof(a)))
	{
		reservations.push_back(a);
	}
	infile.close();

}//hw

// stores reservations into the file Reservations.dat
void ReservationDatabase::storeReservations()
{
	ofstream outfile("Reservations.dat", ios::out | ios::binary);

	if (!outfile)
	{
		cout << "Can't open reservation file!";
		system("pause");
		exit(0);
	}
	int i = 0;
	while (i < reservations.size())
	{
		outfile.write(reinterpret_cast<char*>(&reservations[i]), sizeof(reservations[i]));
		i++;
	}
	outfile.close();

}//hw

// returns an iterator that points to the Reservation object containing specified reservationNumber
vector< Reservation >::iterator ReservationDatabase::getReservation( string reservationNumber )
{
	for (int i = 0; i < reservations.size(); i++) {
		if (reservations[i].getReservationNumber() == reservationNumber)
			return &reservations[i];
	}

}//hw