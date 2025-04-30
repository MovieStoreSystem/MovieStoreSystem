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
			cout << "1.Sign up \n2.Sign in\n";
			cin >> choice;

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
					return 0;
				}
				sign = false;
				break;
			default:
				cout << "invalid choice\n";
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
				Calculate_totalPrice();
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
	cout << "5.Show Freezed Customers\n";
	cout << "6.Remove a Movie\n"; // Missing
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

	cout << "Enter your password:\n";
	cin >> temp.userAccount.password;

	temp.userAccount.accountNumber = (rand() % 50);
	while (findaccountnum(temp.userAccount.accountNumber, users, totalusers)) {
		temp.userAccount.accountNumber = (rand() % 50) + 1;
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
	return 50;
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

//
//void outputToFile(user users[], int totalUsers)
//{
//	ofstream outFile("savedData.txt");
//	if (!outFile)
//	{
//		cerr << "Couldn't open file for writing.";
//		return;
//	}
//
//	if (outFile.is_open())
//	{
//		// Write totalUsers and totalnumofmovies first
//		outFile << totalUsers << '|'
//			<< totalnumofmovies << '|';
//
//		// Write all movie information
//		for (int i{ 0 }; i < totalnumofmovies; i++)
//		{
//			outFile << movie[i].name_of_movie << '|'
//				<< movie[i].Quantity << '|'
//				<< movie[i].rentingCount << '|'
//				<< movie[i].price << '|'
//				<< movie[i].average_rate << '|'
//				<< movie[i].final_score_of_movie << '|'
//				<< movie[i].total_ratings << '|';
//		}
//
//		// Write all users
//		for (int i{ 0 }; i < totalUsers; i++)
//		{
//			outFile << users[i].userAccount.username << '|'
//				<< users[i].userAccount.phoneNumber << '|'
//				<< users[i].userAccount.email << '|'
//				<< users[i].userAccount.password << '|'
//				<< boolalpha << users[i].isEmployee << '|'
//				<< users[i].userRentals.nMovies << '|';
//
//			for (int j{ 0 }; j < users[i].userRentals.nMovies; j++)
//			{
//				outFile << users[i].userRentals.rentedMovies[j].nameOfRentedMovie << '|'
//					<< users[i].userRentals.rentedMovies[j].rentDay.day << '|'
//					<< users[i].userRentals.rentedMovies[j].rentDay.month << '|'
//					<< users[i].userRentals.rentedMovies[j].rentDay.year << '|';
//			}
//
//			outFile << boolalpha << users[i].frozen << '|';
//
//			outFile << '\n'; // New line for the next user
//		}
//
//		outFile.close(); //chat gpt changes idon't know what is the difference but all i know that it doesn't work with the last function ,good luck cause i tried to understand it and it is hard
//		            // Sorry, I couldn't help you :( it's okayyy dont worry abt it 
//	}
//}

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
				<< movie[i].price << '|';

		}
		for (int i{ 0 }; i < totalUsers; i++)
		{
			outFile
				//<< users[i].userAccount.accountNumber << '|'
				<< users[i].userAccount.username << '|' //output user ID & username to file
				<< users[i].userAccount.phoneNumber << '|'
				<< users[i].userAccount.email << '|'
				<< users[i].userAccount.password << '|'
				<< boolalpha << users[i].isEmployee << '|'
				<< users[i].userRentals.nMovies << '|'; //outputs number of rented movies to file

			for (int j{ 0 }; j < users[i].userRentals.nMovies; j++) //output rented movies to file 
			{
				outFile << users[i].userRentals.rentedMovies[j].nameOfRentedMovie << '|';

			}
			outFile << boolalpha << users[i].frozen << '|'; //output frozen status to file



			//Movies Info


			for (int j{ 0 }; j < users[i].userRentals.nMovies; j++) // output user's rented Movie
			{
				outFile << users[i].userRentals.rentedMovies[j].nameOfRentedMovie << '|';

				int movieIndex = findMovieIndexByName(users[i].userRentals.rentedMovies[j].nameOfRentedMovie);
				if (movieIndex != -1)
				{
					outFile << users[i].userRentals.rentedMovies[j].rentDay.day << '|'
						<< users[i].userRentals.rentedMovies[j].rentDay.month << '|'
						<< users[i].userRentals.rentedMovies[j].rentDay.year << '|'
						<< movie[movieIndex].rentingCount << '|'
						<< movie[movieIndex].price << '|';
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
		cerr << "Couldn't open file for reading.";
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
			}
		}

		/*
			getline(ssLine, value, '|');
		if (!value.empty())
			users[currentIndex].userAccount.accountNumber = stoi(value);*/

		getline(ssLine, users[currentIndex].userAccount.username, '|');
		getline(ssLine, users[currentIndex].userAccount.phoneNumber, '|');
		getline(ssLine, users[currentIndex].userAccount.email, '|');
		getline(ssLine, users[currentIndex].userAccount.password, '|');

		getline(ssLine, value, '|');
		users[currentIndex].isEmployee = (value == "true");

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

	int num = 0;
	cout << "\t\tPLEASE CHOOSE MOVIE THAT YOU WANT TO RENT\n";
	displayMovies();
	cout << "Enter a number of movie you want: \n";
	cin >> num;


	if (num < 1 || num>number_of_movies) {
		cout << "Invalid number!!!\n";
	}
	else {
		bool movieRented{ false };
		for (int i = 0;i < number_of_movies;i++) {

			if (num - 1 == i) {
				if (movie[i].Quantity == 0)
				{
					cout << "Sorry, this movie is not available right now ...\n";
					movieRented = false;
					break;
				}
				else {
					movie[i].Quantity--;
					movie[i].rentingCount++;

					users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].nameOfRentedMovie = movie[i].name_of_movie;

					Rentday(i);

					cout << "\t\tRENTED SUCCESFULLY\n";

					users[logged_in_index].userRentals.nMovies++;
					movieRented = true;
					break;
				}
			}
		}
		if (!movieRented)
			cout << "Couldn't rent the movie.\n";
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

void displayMovies() {
	for (int i = 0; i < totalnumofmovies; i++)
	{
		cout << "Movies: " << "\t" << "Rate:";
		cout <<i+1<<". " << movie[i].name_of_movie<<"\t"<<movie[i].average_rate;
		cout << '\n';
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
	if (totalnumofmovies > number_of_movies) {
		cout << "sorry we have reached the maximum number of movies\n";
		return;
	}
	else {
		for (int i = totalnumofmovies;i < count+totalnumofmovies;i++) {
			cout << "Enter the movie name:\n";
			cin.ignore();
			getline(cin, movie[i].name_of_movie);
			cout << "Enter the price of the movie for a day:\n";
			cin >> movie[i].price;
			cout << "Enter the quantity of the movie\n";
			cin >> movie[i].Quantity;
			
			if (i > number_of_movies) {
				cout << "sorry we have reached the maximum number of movies\n";
				return;
			}
		}
		totalnumofmovies+=count;
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

//shrouk
void Calculate_totalPrice() {
	int Nom_of_days;
	float TotalPrice = 0;
	bool found{ false };
	string tempNameOfMovie;

	cout << "Enter the name of movie you want to return:\n";
	cin >> tempNameOfMovie;

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
							TotalPrice = movie[k].price + ((Nom_of_days - duedate) * (0.05f * movie[k].price));
							cout << "You delayed returning the movie by " << (Nom_of_days - duedate) << " days.\n"
								<< "You have to pay: " << TotalPrice << " pounds.\n"
								<< "\t\tNOTE: 5% penalty per delayed day.\n";
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

void Rentday(int index) {
	cout << "Enter the day of renting\n";
	cin >> users[logged_in_index].userRentals.rentedMovies[index].rentDay.day;
	cout << "Enter the month of renting\n";
	cin >> users[logged_in_index].userRentals.rentedMovies[index].rentDay.month;
	cout << "Enter the year of renting\n";
	cin >> users[logged_in_index].userRentals.rentedMovies[index].rentDay.year;
}

void Currentday() {
	cout << "Enter the date of today\n";
	cin >> currentday.day >> currentday.month >> currentday.year;
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

//void update() {
//	bool found;
//	cout << "Enter New Shipments data\n";
//	for (int i = 0; i < number_of_movies; i++) {
//		cin >> x.name_of_movie >> x.Quantity;
//		if (movie[i].name_of_movie == x.name_of_movie) {
//			found = true;
//			movie[i].quantity += x.Quantity;
//		}
//		if (movie[i].name_of_movie != x.name_of_movie) {
//			found = false;
//			movie[i].quantity = 0;
//			movie[i].quantity += x.Quantity;
//			addingMovies(x.Quantity);
//		}
//	}
//}


int findMovieIndexByName(string_view movieName)
{
	for (int i{ 0 }; i < totalnumofmovies; i++)
	{
		if (movieName == movie[i].name_of_movie)
			return i;
	}
	return -1;
}