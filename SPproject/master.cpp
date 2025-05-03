#include "master.h"
#include <cmath>
#include <cctype> 
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <iostream>
using namespace std;

int main() {

	int total_users{ getNumberOfUsersFromFile() };

	if (total_users != 0)
	{
		
	 loadFromFile(users);
		
	}
	
	char ch = 'y', choice;
	bool open = true;

		bool sign = true;
		while (sign) {

			choice = getValidatedIChar("1.Sign up \n2.Sign in\n");

			switch (choice)
			{
			case '1':
				signup(users[total_users], users, total_users);
				logged_in_index = total_users;
				total_users++;
				sign = false;
				break;
			case '2':
				logged_in_index = signin(users, total_users);
				if (logged_in_index == 50) {
					continue;
				}
				sign = false;
				break;
			default:
				cout << "Invalid Choice\n";
				break;

			}

		}
		cout << "\t\tWelcome to our Movie Store\n\n";
	while(open) {
		cout << "\t\tMENU\n";

		if (users[logged_in_index].isEmployee)
		{
			switch (employeermenu())
			{
			case '1':
				moviemanagment();
				break;

			case '2':
				displayMovies();
				break;

			case '3':
				displayCustomers(total_users);
				break;

			case '4':
				sortMoviesByCount();
				break;
			case '5':
				Overdue_clients();
				break;
			case '6':
				Renting();
				break;
			case '7':
				update(movie);
				break;

			case '8':
				cout << "Exiting :)\n";
				open = false;
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
				break;

			case '2':
				Renting();
				break;

			case '3':
				Calculate_totalPrice();
				break;

			case '4':
				ViewAccountInfo();
				break;

			case '5':
				movierate(movie);
				break;

			case '6':
				displayRentedMovies();
				break;

			case '7':
				cout << "Exiting :)\n";
				open = false;
				break;

			default:
				cout << "Sorry, Invalid choice!";
				break;
			}
		}
	
	}

	outputToFile(users, total_users);

}

