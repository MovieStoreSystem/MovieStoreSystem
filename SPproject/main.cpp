#include "master.h"
#include<iostream>
using namespace std;



//function Is the year leap or not?
bool isLeap(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// دالة بتحوّل التاريخ لعدد الأيام 
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

// نحسب الفرق بين تاريخين
int daysBetween(Date rentday, Date currentday) {
	return abs(dateToDays(currentday) - dateToDays(rentday));
}

//function list of overdue clients
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

//if user want to rent movie (renting function)
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


// Nejar 

int Days_Between(Date Return_Date, Date Due_Day)
{
	return (Date_to_days(Due_Day) - Date_to_days(Return_Date));
}
int DaysBetween(Date Rent_Day, Date Due_Day)
{
	return  (Date_to_days(Due_Day) - Date_to_days(Rent_Day));
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
int main()
{
	Date Rent_Day = { 1, 1, 2024 };
	Date Due_Day = { 23, 4, 2025 };
	Date Return_Date = { 23,5,2025 };
	int overdue_days;
	int Total_Days;
	int price_day, overdue_value;
	cout << "Enter the price of the day: ";
	cin >> price_day;
	cout << "Enter the overdue value: ";
	cin >> overdue_value;
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

	double Total_fees = rental_fees(Total_Days, price_day, overdue_days, overdue_value);
	cout << "Total fees are: " << Total_fees;
	return 0;
}

