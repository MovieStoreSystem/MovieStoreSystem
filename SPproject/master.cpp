#include "master.h"
#include <cmath>
#include <cstdlib>
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

			cout << "Please wait...\n";
			platform::wait(2000);
			system("CLS");

			choice = getValidatedChar("1.Sign up \t 2.Sign in");

			system("CLS");

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
				printCenteredText("Invalid Choice");
				break;

			}

		}
		cout << '\n';
		printCenteredText("Welcome to our Movie Store");

	while(open) {
			cout << '\n' << string(nCharactersToFillUpConsole, '=') << '\n';
			printCenteredText("MENU");
			cout << string(nCharactersToFillUpConsole, '=') << '\n';
		if (users[logged_in_index].isEmployee)
		{
			switch (employeermenu())
			{
			case '1':
				system("CLS");
				moviemanagment();
				break;

			case '2':
				system("CLS");
				displayMovies();
				break;

			case '3':
				system("CLS");
				displayCustomers(total_users);
				break;

			case '4':
				system("CLS");
				sortMoviesByCount();
				break;
			case '5':
				system("CLS");
				Display_High_Rated_Movies();
				break;
			case '6':
				system("CLS");
				Overdue_clients();
				break;
			case '7':
				system("CLS");
				deleteMovies();
				break;
			case '8':
				system("CLS");
				update(movie);
				break;

			case '9':
				printCenteredText("Exiting!");
				printCenteredText("Thank you for using our system :)");
				open = false;
				break;
			default:
				printCenteredText("Sorry, Invalid choice!");
				break;
			}
		}
		else
		{

			switch (customermenu())
			{
			case '1':
				system("CLS");
				displayMovies();
				break;

			case '2':
				system("CLS");
				Buy_A_Movie();
				break;
			case '3':
				system("CLS");
				Renting();
				break;

			case '4':
				system("CLS");
				Calculate_totalPrice();
				break;

			case '5':
				system("CLS");
				ViewAccountInfo();
				break;

			case '6':
				system("CLS");
				movierate();
				break;

			case '7':
				system("CLS");
				BoughtandRentedMovies();
				break;

			case '8':
				printCenteredText("Exiting!");
				printCenteredText("Thank you for using our system :)");
				open = false;
				break;

			default:
				printCenteredText("Sorry, Invalid choice!");
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
	printCenteredText("1. View Movies");
	printCenteredText("2. Buy a Movie");
	printCenteredText("3. Rent a Movie");
	printCenteredText("4. Return a Movie");
	printCenteredText("5. View Account Information");
	printCenteredText("6. Rate a Movie / Leave a Review");
	printCenteredText("7. View Currently Rented Movies");
	printCenteredText("8. Exit");
	cout << string(nCharactersToFillUpConsole, '-') << '\n';
	choice = getValidatedChar("Please enter your choice number: ");
	return choice;
}
char employeermenu()
{
	char choice;
	printCenteredText("1.Add a Movie");
	printCenteredText("2.List all Movies");
	printCenteredText("3.List all Customers");
	printCenteredText("4.Most rented movies");
	printCenteredText("5.High Rated Movies");
	printCenteredText("6.Overdue Customers");
	printCenteredText("7.Remove a Movie");
	printCenteredText("8.Edit Movie Information");
	printCenteredText("9.Exit");
	cout << string(nCharactersToFillUpConsole, '-') << '\n';
	choice = getValidatedChar("Please enter your choice number: ");
	return choice;
}

//For layout
void printCenteredText(string coutText, int width)
{
	int padding = (width - coutText.length()) / 2;
	cout << string(padding, ' ') << coutText << '\n';
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
			printCenteredText("Invalid choice.");
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}

	cout << "[Step 1/5] Enter your username:\n";
	cin.ignore();
	getline(cin, temp.userAccount.username);

	while (true) {
	    cout << "[Step 2/5] Enter your age:\n";
		cin >> temp.age;
		if (cin.fail()) {

			printCenteredText("The age must be an integer number.");
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else if (temp.age < 16) {
			printCenteredText("Invalid age :(");
		}
		else
			break;
	}

	while (true) {
		cout << "[Step 3/5] Enter your phone number:\n";
		cin >> temp.userAccount.phoneNumber;

		bool allDigits = true;
		for (char c : temp.userAccount.phoneNumber) {
			if (!isdigit(c)) {
				allDigits = false;
				break;
			}
		}
		if (!allDigits) {
			printCenteredText("The phone number must contain only digits.");
			continue;
		}
		else if (temp.userAccount.phoneNumber.length() != 11) {
			printCenteredText("The phone number must be 11 digits");
			continue;
		}
		else if (findphonenumber(temp.userAccount.phoneNumber, users, totalusers)) {
			printCenteredText("Phone number already used.\n");
			continue;
		}
		else {
			break;
		}
		return false;
	}

	while (true)
	{
		cout << "[Step 4/5] Enter your email:\n";
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
			cout << "[Step 5/5] Enter your password:\n";
			cin >> temp.userAccount.password;
			if (temp.userAccount.password.length() < 7)
			{
				printCenteredText("Password must be atleast 7 digits.");
				cin.clear();
				cin.ignore(10000, '\n');
			}
			else if (temp.userAccount.password.length() > 10)
			{
				printCenteredText("Password cannot exceed 10 digits.");
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
			printCenteredText("Invalid choice.");
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
				printCenteredText("LOGGED IN SUCCESFULLY");
				cout << '\n';
				notfound = false;
				return i;
			}
		}
	}
	else {
		cout << "Enter your username: ";
		cin >> username;
		cout << "Enter your phonenumber: ";
		cin >> phonenumber;

		//checking if they are true!
		for (int i = 0; i < totalusers; i++) {
			if (users[i].userAccount.username == username && users[i].userAccount.phoneNumber == phonenumber && users[i].isEmployee == false) {
				printCenteredText("LOGGED IN SUCCESSFULLY.");
				notfound = false;
				return i;
			}
		}
	}

	printCenteredText("This account doesn't exist.");
	return 50;

}

// Rating Movies
void movierate() {
	string title;
	float temp_rate;
	bool rated = true;
	bool found=false;
	displayMovies();
	cout << "Enter the title of the movie\n";
	//cin.ignore();
	getline(cin, title);

	for (int i = 0;i < totalnumofmovies;i++)
	{
		if (title==movie[i].name_of_movie )
		{
			found = true;
			if (!users[logged_in_index].ratedMovies[i]) {
				while (rated) {
					cout << "Please enter a rating from 1 to 5\n";
					cin >> temp_rate;
					if (cin.fail()) {
						printCenteredText("Rating should be a number from 1 to 5");
						cin.clear();
						cin.ignore(10000, '\n');
					}
					else if (temp_rate < 1 || temp_rate>5) {
						printCenteredText("Sorry, Invalid rating. Should be from 1 to 5 ");
					}
					else {
						movie[i].total_ratings++;
						movie[i].final_score_of_movie += temp_rate;
						movie[i].average_rate = movie[i].final_score_of_movie / movie[i].total_ratings;
						cout << "The new rating is " << movie[i].average_rate << endl;
						printCenteredText("Thank you for your rating:)");
						users[logged_in_index].ratedMovies[i] = true;
						Display_High_Rated_Movies();
						rated = false;
						return;
					}
				}
			}
			else {
				printCenteredText("You have already rated this movie");
				return;
			}
		}
		
	}
	if (!found) {
		printCenteredText("Sorry,This Movie is not available");
	}

	return;
}
void Display_High_Rated_Movies() {
	//movieinfo High_Rated_Movie[number_of_movies];
	for (int i = 0;i < totalnumofmovies;i++) {

		for (int j = i+1;j < totalnumofmovies;j++) {
			if (movie[i].average_rate<movie[j].average_rate) {
				swap(movie[i], movie[j]);
			}
		}
	}
	displayMovies();

}

void Buy_A_Movie() {
	int choice;
	bool buying = true;
	displayMovies();
	while (buying) {
	cout << "Enter the number of the movie you want to buy:\n";
	cin >> choice;
		if (cin.fail()){
			printCenteredText("Please enter an integar number:");
			continue;
		}
		else if (choice<1 || choice>totalnumofmovies ) {
			printCenteredText("Invalid number");
			continue;
		}
		else {

			if (movie[choice - 1].Quantity == 0) {
				printCenteredText("Sorry,This movie is no longer availble");
				buying = false;
				break;
			}
			else {
				movie[choice - 1].Quantity--;
				users[logged_in_index].userBought.name_of_bought_movies[users[logged_in_index].userBought.nBoughtMovies] = movie[choice-1].name_of_movie;
				users[logged_in_index].userBought.nBoughtMovies++;
				cout << "Your total Price is: " << movie[choice - 1].price * 30;
				buying = false;
				break;
			}

		}
	}
}

void BoughtandRentedMovies() {
	cout << "Your Rented Movies:\n";
	if (users[logged_in_index].userRentals.nMovies == 0)
		cout << "You haven't rented any movies yet.\n";
	else
	{
		for (int i = 0;i < users[logged_in_index].userRentals.nMovies;i++) {
			cout << i + 1 << ". " << users[logged_in_index].userRentals.rentedMovies[i].nameOfRentedMovie << "\n";
		}
	}
	cout << "Your Bought Movies:\n";
	if (users[logged_in_index].userBought.nBoughtMovies == 0)
		cout << "You haven't bought any movies yet.\n";
	else 
	{
		for (int i = 0;i < users[logged_in_index].userBought.nBoughtMovies;i++) {
			cout << i + 1 << ". " << users[logged_in_index].userBought.name_of_bought_movies[i] << "\n";
		}
	}
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
		outFile << '\n';
		for (int i{ 0 }; i < totalUsers; i++)
		{
			outFile
				<< users[i].userAccount.username << '|' //output user ID & username to file
				<< users[i].userAccount.phoneNumber << '|'
				<< users[i].userAccount.email << '|'
				<< boolalpha << users[i].isEmployee << '|';
			if (users[i].isEmployee) {
				outFile << users[i].userAccount.password << '|';
			}
			outFile << users[i].userRentals.nMovies << '|'; //outputs number of rented movies to file

			for (int j{ 0 }; j < users[i].userRentals.nMovies; j++) // output user's rented Movie
			{
				outFile << users[i].userRentals.rentedMovies[j].nameOfRentedMovie << '|';

				int movieIndex = findMovieIndexByName(users[i].userRentals.rentedMovies[j].nameOfRentedMovie);
				if (movieIndex != -1)
				{
					outFile << users[i].userRentals.rentedMovies[j].rentDay.day << '|'
						<< users[i].userRentals.rentedMovies[j].rentDay.month << '|'
						<< users[i].userRentals.rentedMovies[j].rentDay.year << '|';

				}

			}

			outFile	<< users[i].userBought.nBoughtMovies << '|';
			for (int j{ 0 }; j < users[i].userBought.nBoughtMovies; j++) //output bought movies to file 
			{
				outFile << users[i].userBought.name_of_bought_movies[j] << '|';

			}
			outFile << boolalpha << users[i].frozen << '|'; //output frozen status to file
		
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


	getline(myFile, line);
	stringstream ssLine(line);
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
	int currentIndex{ 0 };
	while (getline(myFile, line))
	{
		stringstream ssLine(line);

		getline(ssLine, users[currentIndex].userAccount.username, '|');
		getline(ssLine, users[currentIndex].userAccount.phoneNumber, '|');
		getline(ssLine, users[currentIndex].userAccount.email, '|');

		getline(ssLine, value, '|');
		users[currentIndex].isEmployee = (value == "true");

		if (users[currentIndex].isEmployee == true) {
			getline(ssLine, users[currentIndex].userAccount.password, '|');
		}

		getline(ssLine, value, '|');
		if (!value.empty())
			users[currentIndex].userRentals.nMovies = stoi(value);
		else
			users[currentIndex].userRentals.nMovies = 0;

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

		getline(ssLine, value, '|');
		if (!value.empty())
			users[currentIndex].userBought.nBoughtMovies = stoi(value);
		else
			users[currentIndex].userBought.nBoughtMovies = 0;

		for (int i{ 0 }; i < users[currentIndex].userBought.nBoughtMovies; i++)
		{
			getline(ssLine, users[currentIndex].userBought.name_of_bought_movies[i], '|');

		}

		getline(ssLine, value, '|');
		users[currentIndex].frozen = (value == "true");

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
	Currentday();
	int count = 1;
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
					cout << "Name of Customer:\t\t" << "Their Phone Number\t\t" << "Their Email\n";
					cout << count++<< "." << users[i].userAccount.username << "\t\t\t" << users[i].userAccount.phoneNumber << "\t\t\t"<<users[i].userAccount.email<<'\n';
					alreadyMarked = true;
				}
			 break;
			}
		}
	}
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
		printCenteredText("PLEASE CHOOSE A MOVIE TO RENT");
		displayMovies();
		cout << "Enter a number of movie you want: \n";
		cin >> num;
		if (cin.fail()) {
			printCenteredText ("The choice must be a number");
			cin.clear();
			cin.ignore(10000, '\n');
		}

		else if (num < 1 || num>number_of_movies) {
			printCenteredText("Invalid number.");
		}
		else {

			for (int i = 0;i < number_of_movies;i++) {

				if (num - 1 == i) {
					for (int j = 0;j < users[logged_in_index].userRentals.nMovies;j++) {
						if (users[logged_in_index].userRentals.rentedMovies[j].nameOfRentedMovie == movie[i].name_of_movie) {
							printCenteredText("You have already rented this movie");
							return;
						}
					}
					if (movie[i].Quantity == 0)
					{
						printCenteredText("Sorry, this movie is not available right now ...");
						break;
					}
					else {
						movie[i].Quantity--;
						movie[i].rentingCount++;

						users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].nameOfRentedMovie = movie[i].name_of_movie;

						Rentday(i);

						printCenteredText("RENTED SUCCESFULLY");

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
		printCenteredText("Please enter the date of rentday");
		users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.day = getValidatedDate("Enter the day: ");
		users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.month = getValidatedDate("Enter the month: ");
		users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year = getValidatedDate("Enter the year: ");


		//check year
		if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year < 2000 ||
			users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year > 2025) {

			printCenteredText("Invalid year!");
			printCenteredText("Please enter the date again correctly:");
			continue;
		}
		//check months
		if ((users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year % 4 == 0 &&
			users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year % 100 != 0) ||
			(users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.year % 400 == 0)) {

			if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.month == 2) {

				if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.day < 1 ||
					users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.day>29) {

					printCenteredText("Invalid day!");
					printCenteredText("Please enter the date again correctly:");
					continue;
				}
				else {
					break;
				}

			}

		}

		if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.month > 12 ||
			users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.month < 1) {

			printCenteredText("Invalid month!");
			printCenteredText("Please enter the date again correctly:");
			continue;
		}//check days
		else {
			for (int i = 0; i < 12;i++) {
				if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.month == i + 1) {
					if (users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.day > daysInMonth[i] ||
						users[logged_in_index].userRentals.rentedMovies[users[logged_in_index].userRentals.nMovies].rentDay.day < 1) {
						printCenteredText("Invalid day!");
						printCenteredText("Please enter the date again correctly:");
						continue;
					}
					else {
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
			printCenteredText("Please enter a number.");
			cin.clear();
			cin.ignore(10000, '\n');
			printCenteredText("Please enter the date again correctly:");
			continue;
		}


		cout << "Enter the month: ";
		cin >> currentday.month;
		if (cin.fail())
		{
			printCenteredText("Please enter a number.");
			cin.clear();
			cin.ignore(10000, '\n');
			printCenteredText("\tPlease enter the date again correctly:");
			continue;
		}

		cout << "Enter the year: ";
		cin >> currentday.year;
		if (cin.fail())
		{
			printCenteredText("Please enter a number.");
			cin.clear();
			cin.ignore(10000, '\n');
			printCenteredText("Please enter the date again correctly:");
			continue;
		}

		//check year
		if (currentday.year > 0 && currentday.year < 2025) {

			printCenteredText("Invalid year!");
			printCenteredText("Please enter the date again correctly:");
			continue;
		}
		//check monthes
		if ((currentday.year % 4 == 0 && currentday.year % 100 != 0) || (currentday.year % 400 == 0)) {

			if (currentday.month == 2) {

				if (currentday.day < 1 || currentday.day>29) {

					printCenteredText("Invalid day!");
					printCenteredText("Please enter the date again correctly:");
					continue;
				}
				else {
					trueDate = false;
					break;
				}

			}
		}

		if (currentday.month > 12 || currentday.month < 1) {

			printCenteredText("Invalid month!");
			printCenteredText("Please enter the date again correctly:");
			continue;
		}//check days
		else {
			for (int i = 0; i < 12; i++) {
				if (currentday.month == i + 1) {
					if (currentday.day > daysInMonth[i] || currentday.day < 1) {
						printCenteredText("\tInvalid day!");
						printCenteredText("\tPlease enter the date again correctly:");
						continue;
					}
					else {
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

//Menna
void addingMovies(int count)
{
	bool found = true;
	if (totalnumofmovies > number_of_movies) {
		printCenteredText("Sorry we have reached the maximum number of movies...");
		return;
	}
	else {
		for (int i = 0;i < count;i++) {
			found = true;
			cout << "Enter the movie name of movie number #" << i + 1 << '\n';
			cin.ignore();
			getline(cin, movie[totalnumofmovies].name_of_movie);
			for (int j = 0;j < totalnumofmovies;j++) {
				if (movie[totalnumofmovies].name_of_movie == movie[j].name_of_movie) {
					found = false;
				}
			}
			if (!found) {
				printCenteredText("This movie already exists.");
				count++;
			}
			else {
				while (true) {
					cout << "Enter the price of the movie for a day #" << i + 1 << '\n';
					cin >> movie[totalnumofmovies].price;

					if (cin.fail())
					{
						printCenteredText("Please enter a number.");
						cin.clear();
						cin.ignore(10000, '\n');
						continue;
					}
					else
						break;
				}
				while (true) {

					cout << "Enter the quantity of the movie number #" << i + 1 << '\n';
					cin >> movie[totalnumofmovies].Quantity;
					
					if (cin.fail())
					{
						printCenteredText("Please enter a number.");
						cin.clear();
						cin.ignore(10000, '\n');
						continue;
					}
					else
						break;
				}

				totalnumofmovies++;
				if (totalnumofmovies == number_of_movies) {
					printCenteredText("Sorry we have reached the maximum number of movies...");
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
		cout << "Enter how many movies you want to input:\n";
		cin >> count;

		if (cin.fail())
		{
			printCenteredText("Please enter a number.");
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

	BoughtandRentedMovies();
	cout << '\n';
	cout << "Enter the name of movie you want to return:\n";
	getline(cin >> ws, tempNameOfMovie);

	for (int j = 0; j < users[logged_in_index].userRentals.nMovies; j++) {
		if (users[logged_in_index].userRentals.rentedMovies[j].nameOfRentedMovie == tempNameOfMovie) {

			if (users[logged_in_index].userRentals.rentedMovies[j].rentDay.day == 0 &&
				users[logged_in_index].userRentals.rentedMovies[j].rentDay.month == 0 &&
				users[logged_in_index].userRentals.rentedMovies[j].rentDay.year == 0) {
				printCenteredText("You haven't rented this movie yet.");
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
		printCenteredText("You have not rented this movie.");
	}
}

void ViewAccountInfo() {
	printCenteredText("Username:");
	printCenteredText(users[logged_in_index].userAccount.username);
	cout << '\n';
	printCenteredText("Email:");
	printCenteredText(users[logged_in_index].userAccount.email);
	cout << '\n';
	if (users[logged_in_index].isEmployee)
	{
		printCenteredText("Password:");
		printCenteredText(users[logged_in_index].userAccount.password);
		cout << '\n';
	}
	printCenteredText("PhoneNumber:");
	printCenteredText(users[logged_in_index].userAccount.phoneNumber);
	cout << '\n';
	if (users[logged_in_index].frozen) {
		printCenteredText("Your account is blocked");
	}
	else printCenteredText("Your account is not blocked");
}

void displayMovies() {
	cout << "Movies: \t\t" << "Rate: \t\t" << "Price Per Day:\t\t" << "Buying Price: \n";
	for (int i = 0; i < totalnumofmovies; i++)
	{
		cout << i + 1 << ". " << movie[i].name_of_movie << "\t\t " << movie[i].average_rate << "\t\t" << movie[i].price << "\t\t\t" << movie[i].price * 30;
		cout << '\n';
	}
}

void update(movieinfo movie[]) {
	displayMovies();
	int choose, quantity;
	float price;
	while (true)
	{
		while (true) {
			cout << "Enter the number of the movie you want to edit:\n";
			cin >> choose;

			if (cin.fail())
			{
				printCenteredText("Invalid Choice.");
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}
			else
				break;
		}
		if (choose > totalnumofmovies)
		{
			printCenteredText("Please choose a valid movie number.");
			continue;
		}
		else
			break;
	}
	cout << "Add new quantity:\n";
	cin >> quantity;
	movie[choose - 1].Quantity += quantity;
	cout << "Enter new price:\n";
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

char getValidatedChar(string_view sentence)
{

	string choice{};
	while (true)
	{
		printCenteredText(static_cast<string>(sentence));
		getline(cin >> ws, choice);
		if (choice.length() == 1 && isdigit(choice[0]))
			return choice[0];
		else
		{
			printCenteredText("Invalid Choice.");
			continue;
		}
	}
}

int getValidatedDate(string_view sentence)
{
	int input{};
	while(true)
	{
		printCenteredText(static_cast<string>(sentence));
		cin >> input;
		if (cin.fail())
		{
			printCenteredText("Please enter a number.");
			cin.clear();
			cin.ignore(10000, '\n');
			printCenteredText("Please enter the date again correctly:");
			continue;
		}
		else 
			return input;
	}
}

void deleteMovies() {
	displayMovies();
	int choose;
	while (true)
	{

		while (true) {
			cout << "Enter the number of the movie you want to delete\n";
			cin >> choose;

			if (cin.fail())
			{
				printCenteredText("Invalid Choice.");
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}
			else
				break;
		}
		if (choose > totalnumofmovies)
		{
			printCenteredText("Please choose a valid movie number.");
			continue;
		}
		else
			break;
	}
	for (int i = choose-1;i < totalnumofmovies;i++) {
		movie[i] = movie[i + 1];
	}
	totalnumofmovies--;
	printCenteredText("Deleting procces went succesfully!");
};