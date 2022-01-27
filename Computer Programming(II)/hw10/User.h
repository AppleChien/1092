#pragma once
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;
struct Account
{
	char accountNumber[40];
	char PIN[20];
	unsigned int avalablebalance;
	unsigned int totalbalance;
};

class User {
public:
	User();
	bool login();
	int mainMenu();
	bool readAccount(string, string);
	bool saveAccount();
	void setAccount(int, int);
	Account getAccount() { return account; };
protected:
	int count;
	Account account;
};

User::User() :count(0), account({ "","",0,0 }) {

}

bool User::login() {
	string accountNumber, PIN;
	cout << "Welcome!\n\nPlease enter your account number:";
	cin >> accountNumber;
	cout << "\nEnter your PIN:";
	cin >> PIN;
	return readAccount(accountNumber, PIN);
}

int User::mainMenu() {
	int choice;
	cout << "\nMain menu:\n1 - View my balance\n2 - Withdraw cash\n3 - Deposit funds\n4 - Exit\n\nEnter a choice:";
	cin >> choice;
	return choice;
}

bool User::readAccount(string _accountNumber, string _PIN) {
	fstream file("account.txt", ios::in | ios::out);
	if (!file) {
		fstream file("account.txt", ios::out);
		Account user1 = { "12345","54321",1000,1200 }, user2 = { "98765","56789",200,200 };
		file.write(reinterpret_cast<char*>(&user1), sizeof(Account));
		file.write(reinterpret_cast<char*>(&user2), sizeof(Account));
		cout << "\nCannot open account.txt.Please try again.\n\n";
		return false;
	}
	while (file.read(reinterpret_cast<char*>(&account), sizeof(Account)))
	{
		if (strcmp(account.accountNumber, _accountNumber.c_str()) == 0 && strcmp(account.PIN, _PIN.c_str()) == 0)
			return true;
		++count;
	}
	return false;
}

bool User::saveAccount() {
	fstream file("account.txt", ios::in | ios::out);
	if (!file) {
		fstream file("account.txt", ios::out);
		cout << "\nCannot open account.txt.Please try again.\n\n";
		return false;
	}
	file.seekp(sizeof(Account)*count);
	file.write(reinterpret_cast<char*>(&account), sizeof(Account));
}

void User::setAccount(int _avalablebalance, int _totalbalance) {
	account.avalablebalance = _avalablebalance;
	account.totalbalance = _totalbalance;
}