//menu of the system!
char customermenu()
{
	char choice;
	cout << "1.View Movies\n";
	cout << "2.Rent a Movie\n";
	cout << "3.Return a Movie\n";  
	cout << "4.View Account Information\n";  
	cout << "5.Rate a Movie / Leave a Review\n";  
	cout << "6.View Currently Rented Movies\n";  
	cout << "7.Exit\n";
	cout << "Please enter your choice number: ";
	cin >> choice;
	return choice;
}
char employeermenu()
{
	char choice;
	cout << "1.Add a Movie\n";
	cout << "2.List all Movies\n";
	cout << "3.List all Customers\n";
	cout << "4.Most rented movies\n";
	cout << "5.Overdue Customers\n";
	cout << "6.Remove a Movie\n"; // Missing
	cout << "7.Edit Movie Information\n";  
	cout << "8.Exit\n";
	choice = getValidatedIChar("Please enter your choice number: ");
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
	while (true)
	{	cout << "Are you an Employee (E) or a Customer (C)? ";
		cin >> role;

		if (role == 'E' || role == 'e') {
			temp.isEmployee = true;
			break;
		}
		else if (role == 'C' || role == 'c'){
			temp.isEmployee = false;
			break;
		}
		else
		{
			cout << "Invalid choice.\n";
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}

	cout << "Enter your username:\n";
	cin.ignore();
	getline(cin, temp.userAccount.username);

	while (true) {
	    cout << "Enter your age:\n";
		cin >> temp.age;
		if (cin.fail()) {
			cout << "The age must be an integer number\n";
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else if (temp.age < 16) {
			cout << "Invalid age:)\n";
		}
		else
			break;
	}

	while (true) {
		cout << "Enter your phone number:\n";
		cin >> temp.userAccount.phoneNumber;

		bool allDigits = true;
		for (char c : temp.userAccount.phoneNumber) {
			if (!isdigit(c)) {
				allDigits = false;
				break;
			}
		}
		if (!allDigits) {
			cout << "The phone number must contain only digits.\n";
			continue;
		}
		else if (temp.userAccount.phoneNumber.length() != 11) {
			cout << "The phone number must be 11 digits\n";
			continue;
		}
		else if (findphonenumber(temp.userAccount.phoneNumber, users, totalusers)) {
			cout << "Phone number already used.\n";
			continue;
		}
		else {
			break;
		}
		return false;
	}

	while (true)
	{
		cout << "Enter your email:\n";
		cin >> temp.userAccount.email;
		
		if (findemail(temp.userAccount.email, users, totalusers)) {
			cout << "This email already exists!\n";
		}
		else
			break;
	}
	if (temp.isEmployee) {
		while (true)
		{
			cout << "Enter your password:\n";
			cin >> temp.userAccount.password;
			if (temp.userAccount.password.length() < 7)
			{
				cout << "Password must be atleast 7 digits.\n";
				cin.clear();
				cin.ignore(10000, '\n');
			}
			else if (temp.userAccount.password.length() > 10)
			{
				cout << "Password cannot exceed 10 digits.\n";
				cin.clear();
				cin.ignore(10000, '\n');
			}
			else
				break;
		}
	}
	temp.userAccount.accountNumber = (rand() % 50);
	while (findaccountnum(temp.userAccount.accountNumber, users, totalusers)) {
		temp.userAccount.accountNumber = (rand() % 50) + 1;
	}
	return true;
}

int signin(user users[], int totalusers) {
	char choice;
	user temp;
	string email, password, phonenumber, username;
	bool notfound = true;
	while (true) {
		cout << "Are you an Employee (E) or a Customer (C)? ";
		cin >> choice;

		if (choice == 'E' || choice == 'e') {
			temp.isEmployee = true;
			break;
		}
		else if (choice == 'C' || choice == 'c') {
			temp.isEmployee = false;
			break;
		}
		else
		{
			cout << "Invalid choice.\n";
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
	if (temp.isEmployee) {
		cout << "Enter your email: ";
		cin >> email;
		cout << "Enter your password: ";
		cin >> password;

		//checking if they are true!
		for (int i = 0; i < totalusers; i++) {
			if (users[i].userAccount.email == email && users[i].userAccount.password == password&&users[i].isEmployee==true) {
				cout << "Logged in successfully.\n";
				notfound = false;
				return i;
			}
		}
	}
	else {
		cout << "Enter your username: ";
		cin >> username;
		cout << "Enter your Phonenumber: ";
		cin >> phonenumber;

		//checking if they are true!
		for (int i = 0; i < totalusers; i++) {
			if (users[i].userAccount.username == username && users[i].userAccount.phoneNumber == phonenumber && users[i].isEmployee == false) {
				cout << "Logged in successfully.\n";
				notfound = false;
				return i;
			}
		}
	}

	cout << "This account doesn't exist.\n";
	return 50;

}

// Rating Movies
void movierate(movieinfo movie[]) {
	string title;
	int temp_rate;
	bool rated = true;
	cout << "Enter the title of the movie\n";
	cin.ignore();
	getline(cin, title);

	for (int i = 0;i < number_of_movies;i++)
	{
		if (movie[i].name_of_movie == title)
		{
			if (!users[logged_in_index].ratedMovies[i]) {
				while (rated) {
					cout << "Please enter a rating from 1 to 5\n";
					cin >> temp_rate;
					if (cin.fail()) {
						cout << "Rating should be a number from 1 to 5\n";
						cin.clear();
						cin.ignore(10000, '\n');
					}
					else if (temp_rate < 1 || temp_rate>5) {
						cout << "Sorry, Invalid rating. Should be from 1 to 5 \n";
						//return;
					}
					else {
						movie[i].total_ratings++;
						movie[i].final_score_of_movie += temp_rate;
						movie[i].average_rate = (float)movie[i].final_score_of_movie / movie[i].total_ratings;
						cout << "The new rating is " << movie[i].average_rate << endl;
						cout << "Thank you for your rating:)\n";
						users[logged_in_index].ratedMovies[i] = true;
						rated = false;
						return;
					}
				}
			}
			else {
				cout << "You have already rated this movie\n";
				return;
			}
		}
	}

	return;
}


void outputToFile(user users[], int totalUsers)
{
	ofstream outFile("savedData.txt");
	if (!outFile)
	{
		cerr << "Couldn't open file for writing.";
		return;
	}

	outFile << totalUsers << '|';
	outFile << totalnumofmovies << '|';

	if (outFile.is_open())
	{
		for (int i{ 0 }; i < totalnumofmovies; i++) //output movie information
		{
			outFile << movie[i].name_of_movie << '|'
				<< movie[i].Quantity << '|'
				<< movie[i].rentingCount << '|'
				<< movie[i].price << '|'
				<< movie[i].average_rate << '|'
				<< movie[i].final_score_of_movie << '|'
				<< movie[i].total_ratings << '|';

		}
		for (int i{ 0 }; i < totalUsers; i++)
		{
			outFile
				//<< users[i].userAccount.accountNumber << '|'
				<< users[i].userAccount.username << '|' //output user ID & username to file
				<< users[i].userAccount.phoneNumber << '|'
				<< users[i].userAccount.email << '|'
				<< boolalpha << users[i].isEmployee << '|';
				if (users[i].isEmployee) {
					outFile
						<< users[i].userAccount.password << '|';
				}
				outFile
					<< users[i].userRentals.nMovies << '|'; //outputs number of rented movies to file

			/*for (int j{ 0 };j < number_of_movies;j++) {
				outFile
				<< users[i].ratedMovies[j] << '|';
			}*/

			for (int j{ 0 }; j < users[i].userRentals.nMovies; j++) //output rented movies to file 
			{
				outFile << users[i].userRentals.rentedMovies[j].nameOfRentedMovie << '|';

			}
			outFile << boolalpha << users[i].frozen << '|'; //output frozen status to file



			//Movies Info


			for (int j{ 0 }; j < users[i].userRentals.nMovies; j++) // output user's rented Movie
			{
				//outFile << users[i].userRentals.rentedMovies[j].nameOfRentedMovie << '|';

				int movieIndex = findMovieIndexByName(users[i].userRentals.rentedMovies[j].nameOfRentedMovie);
				if (movieIndex != -1)
				{
					outFile << users[i].userRentals.rentedMovies[j].rentDay.day << '|'
						<< users[i].userRentals.rentedMovies[j].rentDay.month << '|'
						<< users[i].userRentals.rentedMovies[j].rentDay.year << '|';
						/*<< movie[movieIndex].rentingCount << '|'
						<< movie[movieIndex].price << '|';*/
				}
				
			}


			outFile << '\n';
		}
		outFile.close();
	}

}

int getNumberOfUsersFromFile()
{
	string nUsers{};
	ifstream myFile("savedData.txt");
	if (!myFile) return 0;

	getline(myFile, nUsers, '\n');
	if (myFile.eof())
		return 0;
	else
		return stoi(nUsers);
}

void loadFromFile(user users[])
{
	string line{}, value{};
	ifstream myFile("savedData.txt");
	if (!myFile)
	{
		cout << "Couldn't open file for reading.";
		return;
	}

	int currentIndex{ 0 };
	while (getline(myFile, line))
	{
		stringstream ssLine(line);

		if (currentIndex == 0)
		{
			getline(ssLine, value, '|');

			getline(ssLine, value, '|');
			totalnumofmovies = stoi(value);

			for (int i{ 0 }; i < totalnumofmovies; i++)
			{

				getline(ssLine, movie[i].name_of_movie, '|');

				if (getline(ssLine, value, '|') && !value.empty())
					movie[i].Quantity = stoi(value);

				if (getline(ssLine, value, '|') && !value.empty())
					movie[i].rentingCount = stoi(value);

				if (getline(ssLine, value, '|') && !value.empty())
					movie[i].price = stof(value);

				if (getline(ssLine, value, '|') && !value.empty())
					movie[i].average_rate = stof(value);

				if (getline(ssLine, value, '|') && !value.empty())
					movie[i].final_score_of_movie = stoi(value);

				if (getline(ssLine, value, '|') && !value.empty())
					movie[i].total_ratings = stoi(value);


			}
		}

		/*
			getline(ssLine, value, '|');
		if (!value.empty())
			users[currentIndex].userAccount.accountNumber = stoi(value);*/

		getline(ssLine, users[currentIndex].userAccount.username, '|');
		getline(ssLine, users[currentIndex].userAccount.phoneNumber, '|');
		getline(ssLine, users[currentIndex].userAccount.email, '|');

		getline(ssLine, value, '|');
		users[currentIndex].isEmployee = (value == "true");

		if (users[currentIndex].isEmployee==true) {
			getline(ssLine, users[currentIndex].userAccount.password, '|');
		}

		getline(ssLine, value, '|');
		if (!value.empty())
			users[currentIndex].userRentals.nMovies = stoi(value);
		else
			users[currentIndex].userRentals.nMovies = 0;

		for (int i{ 0 }; i < users[currentIndex].userRentals.nMovies; i++)
		{
			getline(ssLine, users[currentIndex].userRentals.rentedMovies[i].nameOfRentedMovie, '|');

		}

		getline(ssLine, value, '|');
		users[currentIndex].frozen = (value == "true");


		if (totalnumofmovies != 0)
		{
			for (int i{ 0 }; i < users[currentIndex].userRentals.nMovies; i++)
			{
				getline(ssLine, users[currentIndex].userRentals.rentedMovies[i].nameOfRentedMovie, '|');

				if (getline(ssLine, value, '|') && !value.empty())
					users[currentIndex].userRentals.rentedMovies[i].rentDay.day = stoi(value);

				if (getline(ssLine, value, '|') && !value.empty())
					users[currentIndex].userRentals.rentedMovies[i].rentDay.month = stoi(value);

				if (getline(ssLine, value, '|') && !value.empty())
					users[currentIndex].userRentals.rentedMovies[i].rentDay.year = stoi(value);

			}
		}

		currentIndex++;
	}
	myFile.close();
}



bool isLeap(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

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

int daysBetween(Date rentday, Date currentday) {
	return abs(dateToDays(currentday) - dateToDays(rentday));
}

void Overdue_clients() {
	for (int i = 0, j = 0; i < 20; i++) {
		bool alreadyMarked{ false };
		int Number_of_days = 0;
		for (int k{0}; k < users[i].userRentals.nMovies; k++)
		{
			Number_of_days = daysBetween(users[i].userRentals.rentedMovies[k].rentDay, currentday);
			if (Number_of_days > duedate) {
				if (!alreadyMarked)
				{
					users[i].frozen = true;
					Overdue[j++] = users[i];

					cout << users[i].userAccount.accountNumber << "." << users[i].userAccount.username << "\t" << users[i].userAccount.phoneNumber << "\n";
					alreadyMarked = true;
				}
			 break;
			}
		}
	};
}

void ListofDaysLeft() {
	for (int i = 0; i < 20; i++) {
		int Number_of_days = 0;
		for (int k{ 0 }; k < users[i].userRentals.nMovies; k++)
		{
			Number_of_days = daysBetween(users[i].userRentals.rentedMovies[k].rentDay, currentday);
		}
		cout << "Number of days: " << Number_of_days << endl;
	}
}

//if user want to rent movie (renting function) //
void Renting() {
	bool renting = true;
	while (renting) {
		int num = 0;
		cout << "\t\tPLEASE CHOOSE MOVIE THAT YOU WANT TO RENT\n";
		displayMovies();
		cout << "Enter a number of movie you want: \n";
		cin >> num;
		if (cin.fail()) {
			cout << "The choice must be a number\n";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		else if (num < 1 || num>number_of_movies) {
			cout << "Invalid number!!!\n";
		}
		else {

			for (int i = 0;i < number_of_movies;i++) {

				if (num - 1 == i) {
					for (int j = 0;j < users[logged_in_index].userRentals.nMovies;j++) {
						if (users[logged_in_index].userRentals.rentedMovies[j].nameOfRentedMovie == movie[i].name_of_movie) {
							cout << "You have already rented this movie\n";
							return;
						}
					}
					if (movie[i].Quantity == 0)
					{
						cout << "Sorry, this movie is not available right now ...\n";
						break;
					}
					else {
						movie[i].Quantity--;
						movie[i].rentingCount++;

						users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].nameOfRentedMovie = movie[i].name_of_movie;

						Rentday(i);

						cout << "\t\tRENTED SUCCESFULLY\n";

						users[logged_in_index].userRentals.nMovies++;
						renting = false;
						break;
					}
				}
			}
		}
	}
}
// NEW
void Rentday(int index) {
	while (true) {
		cout << "\t\tPlease enter the date of rentday\n\n\n";
		users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.day = getValidatedDate("Enter the day: ");
		users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.month = getValidatedDate("Enter the month: ");
		users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year = getValidatedDate("Enter the year: ");


		//check year
		if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year < 2000 ||
			users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year > 2025) {

			cout << "Invalid year!!!\n";
			cout << "Please enter the date again correctly:\n\n";
			continue;
		}
		//check months
		if ((users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year % 4 == 0 &&
			users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year % 100 != 0) ||
			(users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year % 400 == 0)) {

			if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.month == 2) {

				if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.day < 1 ||
					users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.day>29) {

					cout << "Invalid day!!!\n";
					cout << "Please enter the date again correctly:\n\n";
					continue;
				}
				else {
					cout << "\t\tEntered successfully";
					break;
				}

			}

		}

		if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.month > 12 ||
			users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.month < 1) {

			cout << "Invalid month!!!\n";
			cout << "Please enter the date again correctly:\n\n";
			continue;
		}//check days
		else {
			for (int i = 0; i < 12;i++) {
				if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.month == i + 1) {
					if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.day > daysInMonth[i] ||
						users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.day < 1) {
						cout << "Invalid day!!!\n";
						cout << "Please enter the date again correctly:\n\n";
						continue;
					}
					else {
						cout << "\t\tEntered successfully";
						break;
					}
				}

			}
			break;

		}

	}

} 

