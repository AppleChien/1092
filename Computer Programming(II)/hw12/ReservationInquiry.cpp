#include <iostream>
using namespace::std;

#include "ReservationInquiry.h"

extern int inputAnInteger( int begin, int end );

ReservationInquiry::ReservationInquiry( ReservationDatabase &theReservationDatabase,
                                        AvailTableDatabase &theAvailTableDatabase )
   : reservationDatabase( theReservationDatabase ),
     availTableDatabase( theAvailTableDatabase )
{
}

// reservation inquiry
void ReservationInquiry::execute()
{
   if( reservationDatabase.empty() )
   {
      cout << "\nNo reservations!\n";
      return;
   }
   else {
	   string reservationNo, password;
	   int n = 0;
	   cout << "Enter reservation number: ";
	   cin >> reservationNo;
	   
	   if (!reservationDatabase.exist(reservationNo)) {
		   cout << "\nNo reservations with this reservation number!\n" << endl;
		   return;
	   }
	   cout << "\nEnter reservation password: ";
	   cin >> password;
	   
	   if (!reservationDatabase.legal(reservationNo, password)) {
		   cout << "\nWrong password!\n" << endl;
		   return;
	   }
	   reservationDatabase.displayReservationInfo(reservationNo);
	   cout << "\n\nCancel this reservation? ( y/n ) ";
	   char ans;
	   cin >> ans;
	   if (ans == 'y') {
		   int t, num;
		   Date d;
		   d = reservationDatabase.getDate(reservationNo);
		   num = reservationDatabase.getNumCustomers(reservationNo);
		   t = reservationDatabase.getTime(reservationNo);
		   availTableDatabase.increaseAvailTables(num,d,t);
		   reservationDatabase.cancelReservation(reservationNo);
	   }

	   cout << "\nThis reservation has been cancelled.\n";
	   cin.ignore();
	   return;
   }
}//hw