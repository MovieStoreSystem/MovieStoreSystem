#include <iostream>
using namespace std;
char menu();


int main() {
	switch (menu())
	{
	case' 1':
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