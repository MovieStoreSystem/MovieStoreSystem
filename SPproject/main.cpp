#include <iostream>
using namespace std;
struct movieinfo {
	string name_of_movie;
	float price = 0;
	int rentingCount = 0;
	int Quantity;
	float average_rate = 0;
	int final_score_of_movie = 0;
	int total_ratings = 0;
}movie;
void name(int count  )
{
	cout << "Enter the movie name" << '\n';
	for (int i = 0;i < count;i++)
		cin >> movie.name_of_movie[i];

}
void addcount(int count)
{
	for (int i = 0;i < count;i++)
	{
		cout << "Enter the count of the movie" << '\n';
		cin >> movie.Quantity;
	}
}
void moviemanagment(int count)
{
	cout << "Enter the count of movies you want to input" << '\n';
	cin >> count;
	name(count);
	addcount(count);
}
void main()
{
	
}