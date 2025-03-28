#include <iostream>
using namespace  std;
char choice;
void menu() {
	cout << "1.rent a movie \n2.exit";
	cin >> choice;
}
int main() {
	menu();
	cout << "it worked";
	return 0;
}