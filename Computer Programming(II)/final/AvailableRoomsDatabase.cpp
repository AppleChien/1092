// AvailableRoomsDatabase.cpp
// Member-function definitions for class AvailableRoomsDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "AvailableRoomsDatabase.h" // AvailableRoomsDatabase class definition

extern Date computeCurrentDate();

extern bool leapYear(int year);

extern const int totalNumRooms[6]; // total number of rooms for each room type

AvailableRoomsDatabase::AvailableRoomsDatabase()
{
	loadAvailableRooms();

	Date currentDate = computeCurrentDate();
	if (numAvailableDays == 0)
		initilizeAvailableRooms(currentDate, 0, 6);
	else
		if (availableRooms[numAvailableDays - 1].getDate() < currentDate)
			initilizeAvailableRooms(currentDate, 0, 6);
		else if (availableRooms[0].getDate() < currentDate)
			adjustAvailableRooms(currentDate);
	// It cannot happen that availableRooms[ 0 ].getDate() > currentDate
}

AvailableRoomsDatabase::~AvailableRoomsDatabase()
{
	saveAvailableRooms();
}

void AvailableRoomsDatabase::initilizeAvailableRooms(const Date& firstDate, int first, int numMonths)
{
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (leapYear(firstDate.getYear()))
		days[2] = 29;
	
	Date currentDate = firstDate;
	int i = first;
	int month = firstDate.getMonth(), year = firstDate.getYear(), day = firstDate.getDay();
	for (int j = 1; j < numMonths; j++) {
		for (int i=day; i <= days[month]; i++) {
			availableRooms[first].initilizeAvailableRooms(year, month, day);
			day = day + 1;
			first++;
			if (currentDate.getDay() == days[currentDate.getMonth()]) {
				break;
			}	
		}
		day = 1;                                   
		month++;
		if (month > 12)
		{
			month = 1;
			year++;
			if (leapYear(year))
				days[2] = 29;
			else
				days[2] = 28;
		}                                         
	}
	numAvailableDays = first + 1;                    
}

// remove outdated data from availableRooms, and
// add new data into availableRooms if necessary
void AvailableRoomsDatabase::adjustAvailableRooms(const Date& currentDate)
{
	Date first = availableRooms[0].getDate();
	Date last = availableRooms[numAvailableDays - 1].getDate();
	Date d = currentDate;
	int diff = d - availableRooms[0].getDate();
	int i = 0;
	for (int i = 0; i < numAvailableDays - diff; i++) {
		availableRooms[i] = availableRooms[i + diff];
	}

	//currentDate = last + diff; //delete 
	int a = availableRooms[i - 1].getDate().getDay();           
	int m = availableRooms[i - 1].getDate().getMonth();
	int y = availableRooms[i - 1].getDate().getYear();
	int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	if (leapYear(y))
		days[2] = 29;
	else
		days[2] = 28;
	a = a + 1;
	if (a > days[m]) {
		m++;
		a = 1;
		if (m > 12) {
			m = 1;
			y++;
			if (leapYear(y))
				days[2] = 29;
			else
				days[2] = 28;
		}
	}
	int c = 6 - abs(m - d.getMonth());                     
	

	for (int k = 0; k <= c; k++) {
		for (int j = a; j <= days[m]; j++) {
			availableRooms[i].initilizeAvailableRooms(y, m, a);
			a++;
			i++;
			diff--;
			if (diff == 0) 
				break;
		}
		a = 1;                                           
		m++;
		if (m > 12)
		{
			m = 1;
			y++;
			if (leapYear(y))
				days[2] = 29;
			else
				days[2] = 28;
		}                                              
	}
	numAvailableDays = i;    
}

void AvailableRoomsDatabase::displayAvailableRooms(Date checkInDate, Date checkOutDate)
{
	cout << "\nAvailable Rooms:\n\n";
	cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";

	// checkInDateIndex is the index of checkInDate in availableRooms
	// checkOutDateIndex is the index of checkOutDate in availableRooms
	int checkInDateIndex = getDateIndex(checkInDate, 0);
	int checkOutDateIndex = getDateIndex(checkOutDate, checkInDateIndex + 1);

	for (int i = checkInDateIndex; i < checkOutDateIndex; i++)
		cout << availableRooms[i].getDate().getYear() << "-"
		<< setw(2) << setfill('0') << availableRooms[i].getDate().getMonth() << "-"
		<< setw(2) << availableRooms[i].getDate().getDay()
		<< setw(16) << setfill(' ') << availableRooms[i].getAvailableRooms(1)
		<< setw(14) << availableRooms[i].getAvailableRooms(2)
		<< setw(19) << availableRooms[i].getAvailableRooms(3)
		<< setw(17) << availableRooms[i].getAvailableRooms(4)
		<< setw(15) << availableRooms[i].getAvailableRooms(5) << "\n";
}

int AvailableRoomsDatabase::findMinNumRooms(int roomType,
	const Date& checkInDate, const Date& checkOutDate)
{
	int minNumRooms = totalNumRooms[roomType];

	int checkInDateIndex = getDateIndex(checkInDate, 0);
	int checkOutDateIndex = getDateIndex(checkOutDate, checkInDateIndex + 1);

	for (int i = checkInDateIndex; i < checkOutDateIndex; i++)
		if (minNumRooms > availableRooms[i].getAvailableRooms(roomType))
			minNumRooms = availableRooms[i].getAvailableRooms(roomType);

	return minNumRooms;
}

void AvailableRoomsDatabase::decreaseAvailableRooms(int roomType, int numRooms,
	const Date& checkInDate, const Date& checkOutDate)
{
	int checkInDateIndex = getDateIndex(checkInDate, 0);
	int checkOutDateIndex = getDateIndex(checkOutDate, checkInDateIndex + 1);

	for (int i = checkInDateIndex; i < checkOutDateIndex; i++)
		availableRooms[i].decreaseAvailableRooms(roomType, numRooms);
}

void AvailableRoomsDatabase::loadAvailableRooms()
{
	ifstream inFile("Available Rooms.dat", ios::in | ios::binary);

	if (!inFile)
	{
		cout << "Available rooms.dat could not be opened!\n";
		system("pause");
		exit(1);
	}

	numAvailableDays = 0;
	while (inFile.read(reinterpret_cast<char*>(&availableRooms[numAvailableDays]), sizeof(AvailableRooms)))
		++numAvailableDays;

	inFile.close();
}

void AvailableRoomsDatabase::saveAvailableRooms()
{
	ofstream outFile("Available Rooms.dat", ios::out | ios::binary);

	if (!outFile)
	{
		cout << "Available rooms.dat could not be opened." << endl;
		system("pause");
		exit(1);
	}

	for (int i = 0; i < numAvailableDays; i++)
		outFile.write(reinterpret_cast<const char*> (&availableRooms[i]), sizeof(AvailableRooms));

	outFile.close();
}

// return the index i in [ dateIndex, numAvailableDays ) such that availableRooms[ i ].date == date
int AvailableRoomsDatabase::getDateIndex(const Date& date, int dateIndex)
{
	for (int i = dateIndex; i < numAvailableDays; i++)
		if (availableRooms[i].getDate() == date)
			return i;

	return -1;
}