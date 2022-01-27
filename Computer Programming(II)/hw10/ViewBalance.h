#include "User.h"
class ViewBalance {
public:
	void doViewBalance(User&);
};

void ViewBalance::doViewBalance(User& user) {
	cout << "\nBalance Information:\n - Available balance: $";
	cout << user.getAccount().avalablebalance;
	cout << ".00\n - Total balance:     $";
	cout << user.getAccount().totalbalance;
	cout << ".00\n";
};