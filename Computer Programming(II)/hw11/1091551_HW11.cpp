#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include"MakeReservation.h"
#include"ReservationInquiry.h"
#include"AvailTableDatabase.h"
#include"ReservationDatabase.h"
using namespace::std;
int inputAnInteger(int begin, int end);

int main()
{
    ReservationDatabase reservationdatabase;
    MakeReservation makereservation;
    ReservationInquiry reservationinquiry;
    AvailTableDatabase availtabledatabase;
    AvailTable availtable;

    cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n";

    vector< Reservation > reservations; // vector of all reservations
    vector< AvailTable > availTables;    // Vector of available seats

    reservationdatabase.loadReservations(reservations);
    availtable.initializeAvailSeats(availTables);

    int choice;
    while (true)
    {
        cout << "\n1 - Book a Table\n"
            << "2 - My Bookings\n"
            << "3 - End\n"
            << "\nEnter Your Choice(1~3): ";

        do cout << "";
        while ((choice = inputAnInteger(1, 3)) == -1);

        switch (choice)
        {
        case 1:
            makereservation.domakeReservation(reservations, availTables);
            break;
        case 2:
            reservationinquiry.doviewReservation(reservations, availTables);
            break;
        case 3:
            reservationdatabase.storeReservations(reservations);
            availtabledatabase.storeAvailSeats(availTables);
            system("pause");
            return 0;
        default:
            cerr << "Incorrect Choice!\n";
            break;
        }
    }

    system("pause");

}

int inputAnInteger(int begin, int end)
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
}