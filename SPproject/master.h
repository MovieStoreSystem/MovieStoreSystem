#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
namespace platform
{
	void wait(int miliseconds)
	{
		Sleep(miliseconds);
	}
}


#include <string>
using namespace std;

//Variables!
const int duedate = 7;
const int number_of_movies = 20;
const int nCharactersToFillUpConsole{ 156 };
int totalnumofmovies = 0;
int logged_in_index = 50;
//number of days of months if the year is not leap
int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

//Stucts
struct Date {
	int day;
	int month;
	int year;
}currentday,returnday;

struct accountinfo
{
	string username;
	string email;
	string password;
	string phoneNumber;
	int accountNumber{0};
	//rentedMOVIE_INFO rented[number_of_movies];
	//int movieNumber[number_of_movies]; 
};

struct movieinfo {
	string name_of_movie;
	float price = 0.0f;
	int rentingCount = 0;
	int Quantity = 0;
	float average_rate = 0.0f;
	float final_score_of_movie=0.0f;
	int total_ratings = 0;
} movie[number_of_movies];

struct RentedMovieInfo
{
	string nameOfRentedMovie;
	Date rentDay;
};

struct RentedMovies {
	RentedMovieInfo rentedMovies[number_of_movies];
	int nMovies = 0;
	
};

struct BoughtMovies {
	string name_of_bought_movies[number_of_movies];
	int nBoughtMovies = 0;
};

struct RatedMovies {
	string ratedMoviesNames[number_of_movies];
	int nRatedMovies = 0;
};

struct user
{
	accountinfo userAccount;
	int age = 0;
	bool isEmployee = false;
	bool frozen = false;
	RentedMovies userRentals;
	BoughtMovies userBought;
	RatedMovies rating;
}users[20], Overdue[20];



//functions

//Menu
char customermenu();
char employeermenu();
//Finding true identity
bool findemail(string email, user users[], int& totalusers);
bool findphonenumber(string phonenum, user users[], int& totalusers);
//Sign in/up
int signin(user users[], int totalusers);
bool signup(user& temp, user users[], int& totalusers);
//Bonus movie rating
void movierate();
void Display_High_Rated_Movies();
void Buy_A_Movie();
void ViewAccountInfo();

//using files to save data
void outputToFile(user users[], int totalUsers);
void loadFromFile(user users[]);
int getNumberOfUsersFromFile();
//checking input
char getValidatedChar(string_view string);
int getValidatedDate(string_view sentence);
int findMovieIndexByName(string_view movieName);
//Layout
void printCenteredText(string coutText, int width = nCharactersToFillUpConsole);

//Renting movies and specifying dates
bool isLeap(int year);
int dateToDays(Date d);
int daysBetween(Date rentday, Date currentday);
void Overdue_clients();
void ListofDaysLeft();
void Renting();
void sortMoviesByCount();
void Rentday(int index);
void Currentday();

// to display info 
void displayCustomers(int totalusers);
void displayMovies();
void BoughtandRentedMovies();

void addingMovies(int count);
void moviemanagment();

//return and calculating the price
void Calculate_totalPrice();

// to change movie info
void update(movieinfo movie[]);
void deleteMovies();




