#pragma once
#include <string>
using namespace std;

//structs and variables
const int number_of_movies = 20;
struct accountinfo
{
	string username;
	string email;
	string password;
	int movieNumber = 0;
	int accountNumber = 0;
};

struct user
{
	accountinfo userAccount;
	int age = 0;
	string phoneNumber;
	string rentedMovies[10];
	bool frozen = false;
	bool isEmployee = false;
};

struct movieinfo {
	string name_of_movie;
	float price = 0;
	int rentingCount = 0;
	float average_rate = 0;
	int final_score_of_movie = 0;
	int total_ratings = 0;
}movie[number_of_movies];

//functions
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