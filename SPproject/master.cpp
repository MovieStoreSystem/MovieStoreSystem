#include "master.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int main() {

	int total_users = 0;
	char ch = 'y', choice;
	user users[20];

	cout << "1.Sign up \n2.Sign in\n";
	cin >> choice;
	switch (choice)
	{
	case '1':
		signup(users[total_users], users, total_users);
		logged_in_index = total_users;
		total_users++;
		break;
	case '2':
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
			case '1':
				moviemanagment();
				break;

			case '2':
				//
				break;

			case '3':
				displayMovies();
				break;

			case '4':
				displayCustomers();
				ListofDaysLeft();
				break;

			case '5':
				sortMoviesByCount();
				break;
			case '6':
				Overdue_clients();
				break;
			case '7':
				//
				break;

			case '8':
				cout << "Exiting :)\n";
				ch = 'n';
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
			case '1':
				displayMovies();
				sortMoviesByCount();
				break;

			case '2':
				Renting();
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
				ch = 'n';
				break;

			default:
				cout << "Sorry, Invalid choice!";
				break;
			}
		}


		if (ch != 'n') {
			cout << "Do you want to continue(y/n)\n";
			cin >> ch;
		}
	} while (ch == 'y' || ch == 'Y');

	/*
	for (int i{ 0 }; i < total_users; i++)
	{
		loadFromFile(users, total_users, i);
	}*/

	outputToFile(users, total_users);

}

//menu of the system!
char customermenu()
{
	char choice;
	cout << "\t\tWelcome to our Movie Store\n";
	cout << "1.View Movies\n";
	cout << "2.Rent a Movie\n";
	cout << "3.Return a Movie\n";  //Missing
	cout << "4.Rental History\n";  //Missing
	cout << "5.View Account Information\n";  //Missing
	cout << "6.Rate a Movie / Leave a Review\n";  
	cout << "7.View Currently Rented Movies\n";  //Missing
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
	cout << "2.Remove a Movie\n"; // Missing
	cout << "3.List all Movies\n";
	cout << "4.List Customers\n";
	cout << "5.Most rented movies\n";
	cout << "6.Show Freezed Customers\n";
	cout << "7.Edit Movie Information\n";  //Missing
	cout << "8.Exit\n";
	cout << "Please enter your choice number: ";
	cin >> choice;
	return choice;
}