void Currentday() {
	bool trueDate = true;
	while (trueDate) {
		cout << "\t\tPlease Enter the date of today\n\n";
		cout << "Enter the day: ";
		cin >> currentday.day;

		if (cin.fail())
		{
			cout << "Please enter a number.\n";
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Please enter the date again correctly:\n\n";
			continue;
		}


		cout << "Enter the month: ";
		cin >> currentday.month;
		if (cin.fail())
		{
			cout << "Please enter a number.\n";
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\tPlease enter the date again correctly:\n\n";
			continue;
		}

		cout << "Enter the year: ";
		cin >> currentday.year;
		if (cin.fail())
		{
			cout << "Please enter a number.\n";
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\tPlease enter the date again correctly:\n\n";
			continue;
		}

		//check year
		if (currentday.year > 0 && currentday.year < 2025) {

			cout << "\tInvalid year!!!\n";
			cout << "\tPlease enter the date again correctly:\n\n";
			continue;
		}
		//check monthes
		if ((currentday.year % 4 == 0 && currentday.year % 100 != 0) || (currentday.year % 400 == 0)) {

			if (currentday.month == 2) {

				if (currentday.day < 1 || currentday.day>29) {

					cout << "\tInvalid day!!!\n";
					cout << "\tPlease enter the date again correctly:\n\n";
					continue;
				}
				else {
					cout << "\t\tEntered successfully\n";
					trueDate = false;
					break;
				}

			}
		}

		if (currentday.month > 12 || currentday.month < 1) {

			cout << "\tInvalid month!!!\n";
			cout << "\tPlease enter the date again correctly:\n\n";
			continue;
		}//check days
		else {
			for (int i = 0; i < 12; i++) {
				if (currentday.month == i + 1) {
					if (currentday.day > daysInMonth[i] || currentday.day < 1) {
						cout << "\tInvalid day!!!\n";
						cout << "\tPlease enter the date again correctly:\n\n";
						continue;
					}
					else {
						cout << "\t\tEntered successfully\n";
						trueDate = false;
						break;
					}
				}

			}
		}

	}
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
	for (int i = 0; i < totalnumofmovies; i++) {
		cout << movie[i].name_of_movie << " - Rentals: " << movie[i].rentingCount << endl;
	}
}



