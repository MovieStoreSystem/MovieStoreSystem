#include <iostream>
#include<string>
using namespace std;

//structs and variables
struct accountinfo
{
	string username;
	string email;
	string password;
	int movieNumber;
	int accountNumber;
};

struct user
{
	accountinfo userAccount;
	int age;
	string phoneNumber;
	string rentedMovies[10];
	bool frozen = false;
	bool isEmployee = false;
};

//functions
char menu();
bool findemail(string email, user users[], int& totalusers);
bool findphonenumber(string phonenum, user users[], int& totalusers);
bool findaccountnum(int accountnum, user users[], int& totalusers);
bool findtrueinfo(string email, string password, user users[], int& totalusers);
int signin(user users[], int totalusers);
bool signup(user& temp, user users[], int& totalusers);


int main() {
	int total_users = 0, logged_in_index = -1;
	char ch = 'y', choice;
	user users[20];
	cout << "1.Sign up \n2.Sign in\n";
	cin >> choice;
	switch (choice)
	{
	case'1':
		signup(users[total_users], users, total_users);
		logged_in_index = total_users;
		total_users++;
		break;
	case'2':
		logged_in_index = signin(users, total_users);
		if (logged_in_index == -1)
			return 0;
		break;
	default:
		cout << "invalid choice";
		break;
	}
	do {

		if (users[logged_in_index].isEmployee)
		{
			//show the employee window
			/*switch ()
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
			}*/
		}
		else
		{
			// show the customer window
			/*switch ()
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
			}*/
		}


		cout << "Do you want to continue(y/n)\n";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');

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
		if (email == users[i].userAccount.email) {
			return true;
		}
	}
	return false;
}

bool findphonenumber(string phonenum, user users[], int& totalusers) {
	{
		for (int i = 0; i < totalusers; i++) {
			if (phonenum == users[i].phoneNumber) {
				return true;
			}
		}
		return false;
	}
}

bool findaccountnum(int accountnum, user users[], int& totalusers) {
	{
		for (int i = 0; i < totalusers; i++) {
			if (accountnum == users[i].userAccount.accountNumber) {
				return true;
			}
		}
		return false;
	}
}

bool findtrueinfo(string email, string password, user users[], int& totalusers) {
	for (int i = 0;i < totalusers;i++) {
		if (email == users[i].userAccount.email && password == users[i].userAccount.password)
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
	getline(cin, temp.userAccount.username);

	cout << "Enter your age:\n";
	cin >> temp.age;

	if (temp.age < 16) {
		cout << "Invalid age:)\n";
		return false;
	}

	cout << "Enter your phone number:\n";
	cin >> temp.phoneNumber;
	if (findphonenumber(temp.phoneNumber, users, totalusers)) {
		cout << "phone number already used" << endl;
		return false;
	}

	cout << "Enter your email:\n";
	cin >> temp.userAccount.email;

	if (findemail(temp.userAccount.email, users, totalusers)) {
		cout << "This email already exists!\n";
		return false; 
	}

	cout << "Enter your password:\n";
	cin >> temp.userAccount.password;

	temp.userAccount.accountNumber = (rand() % 100) + 5;
	while (findaccountnum(temp.userAccount.accountNumber, users, totalusers)) {
		temp.userAccount.accountNumber = (rand() % 100) + 5;
	}
	return true; 
}

int signin(user users[], int totalusers) {
	string email, password;
	cout << "Enter your email: ";
	cin >> email;
	cout << "Enter your password: ";
	cin >> password;

	for (int i = 0; i < totalusers; i++) {
		if (users[i].userAccount.email == email && users[i].userAccount.password == password) {
			cout << "Logged in successfully.\n";
			return i; 
		}
	}
	cout << "This account doesn't exist.\n";
	return -1; 
}