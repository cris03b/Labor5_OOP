// lab5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <Windows.h>
#include <atlstr.h>
#include <sstream>
#include <string>
#include <cassert>
#include "Validation.cpp"
#include "MovieInMemoryRepo.h"
//#include "HTML.cpp"
#include "Tests.cpp"
#include "CSV.cpp"

using namespace std;


void savefile(string format, string& filename) {
	string newExt; //new extension
	HTML h;
	Controller cont;
	if (format == "html" || format == "HTML" || format == "Html") {
		//wir verandern das Format
		//htm, nicht html, weil in Visual Studio die Extension so heisst
		newExt = "htm";
		//wir finden die vorige Extension
		string::size_type i = filename.rfind('.', filename.length());
		if (i != string::npos) {
			filename.replace(i + 1, newExt.length(), newExt);
		}
		h.maketablehtml(cont.repository.repo.watchlist, cont.repository.repo.wlen, filename);
	}
}

int main()
{
	//Tests t;
	//t.Teste(); merg testele, doar ca afiseaza mesaje pe ecran de la functiile respective
	Controller cont;
	cont.repository.repo.read("admin");
	cont.repository.repo.read("user");
	CString url;
	string mode, genre, title;
	int option, year, likes;
	Validation ok;
	string format;
	cout << "WELCOME! \n";
	cout << endl << "Bored in the house? Well now you're in the right place! Let's get it started!" << endl << "You can..." << endl;

	while (true) {
		cout << "\nChoose a mode:" << endl << "User/Admin: ";
		cin >> mode;
		if (ok.ValidMode(mode) == 1) {
			cout << endl << "You entered the User mode" << endl;
			cout << "Choose a format to see your watchlist (html or csv)\nFormat: ";
			cin >> format;
			ok.ValidFormat(format);
			string filename = "watchlistfile.txt";
			savefile(format, filename);
			while (true) {
				cout << endl << "1. Search movies by genre and add some in your watchlist" << endl << \
					"2. Delete the movie you already saw" << endl << \
					"3. See your watchlist" << endl << \
					"4. See all movies" << endl << \
					"5. Back" << endl << \
					"6. Exit\n";
				ok.ValidOption(option);
				if (option == 1) {
					cout << endl << "Search movies" << endl << "Some ideas for genre: SF, comedy, drama, action, mystery, thriller..." << endl << \
						"Hint: If you didn't think of a specific genre, just type '?', and you'll see the entire list of movies" << endl;
					cout << "Genre: ";
					cin >> genre;
					cont.find_movie(genre);
				}
				else if (option == 2) {
					cout << endl << "Delete movies" << endl << \
						"Hint: If you watched the movie and want to delete it from the watchlist, just type its name and year" << endl;
					cout << "Title: ";
					cin.get();
					getline(cin, title, '\n');
					ok.ValidYear(year);
					cont.repository.delete_movie_watchlist(title, year);
				}
				else if (option == 3) {
					cout << endl << "Your watchlist:" << endl;
					if (format == "html") {
						//wenn der Format html ist, wird die Liste in html geoffnet
						HTML h;
						h.executehtml(cont.repository.repo.watchlist, cont.repository.repo.wlen);
					}
					else if (format == "csv") {
						CSV csv;
						csv.csv_file(cont.repository.repo.watchlist, cont.repository.repo.wlen);
						cout << endl << "A csv file with the name \"\Watchlist.csv\"\ was created. You can search it in your folder and see your watchlist!" << endl;
					}
				}
				else if (option == 4) {
					cout << endl << "All movies:" << endl;
					cont.repository.show_movies();
					cout << endl;
				}
				else if (option == 5) {
					cout << "\nYou want to switch the mode from user to administrator.\nNow you can choose again!\n";
					break;
				}
				else if (option == 6) {
					cout << endl << "So you're not bored anymore, great! We'll see you next time!" << endl;
					return 0;
				}
			}
		}

		else if (ok.ValidMode(mode) == 2) {
			cout << endl << "You entered the Administrator mode" << endl;
			while (true) {
				cout << endl << "1. Add a new movie to the movielist" << endl << \
					"2. Delete a movie from the movielist" << endl << \
					"3. Edit a movie" << endl << \
					"4. See the movielist" << endl << \
					"5. Back" << endl << \
					"6. Exit\n";
				ok.ValidOption(option);
				if (option == 1) {
					cout << endl << "Add a movie";
					cout << "\nTitle: ";
					cin.get();
					getline(cin, title, '\n');
					cout << "Genre: ";
					cin >> genre;
					ok.ValidYear(year);
					ok.ValidLikes(likes);
					cout << "Trailer: ";
					char myString[256];
					cin >> myString;
					url = CString(myString);
					Movie m(title, genre, year, likes, url);
					cont.repository.add_movie(m, "admin");
				}
				else if (option == 2) {
					cout << endl << "Delete movies" << endl << \
						"Hint: If you don't like the movie, you can delete it." << endl;
					cout << "Title: ";
					cin.get();
					getline(cin, title, '\n');
					ok.ValidYear(year);
					cont.repository.delete_movie_list(title, year);
				}
				else if (option == 3) {
					string edit_opt;
					cout << endl << "Edit movies" << endl << \
						"You can choose between these edit options: title, genre, year, likes, trailer" << endl;
					cout << "Title: ";
					cin.get();
					getline(cin, title, '\n');
					ok.ValidYear(year);
					cout << "Edit option: ";
					cin >> edit_opt;
					cont.repository.edit_movie(title, year, edit_opt);
				}
				else if (option == 4) {
					cout << endl << "Your Movielist:" << endl;
					cont.repository.show_movies();
					cout << endl;
				}
				else if (option == 5) {
					cout << "\nYou want to switch the mode from administrator to user.\nNow you can choose again!\n";
					break;
				}
				else if (option == 6) {
					cout << endl << "So you're not bored anymore, great! We'll see you next time!" << endl;
					return 0;
				}
			}
		}
		else {
			cout << "Please choose a valid mode" << endl;
		}
	}
	return 0;
}


/*int main() {
	//MovieInMemoryRepo repo;
	//repo.read();
	Repo repo;
	string title, genre;
	CString url;
	int year, likes;
	cout << "\nTitle: ";
	cin.get();
	getline(cin, title, '\n');
	cout << "Genre: ";
	cin >> genre;
	cout << endl << "year: ";
	cin >> year;
	cout << endl << "likes: ";
	cin >> likes;
	cout << "Trailer: ";
	char myString[256];
	cin >> myString;
	url = CString(myString);
	Movie m(title, genre, year, likes, url);
	repo.add_movie(m, "admin");
	repo.show_movies();
	repo.add_movie(m, "user");
	repo.show_watchlist();
	return 0;
}*/