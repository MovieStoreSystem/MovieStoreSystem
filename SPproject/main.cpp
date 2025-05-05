#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
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
void addingMovies(int count)
{
	bool found = true;
	if (totalnumofmovies > number_of_movies) {
		cout << "sorry we have reached the maximum number of movies\n";
		return;
	}
	else {
		for (int i = 0;i < count;i++) {
			found = true;
			cout << "Enter the movie name:\n";
			cin.ignore();
			getline(cin, movie[totalnumofmovies].name_of_movie);
			
			for (int j = 0;j < totalnumofmovies;j++) {
				if (movie[totalnumofmovies].name_of_movie == movie[j].name_of_movie) {
					found = false;
				}
			}
			if (!found) {
				cout << "This Movie already exist\n";
				count++;
			}
			else {
				while (true) {
					cout << "Enter the price of the movie for a day:\n";
					cin >> movie[totalnumofmovies].price;

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
				while (true) {

					cout << "Enter the quantity of the movie\n";
					cin >> movie[totalnumofmovies].Quantity;

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

				totalnumofmovies++;
				if (totalnumofmovies == number_of_movies) {
					cout << "sorry we have reached the maximum number of movies\n";
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
void main()
{
	moviemanagment();
}