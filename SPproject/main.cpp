#include<iostream>
#define duedate 7
using namespace std;


struct Date {
	int day;
	int month;
	int year;
}currentday;


struct CLIENT {
	char name[50];
	int ID;
	string email;
	int telephone_number;
	Date rentday;

}client[20], Overdue[20];

struct MOVIES {
	char name[50];
	int ID;
	int Quantity;

}movie[10];


//number of days of months if the year is not leap
int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

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
	for (int i = 0, int j = 0; i < 20; i++) {
		int Number_of_days = daysBetween(client[i].rentday, currentday);
		cout << "Number of days: " << Number_of_days << endl;

		if (Number_of_days > duedate) {
			Overdue[j] = client[i];
			j++;
		}
	};
}

//if user want to rent movie (renting function)
void Renting() {
	int num;
	cout << "            PLEASE CHOOSE MOVIE THAT YOU WANT TO RENT               ";
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << ". " << movie[i].name;
	}
	cout << "Enter a number of movie you want: ";
	cin >> num;
	if (num < 1 || num>10) {
		cout << "Invalid number!!!\n";
	}
	else {
		for (int i = 0; i < 10; i++) {
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

int main() {


	return 0;
}
