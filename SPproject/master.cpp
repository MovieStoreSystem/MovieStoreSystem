#include <iostream>
using namespace std;

//structs and variables
struct accountinfo
{
	string username;
	string email;
	char password[20];
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
};

//functions
char menu();
bool findemail(string email, user users[], int totalUsers);
bool signup(user& temp, user users[], int totalUsers);


int main() {
	int totalusers = 0;
	user users[20];
	switch (menu())
	{
	case' 1':
		//
		break;

	case '2':
		signup(users[totalusers], users, totalusers);
		totalusers++;
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

bool findemail(string email, user users[], int totalUsers)
{
	for (int i = 0; i < totalUsers; i++) {
		if (email == users[i].useraccount.email) {
			return true;
		}
	}
	return false;
}

bool signup(user& temp, user users[], int totalUsers)
{
	cout << "Enter your username:\n";
	cin >> temp.useraccount.username;

	cout << "Enter your age:\n";
	cin >> temp.age;

	if (temp.age < 16) {
		cout << "Invalid age:)\n";
		return false;
	}

	cout << "Enter your phone number:\n";
	cin >> temp.phonenumber;

	cout << "Enter your email:\n";
	cin >> temp.useraccount.email;

	if (findemail(temp.useraccount.email, users, totalUsers)) {
		cout << "This email already exists!\n";
		return false; // ✅ Sign-up failed
	}

	cout << "Enter your password:\n";
	cin >> temp.useraccount.password;

	return true; // ✅ Sign-up succeeded
}