// Displaying information
void displayCustomers(int totalusers) {
	int j = 1;
	for (int i = 0; i < totalusers; i++)
	{
		if (!users[i].isEmployee) {
			cout << j<<". " << users[i].userAccount.username << '\n';
			j++;
		}
	}
}

void displayRentedMovies() {
	for (int i = 0; i < totalnumofmovies; i++) 
	{
		{
			if (users[i].userRentals.nMovies > 0)
			{
				cout << "Rented movies for user: " << users[i].userAccount.username << '\n';

				for (int j{ 0 }; j < users[i].userRentals.nMovies; j++)
					cout << users[i].userRentals.rentedMovies[j].nameOfRentedMovie << '\n';
			}
		}
	}
}

//Menna
void addingMovies(int count)
{
	bool found = true;
	if (totalnumofmovies > number_of_movies) {
		cout << "sorry we have reached the maximum number of movies\n";
		return;
	}
	else {
		for (int i = 0;i < count;i++) {
			found = true;
			cout << "Enter the movie name:\n";
			cin.ignore();
			getline(cin, movie[totalnumofmovies].name_of_movie);
			for (int j = 0;j < totalnumofmovies;j++) {
				if (movie[totalnumofmovies].name_of_movie == movie[j].name_of_movie) {
					found = false;
				}
			}
			if (!found) {
				cout << "This Movie already exist\n";
				count++;
			}
			else {
				cout << "Enter the price of the movie for a day:\n";
				cin >> movie[totalnumofmovies].price;
				cout << "Enter the quantity of the movie\n";
				cin >> movie[totalnumofmovies].Quantity;
				totalnumofmovies++;
				if (totalnumofmovies > number_of_movies) {
					cout << "sorry we have reached the maximum number of movies\n";
					return;
				}
			}
		}
	}
}
void moviemanagment()
{
	int count;
	while (true) {
		cout << "Enter how many movies you want to input\n";
		cin >> count;

		if (cin.fail())
		{
			cout << "Please enter a number.\n";
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		else
			break;
	}
	addingMovies(count);
}

void Calculate_totalPrice() {
	int Nom_of_days;
	float TotalPrice = 0;
	bool found{ false };
	string tempNameOfMovie;

	cout << "Enter the name of movie you want to return:\n";
	cin.ignore();
	getline(cin, tempNameOfMovie);

	for (int j = 0; j < users[logged_in_index].userRentals.nMovies; j++) {
		if (users[logged_in_index].userRentals.rentedMovies[j].nameOfRentedMovie == tempNameOfMovie) {

			if (users[logged_in_index].userRentals.rentedMovies[j].rentDay.day == 0 &&
				users[logged_in_index].userRentals.rentedMovies[j].rentDay.month == 0 &&
				users[logged_in_index].userRentals.rentedMovies[j].rentDay.year == 0) {
				cout << "You haven't rented this movie yet.\n";
				return;
			}
			else {
				found = true;
				Currentday();  // sets the currentday variable
				Nom_of_days = daysBetween(users[logged_in_index].userRentals.rentedMovies[j].rentDay, currentday);

				// Find the movie in the movies list
				for (int k = 0; k < number_of_movies; k++) {
					if (movie[k].name_of_movie == tempNameOfMovie) {

						if (Nom_of_days <= duedate) {
							TotalPrice = movie[k].price * Nom_of_days;
							cout << "You have to pay: " << TotalPrice << " pounds.\n";
						}
						else {
							TotalPrice = (movie[k].price*Nom_of_days) + ((Nom_of_days - duedate) * (0.05f * movie[k].price));
							cout << "You delayed returning the movie by " << (Nom_of_days - duedate) << " days.\n"
								<< "You have to pay: " << TotalPrice << " pounds.\n"
								<< "NOTE: 5% penalty per delayed day.\n";
						}
						movie[k].Quantity++;
						users[logged_in_index].userRentals.nMovies--;
						TotalPrice = 0;
						users[logged_in_index].userRentals.rentedMovies[j].rentDay= { 0, 0, 0 };
						return;
					}
				}
			}
		}
	}

	if (!found) {
		cout << "You have not rented this movie.\n";
	}
}

void ViewAccountInfo() {
	cout << "Username:\t" << users[logged_in_index].userAccount.username << "\n";
	cout << "Email:\t" << users[logged_in_index].userAccount.email << "\n";
	cout << "Password:\t" << users[logged_in_index].userAccount.password << "\n";
	cout << "PhoneNumber:\t" << users[logged_in_index].userAccount.phoneNumber << "\n";
	if (users[logged_in_index].frozen) {
		cout << "Your account is blocked\n";
	}
	else cout << "Your account is not blocked\n";
}

void displayMovies() {
	cout << "Movies: " << "\t\t " << "Rate:\n";
	for (int i = 0; i < totalnumofmovies; i++)
	{
		cout << i + 1 << ". " << movie[i].name_of_movie << "\t\t " << movie[i].average_rate;
		cout << '\n';
	}
};

void update(movieinfo movie[]) {
	displayMovies();
	int choose, quantity;
	float price;
	while (true)
	{

		choose = getValidatedInt("Enter the number of the movie you want to edit\n", "Invalid Choice.\n");
		if (choose > totalnumofmovies)
		{
			cout << "Please choose a valid movie number.\n";
			continue;
		}
		else
			break;
	}
	cout << "Enter new quantity\n";
	cin >> quantity;
	movie[choose - 1].Quantity = quantity;
	cout << "Enter new fees's price\n";
	cin >> price;
	movie[choose - 1 ].price = price;

};

int findMovieIndexByName(string_view movieName)
{
	for (int i{ 0 }; i < totalnumofmovies; i++)
	{
		if (movieName == movie[i].name_of_movie)
			return i;
	}
	return -1;
}

char getValidatedIChar(string_view sentence)
{

	string choice{};
	while (true)
	{
	    cout << sentence;
		getline(cin >> ws, choice);
		if (choice.length() == 1 && isdigit(choice[0]))
			return choice[0];
		else
		{
			cout << "Invalid Choice.\n";
			continue;
		}
	}
}

int getValidatedInt(string_view sentence, string_view ERRORsentence)
{

	string choice{};
	while (true)
	{
		cout << sentence;
		getline(cin >> ws, choice);
		int validatedDigit[2] = { isdigit(choice[0]), isdigit(choice[1]) };
		if (choice.length() == 1 || choice.length() == 2 && (validatedDigit[0]
			|| (validatedDigit[0] && validatedDigit[1])))
			return stoi(choice);
		else
		{
			cout << ERRORsentence;
			continue;
		}
	}
}

int getValidatedDate(string_view sentence)
{
	int input{};
	while(true)
	{
		cout << sentence;
		cin >> input;
		if (cin.fail())
		{
			cout << "Please enter a number.\n";
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Please enter the date again correctly:\n\n";
			continue;
		}
		else 
			return input;
	}
}
