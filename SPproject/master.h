#pragma once
#include <string>
using namespace std;

//Variables!
const int duedate = 7;
const int number_of_movies = 20;
int totalnumofmovies = 0;
int logged_in_index = -1;
//number of days of months if the year is not leap
int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

//Stucts
struct Date {
	int day;
	int month;
	int year;
}currentday;

struct accountinfo
{
	string username;
	string email;
	string password;
	string phoneNumber;
	int movieNumber = 0;
	int accountNumber = 0;
};

struct movieinfo {
	string name_of_movie;
	Date rentday,currentday;
	float price = 0;
	float overdue_price = 0;
	int rentingCount = 0;
	int Quantity;
	float average_rate = 0;
	int final_score_of_movie = 0;
	int total_ratings = 0;
}movie[number_of_movies];

struct user
{
	accountinfo userAccount;
	int age = 0;
	string rentedMovies[10];
	Date rentday, currentday;
	bool frozen = false;
	bool isEmployee = false;
	movieinfo usersmovie[number_of_movies];
}users[20], Overdue[20];



//functions
//sign in/up
char customermenu();
char employeermenu();
bool findemail(string email, user users[], int& totalusers);
bool findphonenumber(string phonenum, user users[], int& totalusers);
bool findaccountnum(int accountnum, user users[], int& totalusers);
bool findtrueinfo(string email, string password, user users[], int& totalusers);
int signin(user users[], int totalusers);
bool signup(user& temp, user users[], int& totalusers);
void movierate(movieinfo movies[]);
void outputToFile(user users[], int totalUsers);
void loadFromFile(user users[]);
int getNumberOfUsersFromFile();

//Renting and ReturnSystems
bool isLeap(int year);
int dateToDays(Date d);
int daysBetween(Date rentday, Date currentday);
void Overdue_clients();
void ListofDaysLeft();
void Renting();
void sortMoviesByCount();
int Days_Between(Date Return_Date, Date Due_Day);
double rental_fees(int total_days, float price_of_day, int overdue_days, int overdue_value);

void availability(int count);
void rentcount(int count);
void name(int count);
void moviemanagment();

//display
void displayCustomers();
void displayMovies();

void addingMovies(int count);
void moviemanagment();

double rental_fees(int total_days, float price_of_day, int overdue_days, int overdue_value);
void returnfees();

void Rentday(int index);
void Currentday(int index);