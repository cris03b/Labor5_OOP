#include <iostream>
#include "Ausnahmen.cpp"

using namespace std;

class Validation {
public:
	Exceptions valid;

public:
	Validation() {
	}
	void ValidYear(int& year) {
		//Uberpruft ob das Jahr gultig ist = Datenvalidierung
		while (!valid.YearExcept(year) || year < 1800 || year>2020) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "This Year is invalid. Please choose a valid Year.\n";
		}
	}

	void ValidLikes(int& likes) {
		//Uberpruft ob die Likes gultig sind = Datenvalidierung
		while (!valid.LikeExcept(likes) || likes < 0) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "This number of Likes is invalid. Please choose a valid number of Likes.\n";
		}
	}

	void ValidOption(int& option) {
		//Uberpruft ob die Option ein Integer ist = Datenvalidierung
		while (!valid.OptionExcept(option) || option <= 0 || option >= 7) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "This Option is invalid. Please choose a valid option.\n";
		}
	}

	int ValidMode(string mode) {
		if (mode == "user" || mode == "User") {
			return 1;
		}
		if (mode == "Admin" || mode == "admin") {
			return 2;
		}
		return 0;
	}
	void ValidFormat(string& format) {
		//Uberpruft ob das Jahr gultig ist = Datenvalidierung
		while (format != "HTML" && format != "html" && format != "Html" && format != "csv" && format != "CSV" && format != "Csv") {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "This Format is invalid. Please choose between html and csv.\n";
			cout << "Format: ";
			cin >> format;
		}
	}
};