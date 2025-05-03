#include <iostream>
#include <string>
using namespace std;
const int number_of_movies = 20;
int totalnumofmovies = 0;
struct movieinfo {
	string name_of_movie;
	float price = 0,overdue_price = 0.0;
	int rentingCount = 0;
	int Quantity =0;
	float average_rate = 0;
	int final_score_of_movie = 0;
	int total_ratings = 0;
}movie[number_of_movies];


void addingMovies(int count, movieinfo movie[])
{

	if (totalnumofmovies > number_of_movies) {
		cout << "sorry we have reached the maximum number of movies\n";
		return;
	}
	else {
		for (int i = totalnumofmovies;i < count + totalnumofmovies;i++) {
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
		totalnumofmovies += count;
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
	addingMovies(count, movie);
}
void main()
{
	moviemanagment();
}