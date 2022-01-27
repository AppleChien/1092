#include "User.h"
class Withdraw {
public:
	void doWithdraw(User&);
	Withdraw() :bills(500) {};
private:
	int bills;
};

void Withdraw::doWithdraw(User& user) {
	int chioce = 0, money[5] = { 20,40,60,100,200 };
	while (cout << "\nWithdrawal options:\n1 - $20\n2 - $40\n3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\nChoose a withdrawal option (1-6): ") {
		cin >> chioce;
		if (chioce - 1 > 6)
			cout << "\nWrong input!Please try again.\n";
		else if (chioce - 1 == 6)
			return;
		else if (money[chioce - 1] > user.getAccount().avalablebalance)
			cout << "\nYou only have" << user.getAccount().avalablebalance << " to withdraw.Please choose a smaller amount.";
		else if (money[chioce - 1] > bills * 20)
			cout << "\nSorry,there is only $" << bills * 20 << "to be withdraw.Please choose a smaller amount.";
		else
			break;
	}
	bills -= money[chioce - 1] / 20;
	int temp1 = user.getAccount().avalablebalance - money[chioce - 1];
	int temp2 = user.getAccount().totalbalance - money[chioce - 1];
	user.setAccount(temp1, temp2);
	cout << "\nPlease take your cash from the cash dispenser.\n";
}