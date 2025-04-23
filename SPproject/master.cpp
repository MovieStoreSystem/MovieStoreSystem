#include <iostream>
#include<string>
using namespace std;

//structs and variables
const int number_of_movies = 20;
struct accountinfo
{
	string username;
	string email;
	string password;
	int movieNumber = 0;
	int accountNumber = 0;
};

struct user
{
	accountinfo userAccount;
	int age = 0;
	string phoneNumber;
	string rentedMovies[10];
	bool frozen = false;
	bool isEmployee = false;
};

struct movieinfo {
	string name_of_movie;
	float price = 0;
	int rentingCount = 0;
	float average_rate = 0;
	int final_score_of_movie = 0;
	int total_ratings = 0;
}movie[number_of_movies];

//functions
char customermenu();
char employeermenu();
bool findemail(string email, user users[], int& totalusers);
bool findphonenumber(string phonenum, user users[], int& totalusers);
bool findaccountnum(int accountnum, user users[], int& totalusers);
bool findtrueinfo(string email, string password, user users[], int& totalusers);
int signin(user users[], int totalusers);
bool signup(user& temp, user users[], int& totalusers);
void movierate(movieinfo movies[]);


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
			switch (employeermenu())
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
			case '6':
				//
				break;
			case '7':
				//
				break;

			case '8':
				cout << "Exiting :)\n";
				break;
			default:
				cout << "Sorry, Invalid choice!";
				break;
			}
		}
		else
		{
			switch (customermenu())
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

			case '6':
				movierate(movie);
				break;

			case '7':
				//
				break;

			case '8':
				cout << "Exiting :)\n";
				break;

			default:
				cout << "Sorry, Invalid choice!";
				break;
			}
		}


		cout << "Do you want to continue(y/n)\n";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');

}

//menu of the system!
char customermenu()
{
	char choice;
	cout << "\t\tWelcome to our Movie Store\n";
	cout << "1.View Movies\n";
	cout << "2.Rent a Movie\n";
	cout << "3.Return a Movie\n";
	cout << "4.Rental History\n";
	cout << "5. View Account Information\n";
	cout << "6. Rate a Movie / Leave a Review\n";
	cout << "7.View Currently Rented Movies\n";
	cout << "8.Exit\n";
	cout << "Please enter your choice number: ";
	cin >> choice;
	return choice;
}

char employeermenu()
{
	char choice;
	cout << "\t\tWelcome to our Movie Store\n";
	cout << "1.Add a Movie\n";
	cout << "2.Remove a Movie\n";
	cout << "3.List all Movies\n";
	cout << "4.List Customers\n";
	cout << "5.Rental History\n";
	cout << "6. Freeze/Unfreeze Customer Account\n";
	cout << "7. Edit Movie Information\n";
	cout << "8.Exit\n";
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

	//checking if they are true!
	for (int i = 0; i < totalusers; i++) {
		if (users[i].userAccount.email == email && users[i].userAccount.password == password) {
			cout << "Logged in successfully.\n";
			return i;
		}
	}
	cout << "This account doesn't exist.\n";
	return -1;
}

void movierate(movieinfo movie[]) {
	string title;
	int temp_rate;
	cout << "Enter the title of the movie\n";
	cin.ignore();
	getline(cin, title);

	for (int i = 0;i < number_of_movies;i++)
	{
		if (movie[i].name_of_movie == title)
		{
			cout << "Please enter a rating from 1 to 5\n";
			cin >> temp_rate;

			if (temp_rate < 1 || temp_rate>5) {
				cout << "Sorry, Invalid rating. Should be from 1 to 5 \n";
				return;
			}
			movie[i].total_ratings++;
			movie[i].final_score_of_movie += temp_rate;
			movie[i].average_rate = (float)movie[i].final_score_of_movie / movie[i].total_ratings;
			cout << "The new rating is " << movie[i].average_rate << endl;
			return;
		}
	}
	cout << "Movie title not found \n";
	return;
}