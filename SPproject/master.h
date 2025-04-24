#pragma once
#include <string>
#define duedate 7
using namespace std;

//structs and variables!

const int number_of_movies = 20;
//number of days of months if the year is not leap
int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


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

struct user
{
	accountinfo userAccount;
	int age = 0;
	string rentedMovies[10];
	Date rentday ;
	bool frozen = false;
	bool isEmployee = false;
}users[20], Overdue[20];

struct movieinfo {
	string name_of_movie;
	float price = 0;
	int rentingCount = 0;
	int Quantity;
	float average_rate = 0;
	int final_score_of_movie = 0;
	int total_ratings = 0;
}movie[number_of_movies];

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
void loadFromFile(user users[], int totalUsers, int userIndex);
//RentingSystem
bool isLeap(int year);
int dateToDays(Date d);
int daysBetween(Date rentday, Date currentday);
void Overdue_clients();
void ListofDaysLeft();
void Renting();
void MostandLeastRentedMovies();