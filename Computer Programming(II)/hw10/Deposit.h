#include "User.h"
class Deposit {
public:
	void doDeposit(User&);
};

void Deposit::doDeposit(User& user) {
	double money;
	cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";
	cin >> money;
	if (money == 0)
		return;
	else {
		cout << "\nPlease insert a deposit envelope containing $"<< money/100.00 <<"in the deposit slot.\n";
		cout << "\nYour envelope has been received.\nNOTE: The money deposited will not be available until we\nverify the amount of any enclosed cash, and any enclosed checks clear.\n";
		int temp = user.getAccount().totalbalance + money/100.00;
		user.setAccount(user.getAccount().avalablebalance, temp);
	}
}