// Functions for checking the true identity
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
			if (phonenum == users[i].userAccount.phoneNumber) {
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

// Signing
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
	cin >> temp.userAccount.phoneNumber;
	if (findphonenumber(temp.userAccount.phoneNumber, users, totalusers)) {
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

// Rating Movies
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

void outputToFile(user users[], int totalUsers)
{
	ofstream outFile("savedData.txt", ios::app);
	while (outFile.is_open())
	{
		for (int i{ 0 }; i < totalUsers; i++)
		{
			outFile << users[i].userAccount.accountNumber << '|'
				<< users[i].userAccount.username << '|'; //output user ID & username to file
			for (int j{ 0 }; i < users[i].userAccount.movieNumber; j++) //output rented movies to file 
			{
				outFile << users[i].rentedMovies[j] << '|';
			}
			outFile << boolalpha << users[i].frozen << '|'; //output frozen status to file
		}
		outFile.close();
	}

}

/*
void loadFromFile(user users[], int totalUsers, int userIndex)
{
	string line{}, id{}, username{}, frozen{};
	ifstream myFile("savedData.txt");
	while (getline(myFile, line))
	{
		stringstream ssLine(line);
		getline(ssLine, id, '|');
		getline(ssLine, users[userIndex].userAccount.username, '|');
		getline(ssLine, frozen, '|');

		users[userIndex].userAccount.accountNumber = stoi(id);
		users[userIndex].frozen = (frozen == "true") ? true : false;
        
	}
}*/

//function Is the year leap or not?
bool isLeap(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// دالة بتحوّل التاريخ لعدد الأيام 
int dateToDays(Date d) {
	int days = d.year * 365 + d.day;

	// نضيف الأيام بتاعت الشهور اللي فاتت في نفس السنة
	for (int i = 0; i < d.month - 1; ++i) {
		days += daysInMonth[i];
	}

	// لو السنة كبيسة و الشهر بعد فبراير، نضيف يوم
	if (d.month > 2 && isLeap(d.year))
		days += 1;

	// نضيف عدد السنوات الكبيسة اللي فاتت
	days += (d.year / 4) - (d.year / 100) + (d.year / 400);

	return days;
}

// نحسب الفرق بين تاريخين
int daysBetween(Date rentday, Date currentday) {
	return abs(dateToDays(currentday) - dateToDays(rentday));
}

//function list of overdue clients
void Overdue_clients() {
	for (int i = 0, j = 0; i < 20; i++) {
		int Number_of_days = 0;
		Number_of_days = daysBetween(users[i].rentday, currentday);
		if (Number_of_days > duedate) {
			users[i].frozen = true;
			Overdue[j] = users[i];
			cout << users[i].userAccount.accountNumber << "." << users[i].userAccount.username << "\n";
			j++;
		}
	};
}

void ListofDaysLeft() {
	for (int i = 0;i < 20;i++) {
		int Number_of_days = 0;
		Number_of_days = daysBetween(users[i].rentday, currentday);
		cout << "Number of days: " << Number_of_days << endl;
	}
}

//if user want to rent movie (renting function)
void Renting() {
	int num;
	cout << "\t\tPLEASE CHOOSE MOVIE THAT YOU WANT TO RENT";
	for (int i = 0; i < number_of_movies; i++) {
		cout << i + 1 << ". " << movie[i].name_of_movie;
	}
	cout << "Enter a number of movie you want: ";
	cin >> num;
	if (num < 1 || num>number_of_movies) {
		cout << "Invalid number!!!\n";
	}
	else {
		for (int i = 0; i < number_of_movies; i++) {
			if (num - 1 == i) {
				if (movie[i].Quantity == 0)
					cout << "Sorry,This movie is not available now ...\n";
				else {
					movie[i].Quantity - 1;
					movie[i].rentingCount++;
					Rentday(i);
					cout << "\t\trented successfully\n";
				}
			}
		}
	}
	// int num
}

void sortMoviesByCount() {
	// ترتيب بالأكبر count
	for (int i = 0; i < number_of_movies - 1; i++) {
		for (int j = i + 1; j < number_of_movies; j++) {
			if (movie[i].rentingCount < movie[j].rentingCount) {
				// تبادل العناصر
				swap(movie[i], movie[j]);
			}
		}
	}
	for (int i = 0; i < number_of_movies; i++) {
		cout << movie[i].name_of_movie << " - Rentals: " << movie[i].rentingCount << endl;
	}
}

// Displaying information
void displayCustomers() {
	for (int i = 0; i < 20; i++)
	{
		cout << users[i].userAccount.accountNumber << '\t';
		cout << users[i].userAccount.username << '\n';
	}
}

void displayMovies() {
	for (int i = 0; i < totalnumofmovies; i++)
	{
		cout << movie[i].name_of_movie;
		cout << endl;
	}
}

//Menna
void addingMovies(int count)
{
	for (int i = 0;i < count;i++) {
		cout << "Enter the movie name:\n";
		cin >> movie[totalnumofmovies].name_of_movie;
		cout << "Enter the price of the movie for a day:\n";
		cin >> movie[totalnumofmovies].price;
		cout << "Enter the overdue price of the movie:\n";
		cin >> movie[totalnumofmovies].overdue_price;
		cout << "Enter the count of the movie" << '\n';
		cin >> movie[totalnumofmovies].Quantity;
		totalnumofmovies++;
	}
}

void moviemanagment()
{
	int count;
	cout << "Enter the count of movies you want to input\n";
	cin >> count;
	addingMovies(count);
}

double rental_fees(int total_days, float price_of_day, int overdue_days, int overdue_value)
{
	double fees = total_days * price_of_day;
	if (overdue_value > 0)
	{
		fees = fees + (overdue_days * overdue_value);
		return fees;
	}
	else
		return fees;
}

void returnfees() {
	Date Rent_Day = { 1, 1, 2024 };
	Date Due_Day = { 23, 4, 2025 };
	Date Return_Date = { 23,5,2025 };
	int overdue_days;
	int Total_Days;
	int price_day, overdue_value;

	int movienum;
	cout << "\t\t List of Movies\n";
	for (int i = 0; i < totalnumofmovies; i++)
	{
		cout << i + 1 << "." << movie[i].name_of_movie;
		cout << endl;
	}
	cin >> movienum;
	movienum--;
	int days_of_return_date = dateToDays(Return_Date);
	int days_of_current_day = dateToDays(Due_Day);
	if (days_of_return_date <= days_of_current_day)
	{
		Total_Days = daysBetween(Rent_Day, Due_Day);
		overdue_days = 0;
	}
	else
	{
		Total_Days = daysBetween(Rent_Day, Due_Day);
		overdue_days = daysBetween(Return_Date, Due_Day);
	}

	double Total_fees = rental_fees(Total_Days, movie[movienum].price, overdue_days, movie[movienum].overdue_price);
	cout << "Total fees are: " << Total_fees;
}

void Rentday(int index) {
	cout << "Enter the day of renting\n";
	cin >> users[logged_in_index].usersmovie[index].rentday.day;
	cout << "Enter the month of renting\n";
	cin >> users[logged_in_index].usersmovie[index].rentday.month;
	cout << "Enter the year of renting\n";
	cin >> users[logged_in_index].usersmovie[index].rentday.year;
}
void Currentday(int index) {
	cout << "Enter the current day\n";
	cin >> users[logged_in_index].usersmovie[index].currentday.day;
	cout << "Enter the current month\n";
	cin >> users[logged_in_index].usersmovie[index].currentday.month;
	cout << "Enter the current year\n";
	cin >> users[logged_in_index].usersmovie[index].currentday.year;
}