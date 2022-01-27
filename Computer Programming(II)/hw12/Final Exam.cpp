#include <iostream>
#include <ctime>
using namespace::std;

#include "MakeReservation.h"    // MakeReservation class definition
#include "ReservationInquiry.h" // ReservationInquiry class definition

int inputAnInteger( int begin, int end ); // input an integer in the range [ begin, end ]
Date computeCurrentDate(); // compute current date
bool leapYear( int year ); // if the year is a leap year, return true; otherwise, return false

int main()
{
    
   cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n";

   ReservationDatabase reservationDatabase; // reservation information database
   AvailTableDatabase availTableDatabase;   // available table information database
  
   MakeReservation makeReservation( reservationDatabase, availTableDatabase );
   ReservationInquiry reservationInquiry( reservationDatabase, availTableDatabase );

   bool userExited = false; // user has not chosen to exit
   int choice;

   // loop while user has not chosen option to exit system
   while( !userExited )
   {
      cout << "\n1 - Book a Table\n";
      cout << "2 - My Bookings\n";
      cout << "3 - End\n\n";

      do cout << "Enter your choice: (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );

      // decide how to proceed based on user's menu selection
      switch( choice )
      {
      case 1:
         makeReservation.execute(); // make reservation
         break;
      case 2:
         reservationInquiry.execute(); // reservation inquiry
         break;
      case 3: // user chose to exit
         userExited = true;
         cout << endl;
         break;
      default: // user did not enter an integer from 1-3
         cout << "\nIncorrect choice!" << endl;
      }
   }

   system( "pause" );
}

int inputAnInteger( int begin, int end )
{
    char code[100];
    int intcode;

    cin.getline(code, 100, '\n');

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

}//hw

Date computeCurrentDate()
{
    int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int remainingSeconds = static_cast<int>(time(0)) + 8 * 60 * 60;
    Date currentDate;
    int y = 1970;
    currentDate.setYear(y);

    int secondsPerYear = 365 * 24 * 60 * 60;
    if (leapYear(y))
        secondsPerYear += 24 * 60 * 60;

    while (remainingSeconds >= secondsPerYear)
    {
        remainingSeconds -= secondsPerYear;
        y++;
        currentDate.setYear(y);

        secondsPerYear = 365 * 24 * 60 * 60;
        if (leapYear(y))
            secondsPerYear += 24 * 60 * 60;
    }

    if (leapYear(currentDate.getYear()))
        days[2] = 29;

    int m = 1;
    currentDate.setMonth(m);
    while (remainingSeconds >= days[currentDate.getMonth()] * 24 * 60 * 60)
    {
        remainingSeconds -= days[currentDate.getMonth()] * 24 * 60 * 60;
        m++;
        currentDate.setMonth(m);
    }

    currentDate.setDay(remainingSeconds / (24 * 60 * 60) + 1);

    return currentDate;
}//hw

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}