#include <iostream>
using namespace std;
struct movies {
	string name[100];
	char avlb;
	int count;
};
void rentcount(int count,string m[])
{
	for (int j = 0;j < count; j++)
	{
		movies mv;
		count = 0;
		if (m[j] == mv.name[j])
			count++;

	}
}
void name(int count, string m[])
{
	cout << "Enter the movie name" << '\n';
	for (int i = 0;i < count;i++)
		cin >> m[i];

}
void av(int count ,char avlb, string m[])
{
	movies v;
	for (int i = 0;i < count;i++)
	{
		if (m[i] == v.name[i])
			cout << "This movie is available in our websit" << '\n';
		else
			cout << "this movie is unavailable in our websit" << '\n';
	}
	
}
void moviemanagment(string m[], char avlb, int count)
{
	movies m;
	string names[100];
	char avlb;
	int count = 0;
	cout << "Enter the count of movies you want to rent" << '\n';
	cin >> count;
	name(count, names);
	av(count, avlb, names);
	rentcount(count, names);

}
void main()
{
	
}