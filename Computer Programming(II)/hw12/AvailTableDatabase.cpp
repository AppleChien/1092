#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailTableDatabase.h"

// tableTypes[ i ] is the table type for i customers
const int tableTypes[ 13 ] = { 0, 1, 1, 2, 2, 3, 4, 4, 0, 0, 5, 5, 5 };

extern Date computeCurrentDate();

// calls loadAvailTables(), removes outdated available table informations and
// adds new available table informations
AvailTableDatabase::AvailTableDatabase()
{
   loadAvailTables();
   Date currentday;
   int theNumAvailTables[6] = { 2,2,2,2,2,2 };
   currentday = computeCurrentDate();
   currentday = currentday + 1;
   if (availTables.size() == 0) {
	   AvailTable b;
	   availTables.push_back(b);
	   for (int i = 1; i <= 30; i++) {
		   AvailTable a(currentday, theNumAvailTables);
		   availTables.push_back(a);
		   currentday = currentday + 1;
	   }
   }
   else {
	   Date lastday = availTables[availTables.size() - 1].getDate();
	   Date firstday = availTables[1].getDate();

	   if (lastday < currentday) {
		   for (int i = 1; i <= 30; i++) {
			   AvailTable a(currentday, theNumAvailTables);
			   availTables[i] = a;
			   currentday = currentday + 1;
		   }
	   }
	   else if (firstday < currentday) {
		   int diff = currentday - firstday ;
		   for (int i = 1; i <= 30 - diff; i++)
			   availTables[i] = availTables[i + diff];
		   currentday = lastday + diff;
		   for (int i = 1; i <= diff; i++) {
			   availTables.pop_back();
		   }
		   for (int i = 1; i <= diff; i++) {
			   AvailTable a(currentday, theNumAvailTables);
			   availTables.push_back(a);
			   currentday = currentday + 1;
		   }
	   }
   }
}//hw

// call storeAvailTables
AvailTableDatabase::~AvailTableDatabase()
{
   storeAvailTables();
}

// increases the number of available tables by one on date and timeCode for corresponding table type
void AvailTableDatabase::increaseAvailTables( int numCustomers, Date date, int timeCode )
{
   int tableType = tableTypes[ numCustomers ];
   vector< AvailTable >::iterator it = getAvailTable( date );
   it->increaseAvailTables( timeCode, tableType );
}

// decreases the number of available tables by one on date and timeCode for corresponding table type
void AvailTableDatabase::decreaseAvailTables( int numCustomers, Date date, int timeCode )
{
   int tableType = tableTypes[ numCustomers ];
   vector< AvailTable >::iterator it = getAvailTable( date );
   it->decreaseAvailTables( timeCode, tableType );
}

// returns true if there are available tables on date for corresponding table type
bool AvailTableDatabase::availableTables( int numCustomers, Date date )
{
	vector< AvailTable >::iterator it = getAvailTable(date);
	int tableType = tableTypes[numCustomers];
	for (int i = 1; i <= 3; i++) {
		if (it->getNumAvailTables(i, tableType) > 0)
			return true;
	}
	return false;
}//hw

// returns true if there are available tables on date and timeCode for corresponding table type
bool AvailTableDatabase::availableTables( int numCustomers, Date date, int timeCode )
{
	vector< AvailTable >::iterator it = getAvailTable(date);
	int tableType = tableTypes[numCustomers];
	if (it->getNumAvailTables(timeCode, tableType) > 0)
		return true;
	else
		return false;
}//hw

void AvailTableDatabase::loadAvailTables()
{
	ifstream infile("AvailTables.dat", ios::in | ios::binary);

	if (!infile)
	{
		cout << "Can't open reservation file!";
		system("pause");
		exit(0);
	}
	AvailTable a;
	while (infile.read(reinterpret_cast<char*>(&a), sizeof(a)))
	{
		availTables.push_back(a);
	}
	infile.close();

}//hw

void AvailTableDatabase::storeAvailTables()
{
	ofstream outfile("AvailTables.dat", ios::out | ios::binary);

	if (!outfile)
	{
		cout << "Can't open reservation file!";
		system("pause");
		exit(0);
	}
	int i = 0;
	while (i < availTables.size())
	{
		outfile.write(reinterpret_cast<char*>(&availTables[i]), sizeof(availTables[i]));
		i++;
	}
	outfile.close();

}//hw

// returns an iterator that points to the AvailTable object containing specified date
vector< AvailTable >::iterator AvailTableDatabase::getAvailTable( Date date )
{
	for (int i = 0; i < availTables.size(); i++) {
		if (availTables[i].getDate() == date)
			return &availTables[i];
	}
}//hw