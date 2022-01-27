#include <iostream>
#include "User.h"
#include "ATM.h"
using namespace std;
int main() {
	ATM atm;
	User user;
	int chioce;
	while (true) {
		if (user.login()) {
			while (chioce = user.mainMenu()) {
				if (chioce == 1)
					atm.viewbalance.doViewBalance(user);
				else if (chioce == 2)
					atm.withdraw.doWithdraw(user);
				else if (chioce == 3)
					atm.deposit.doDeposit(user);
				else if (chioce == 4) {
					user.saveAccount();
					cout << "\nExiting the system...\n\nThank you! Goodbye!\n\n";
					break;
				}
				else
					cout << "\nWrong account or PIN. Please try again.\n";
			}
		}
	}
	return 0;
}