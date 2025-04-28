#include "master.h"
#include<iostream>
using namespace std;

bool isLeap(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int dateToDays(Date date) {
	int nDays = date.year * 365 + date.day;

	// نضيف الأيام بتاعت الشهور اللي فاتت في نفس السنة
	for (int i = 0; i < d.month - 1; ++i) {
		nDays += daysInMonth[i];
	}

	// لو السنة كبيسة و الشهر بعد فبراير، نضيف يوم
	if (date.month > 2 && isLeap(date.year))
		nDays += 1;

	// نضيف عدد السنوات الكبيسة اللي فاتت
	nDays += (date.year / 4) - (date.year / 100) + (date.year / 400);

	return nDays;
}
int daysBetween(Date rentday, Date currentday) {
	return abs(dateToDays(currentday) - dateToDays(rentday));
}
void Overdue_clients() {
	for (int i = 0, int j = 0; i < 20; i++) {
		int Number_of_days = daysBetween(users[i].rentday, currentday);
		cout << "Number of days: " << Number_of_days << endl;

		if (Number_of_days > duedate) {
			Overdue[j] = users[i];
			users[i].frozen = true;
			cout << users[i].userAccount.accountNumber << "." << users[i].userAccount.username << "\n";
			j++;
		}
	};
}
void Renting() {
	int num;
	cout << "            PLEASE CHOOSE MOVIE THAT YOU WANT TO RENT               ";
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
					cout << "                   rented successfully                  \n";
				}
			}
		}
	}
}

//SARA
void availability(int count)
{
	for (int i = 0;i < count;i++) {
		int amount = 0;
		cout << "Enter the quantity of " << movie[totalnumofmovies].name_of_movie << " you want to add";
		cin >> amount;
		movie[totalnumofmovies].Quantity += amount;
	}

}
void rentcount(int count)
{
	for (int j = 0;j < count; j++)
	{
		count = 0;
		cout << "Enter the amount of " << movie[totalnumofmovies].Quantity;
		cin >> count;
		movie[totalnumofmovies].Quantity += count;
		totalnumofmovies++
	}
}
void name(int count)
{
	for (int i = 0;i < count;i++) {
		cout << "Enter the movie name of movie number " << totalnumofmovies + 1 << "\n";
		cin.ignore();
		getline(cin, movie[i].name_of_movie);
	}
}
void moviemanagment()
{
	// movie[number_of_movies] globlal variable
	// string names[100]; names of movies are already included in the struct
	// char avlb; i don't see why we need it

	int count = 0;
	cout << "Enter the count of movies you want to add" << '\n';
	cin >> count;
	name(count); // to add the movie names
	av(count); // to add the quantities of each movie;
	rentcount(count, names);
	totalnumofmovies += count;
	if (totalnumofmovies <= 20)
		cout << "We have reached the maximum amount of movies\n";
}
void addingMovies(int count)
{
	for (int i = 0;i < count;i++) {
		cout << "Enter the movie name\n";
		cin >> movie.name_of_movie[totalnumofmovies];
		totalnumofmovies++;
	}
}
void addcount(int count)
{
	for (int i = 0;i < count;i++)
	{
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
	name(count);
	addcount(count);
}
//Nejar
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
		cout << i + 1 << "." << movie[i].names_of_movies;
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







void deleteMovie(movieinfo movies[], int number_of_movies, movieinfo y.Quantity, movieinfo y.name_of_movie) {
	bool insystem = false;
	for (int i = 0; i < number_of_movies; i++) {
		if (movies[i] == y.name_of_movie) {
			insystem = true;
			movies[i] == 0;
			number_of_movies--;
			cout << "Deleting process was successful\n";
		}
		else {
			insystem = false;
			cout << "The selected movie isn't found\n";
		}
	}
}
int main()
{
	
}

//shrouk
void Calculate_totalPrice() {
	int Nom_of_days;
	float TotalPrice = 0;
	bool found{ false };
	string tempNameOfMovie;
	cout << "Enter the name of movie you want to return\n";
	cin >> tempNameOfMovie;
	for (int j = 0; j < users[logged_in_index].userRentals.nMovies; j++) {
		for (int k = 0; k < number_of_movies; k++) { // for every movie
			if (users[logged_in_index].userRentals.rentedMovies[j].nameOfRentedMovie == tempNameOfMovie) {
				if (users[logged_in_index].userRentals.rentedMovies[j].rentDay.day == 0 &&
					users[logged_in_index].userRentals.rentedMovies[j].rentDay.month == 0 &&
					users[logged_in_index].userRentals.rentedMovies[j].rentDay.year == 0) {
					cout << "You haven't rented the movie yet\n";
					return;
				}
				else {
					found = true;
					Currentday();
					Nom_of_days = daysBetween(users[logged_in_index].userRentals.rentedMovies[j].rentDay, currentday);

					if (Nom_of_days <= duedate) {
						TotalPrice = movie[k].price * Nom_of_days;
						cout << "You have to pay: " << TotalPrice << " Pounds.\n";
						movie[k].Quantity++;
						TotalPrice = 0;
						users[logged_in_index].userRentals.rentedMovies[j].rentDay = { 0 };
						return;
					}
					else
					{

						TotalPrice = movie[k].price + ((Nom_of_days - 7) * (0.05 * movie[k].price));
						cout << "You have delayed to return the movie for " << (Nom_of_days - 7) << "days.\n"
							<< "You have to pay: " << TotalPrice << "Pounds.\n"
							<< "\t\tNOTE:You have to pay 5% of the movie price for each day you have delayed.\n";
						movie[k].Quantity++;
						TotalPrice = 0;
						users[logged_in_index].userRentals.rentedMovies[j].rentDay = { 0 };
						return;
					}
					break;

				}
			}
			if (found) break;
		}
		if (!found)
			cout << "User hasn't rented any movies.";
	}

}
if (ch != 'n') {
	cout << "Do you want to continue(y/n)\n";
	cin >> ch;
}