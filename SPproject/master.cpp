#include <iostream>
#include<string>
using namespace std;

//structs and variables
struct accountinfo
{
	string username;
	string email;
	string password;
	int movienumber;
	int accountnumber;
};

struct user
{
	accountinfo useraccount;
	int age;
	string phonenumber;
	string rentedmovies[10];
	bool frozen = false;
	bool isEmployee = false;
};

//functions
char menu();
bool findemail(string email, user users[], int& totalusers);
bool findphonenumber(string phonenum, user users[], int& totalusers);
bool findaccountnum(int accountnum, user users[], int& totalusers);
bool findtrueinfo(string email, string password, user users[], int& totalusers);
bool signin(user& temp, user users[], int& totalusers);
bool signup(user& temp, user users[], int& totalusers);


int main() {
	int totalusers = 0;
	char ch = 'y', choice;
	user users[20];
	cout << "1.Sign up \n2.Sign in\n";
	cin >> choice;
	switch (choice)
	{
	case'1':
		signup(users[totalusers], users, totalusers);
		totalusers++;
		break;
	case'2':
		signin(users[totalusers], users, totalusers);
		break;
	default:
		cout << "invalid choice";
		break;
	}
	do {

		switch (menu())
		{
		case'1':
			//
			break;

		case '2':
			//
			break;

		case '3':
			//
			break;

		case '4':
			//
			break;

		case '5':
			//
			break;

		default:
			cout << "Sorry, Invalid choice!";
			break;
		}
		cout << "Do you want to continue(y/n)\n";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	return 0;
}

//menu of the system!
char menu()
{
	char choice;
	cout << "\t\tWelcome to our Movie Store\n";
	cout << "1.View Movies\n";
	cout << "2.Rent a Movie\n";
	cout << "3.Return a Movie\n";
	cout << "4.Rental History\n";
	cout << "5.Exit\n";
	cout << "Please enter your choice number: ";
	cin >> choice;
	return choice;
}

bool findemail(string email, user users[], int& totalusers)
{
	for (int i = 0; i < totalusers; i++) {
		if (email == users[i].useraccount.email) {
			return true;
		}
	}
	return false;
}

bool findphonenumber(string phonenum, user users[], int& totalusers) {
	{
		for (int i = 0; i < totalusers; i++) {
			if (phonenum == users[i].phonenumber) {
				return true;
			}
		}
		return false;
	}
}

bool findaccountnum(int accountnum, user users[], int& totalusers) {
	{
		for (int i = 0; i < totalusers; i++) {
			if (accountnum == users[i].useraccount.accountnumber) {
				return true;
			}
		}
		return false;
	}
}

bool findtrueinfo(string email, string password, user users[], int& totalusers) {
	for (int i = 0;i < totalusers;i++) {
		if (email == users[i].useraccount.email && password == users[i].useraccount.password)
			return true;
	}
	return false;
}


bool signup(user& temp, user users[], int& totalusers)
{
	char role;
	cout << "Are you an Employee (E) or a Customer (C)? ";
	cin >> role;

	if (role == 'E' || role == 'e') {
		temp.isEmployee = true;
	}
	else {
		temp.isEmployee = false;
	}

	cout << "Enter your username:\n";
	cin.ignore();
	getline(cin, temp.useraccount.username);

	cout << "Enter your age:\n";
	cin >> temp.age;

	if (temp.age < 16) {
		cout << "Invalid age:)\n";
		return false;
	}

	cout << "Enter your phone number:\n";
	cin >> temp.phonenumber;
	if (findphonenumber(temp.phonenumber, users, totalusers)) {
		cout << "phone number already used" << endl;
		return false;
	}

	cout << "Enter your email:\n";
	cin >> temp.useraccount.email;

	if (findemail(temp.useraccount.email, users, totalusers)) {
		cout << "This email already exists!\n";
		return false; // ✅ Sign-up failed
	}

	cout << "Enter your password:\n";
	cin >> temp.useraccount.password;

	temp.useraccount.accountnumber = (rand() % 100) + 5;
	while (findaccountnum(temp.useraccount.accountnumber, users, totalusers)) {
		temp.useraccount.accountnumber = (rand() % 100) + 5;
	}
	return true;  // ✅ Sign-up succeeded
}

bool signin(user& temp, user users[], int& totalusers) {
	cout << "Enter your email" << endl;
	cin >> temp.useraccount.email;
	cout << "Enter your password" << endl;
	cin >> temp.useraccount.password;
	if (findtrueinfo(temp.useraccount.email, temp.useraccount.password, users, totalusers)) {
		cout << "loged in successfully\n";
		return true;
	}
	else {
		cout << "this account doesn't exist\n";
		return false;
	}
}