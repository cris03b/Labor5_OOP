#include <iostream>
#include <exception>

using namespace std;

class myex {
	/*Eigene Exception class, die ein Exception erstellt*/
public:
	myex() {

	}
	int myexception() {
		//gibt eine Zahl zuruck und erlaubt in dem catch weiterzugehen
		return 20;
	}
};

class Exceptions {
	/*Mehrere Funktionen, die die falschen Eingabedaten verbessert
	zB. ein string in einer int Variable zu lesen*/
public:
	myex except;
public:
	Exceptions() {
	}

	bool LikeExcept(int& likes) {
		//Exception fur Likes
		try {
			//uberpruft ob die Anzahl der Likes ein Integer ist
			cout << "Likes= ";
			cin >> likes;
			if (cin.fail())
				//sonst wirft sie ein Exception
				throw except.myexception();
		}
		catch (...) {
			//sie kommt hier durch die geworfene Exception an und schreibt das auf dem Bildschirm an
			cout << "Oh no...An exception occured...\n";
			return false;
		}
		return true;
	}

	bool YearExcept(int& year) {
		//Exception fur das Jahr
		try {
			//uberpruft ob das Jahr ein Integer ist
			cout << "Year= ";
			cin >> year;
			if (cin.fail())
				//sonst wirft sie ein Exception
				throw except.myexception();
		}
		catch (...) {
			//sie kommt hier durch die geworfene Exception an und schreibt das auf dem Bildschirm an
			cout << "Oh no...An exception occured...\n";
			return false;
		}
		return true;
	}

	bool OptionExcept(int& option) {
		//Exception fur die Option, die man eingibt
		try {
			//uberpruft ob die Option ein Integer ist
			cout << "Your option= ";
			cin >> option;
			if (cin.fail())
				//sonst wirft sie ein Exception
				throw except.myexception();
		}
		catch (int e) {
			//sie kommt hier durch die geworfene Exception an und schreibt das auf dem Bildschirm an
			cout << "Oh no...An exception occured...\n";
			return false;
		}
		return true;
	}
};