//Rikako Yamada 1665648
//Mark Chaves 1724560
//Mai Ra 1570598

#include <cctype>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

#include <ctime>
#include <cstdlib>
#include "AssociativeArray.h"
#include "StaticArray.h"

class food {
public:
	virtual string getType() {
		return type;

	}
	virtual double getPrice() {
		return price;
	}
protected:
	string type;
	double price;
};

class popcorn : public food {
public:
	popcorn(int p) {
		price = p;
		type = "popcorn";
	}


private:

};

class soda : public food {
public:
	soda(int p) {
		price = p;
		type = "soda";
	}
private:


};

class candybar : public food {
public:
	candybar() {
		price = 3;
		type = "Candybar";
	}
};

class nachos : public food {
public:
	nachos() { price = 10; type = "Nachos"; }
};

class hotdog : public food {
public:
	hotdog() {
		price = 5;
		type = "Hotdog";
	}
};

struct movie
{
	string title;
	AssociativeArray<string, StaticArray<int, 5>> showtimes;
};

int main()
{
	cout << "Programmers: Rikako, Mark, Mai\n";
	cout << "File: " << __FILE__ << endl;

	srand(time(0)); rand();

	AssociativeArray<string, AssociativeArray<string, AssociativeArray<char, AssociativeArray<int, bool>>>> seatInfo;
	AssociativeArray<string, AssociativeArray<string, StaticArray<string, 5>>> movieInfo;
	int ticketPrice = 12;
	string line, title, time, date, showtime;
	string movieTime;
	int random;
	int count = 0;
	char choiceLetter = 'A';
	int timeIndex;
	string dateIndex;

	ifstream fin;
	fin.open("Text.txt");
	

	//parse the file
	while (fin.good()) {
		getline(fin, title, '\t');
		getline(fin, date, '\t');
		getline(fin, time);
		movieInfo[title][date][count] = time;
		showtime = date + " " + time;
		for (int i = 65; i < 75; i++)
			for (int j = 1; j < 11; j++)
				seatInfo[title][showtime][i][j] = false;
		if (count == 4) count = 0;
		else count++;
	}

	queue<string> movies = movieInfo.Keys();

	cout << "Select a movie from the list: " << endl;
	while (!movies.empty())
	{
		if (movies.front() != "") {
			if (count % 2 == 0) cout << endl;
			cout << setw(25) << movies.front();
			count++;
		}
		movies.pop();
	}
	cout << endl;

	//prompt user
	cout << "\n--> ";
	getline(cin, title);

	queue<string> dateKeys = movieInfo[title].Keys(); //date keys
	StaticArray<string, 3> temp;
	int i = 0;
	while(!dateKeys.empty()) {
		if(dateKeys.front() != "")
			temp[i++] = dateKeys.front();
		dateKeys.pop();
	}

	string movieDate;
	cout << "\nSelect date: " << endl;
	for(i = 2; i >= 0; i--){
			cout << setw(10) << "(" << choiceLetter << ") " << temp[i] << " | ";
			count++;
			choiceLetter++;
	}
	cout << endl;

	string a, b, c;
	count = 0;
	getline(cin, date);
	date = toupper(date[0]);
	
	choiceLetter = 'A';
	if (date == "A") {
		cout << "Select a showtime: \n";
		for (i = 0; i < 5; i++) {
			cout << "(" << choiceLetter << ") " << movieInfo[title][temp[0]][i] << "\t";
			choiceLetter++;
			dateIndex = temp[0];
		}
		
	}

	else if (date == "B") {
		cout << "Select a showtime: \n";
		for (i = 0; i < 5; i++) {
			cout << "(" << choiceLetter << ") " << movieInfo[title][temp[1]][i] << "\t";
			choiceLetter++;
			dateIndex = temp[1];
		}
	}

	else if (date == "C") {
		cout << "Select a showtime: \n";
		for (i = 0; i < 5; i++) {
			cout << "(" << choiceLetter << ") " << movieInfo[title][temp[2]][i] << "\t";
			choiceLetter++;
			dateIndex = temp[2];
		}
	}
	
	cout << "\nEnter a showtime:";
	getline(cin, showtime);
	
	showtime = toupper(showtime[0]);
	if (showtime == "A") timeIndex = 0;
	else if (showtime == "B") timeIndex = 1;
	else if (showtime == "C") timeIndex = 2;
	else if (showtime == "D") timeIndex = 3;
	else if (showtime == "E") timeIndex = 4;

	movieTime = movieInfo[title][dateIndex][timeIndex];

	for (int i = 0; i < 25; i++) {
		seatInfo[title][showtime][rand() % 10 + 65][rand() % 10 + 1] = true;
	}

	int row = 10;
	int seats = 10;
	char letter = 'A';
	int num = 1;
	int seatNumber = 1;
	int rowLetter = 'A';

	cout << "  ";
	for (int k = 0; k < seats; k++) {
		cout << num << " ";
		num++;
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		cout << letter << " ";
		for (int j = 0; j < seats; j++) {
			if (seatInfo[title][showtime][letter][j]) {
				cout << "X" << " ";
			}
			else {
				cout << "*" << " ";
			}
		
		}	letter++;
			cout << endl;
	}
	cout << endl;

	int tickets;
	cout << "Enter the number of tickets: ";
	cin >> tickets;
	cin.ignore(1000, '\n');
	cout << endl;
	//let the user pick seats
	string seat;
	string seatLetter, seatNum;
	vector<string> seatArr;
	bool set = false;
	for (int i = 0; i < tickets; i++) {
		cout << "Select seat [ex. A 1]: ";
		getline(cin, seatLetter, ' ');
		getline(cin, seatNum);
		while (seatInfo[title][showtime][seatLetter[0]][stoi(seatNum) - 1]){
		cout << "This seat is taken. Select a new seat: ";
		getline(cin, seatLetter, ' ');
		getline(cin, seatNum);
		}
		seatInfo[title][showtime][seatLetter[0]][stoi(seatNum) - 1] = true;
		seatArr.push_back(seatLetter + seatNum);

	}
	cout << endl;

	//food
	int totalPrice = 0;
	vector<food*> food;
	const int SMALL_POPCORN = 5;
	const int MED_POPCORN = 6;
	const int LARGE_POPCORN = 7;
	const int SMALL_SODA = 3;
	const int MED_SODA = 4;
	const int LARGE_SODA = 5;

	string answer = "";
	string size;

	cout << "Enter any food you would like to order or type q to quit." << endl;
	cout << "Popcorn Small $5.00 Medium $6.00 Large $7.00\nSoda Small $3.00 Medium $4.00 Large $5.00\nCandybar $3.00\nNachos $10.00\nHotdog $5.00\n";
	getline(cin, answer);
	cout << endl;
	while (answer != "q" && answer != "Q") {

		if (answer == "Popcorn" || answer == "popcorn") {
			cout << "Would you like Small Medium or Large?" << endl;
			getline(cin, size);
			if (size == "Small" || size == "small") {
				food.push_back(new popcorn(SMALL_POPCORN));
			}
			else if (size == "Medium" || size == "medium") {
				food.push_back(new popcorn(MED_POPCORN));
			}
			else if (size == "Large" || size == "large") {
				food.push_back(new popcorn(LARGE_POPCORN));
			}

		}

		else if (answer == "Soda" || answer == "soda") {
			cout << "Would you like Small Medium or Large?" << endl;
			getline(cin, size);
			if (size == "Small" || size == "small") {
				food.push_back(new soda(SMALL_SODA));
			}
			else if (size == "Medium" || size == "medium") {
				food.push_back(new soda(MED_SODA));
			}
			else if (size == "Large" || size == "large") {
				food.push_back(new soda(LARGE_SODA));
			}

		}
		else if (answer == "Candybar" || answer == "candybar") {
			food.push_back(new candybar);
		}
		else if (answer == "Nachos" || answer == "nachos") {
			food.push_back(new nachos);
		}
		else if (answer == "Hotdog" || answer == "hotdog") {
			food.push_back(new hotdog);
		}
		else {
			cout << "Invalid response. Please enter your answer again." << endl << endl;
		}
		cout << endl;
		cout << "Anything else? [q/Q to quit]" << endl;
		getline(cin, answer);
	}

	cout << endl;
	//display everything
	cout << "You selected \"" << title << "\"" << " on " << dateIndex << " at " << movieTime << ". \n";
	
		cout << "Your seats are ";
		for (int i = 0; i < tickets; i++)
			cout << seatArr[i] << " ";

	cout << endl;

	cout << "Here is your total bill: " << endl;
	for (int i = 0; i < food.size(); i++) {
		cout << food.at(i)->getType() << " " << fixed << setprecision(2) << "$" << food.at(i)->getPrice() << endl;
		totalPrice += food.at(i)->getPrice();
	}

	cout << tickets << " ticket(s) X $" << ticketPrice << endl;
	totalPrice = totalPrice + tickets * ticketPrice;
	cout << "__________________________\nTotal Price: " << "$" << totalPrice << endl;
	cout << endl;



	system("pause");
}
