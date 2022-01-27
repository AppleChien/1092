#pragma once
#ifndef AvailTableDatabase_H
#define AvailTableDatabase_H
#include<fstream>
#include<vector>
#include"AvailTable.h"
class AvailTableDatabase {
public:
	void loadAvailSeats(vector< AvailTable >& availSeats)
	{
		ifstream inAvailTable("AvailTables.dat", ios::binary);
		if (!inAvailTable)
		{
			cout << "Reservations can not open";
			system("pause");
		}
		AvailTable i;
		inAvailTable.seekg(0);
		while (!inAvailTable.eof())
		{
			inAvailTable.read(reinterpret_cast<char*>(&i), sizeof(i));
			if (i.date.year == 2000)
				continue;

			availSeats.push_back(i);
		}
		inAvailTable.close();
	}

	void storeAvailSeats(vector< AvailTable >& availSeats)
	{
		ofstream outstoreAvailTable("AvailTables.dat", ios::binary);

		if (!outstoreAvailTable)
			cout << "No";

		if (availSeats.size() != 0)
			for (int i = 0; i <= availSeats.size() - 1; i++) {
				outstoreAvailTable.write(reinterpret_cast<const char*>(&availSeats[i]), sizeof(availSeats[i]));
			}
		outstoreAvailTable.close();
	}

};
#endif
