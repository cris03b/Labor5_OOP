#include "Domain.cpp"
#include <iostream>
#include <fstream>
#include "MovieInMemoryRepo.h"
using namespace std;

class Repo {
public:
	MovieInMemoryRepo repo;

	Repo() {

	};


	void show_movies() {
		//Zeigt alle Filme, die in der Liste sind
		if (repo.length != 0) {
			//repo.read("admin");
			cout << endl << "Here are all the movies that we have:" << endl;
			for (int i = 0; i < repo.length; i++) {
				cout << "Title: " << repo.movies[i].getTitle() << ", Genre: " << repo.movies[i].getGenre() << \
					", Year: " << repo.movies[i].getYear() << ", Likes: " << repo.movies[i].getLikes() << endl;
			}
		}
		else {
			cout << endl << "There are no movies in the list!";
		}
	}

	void show_watchlist() {
		// wenn die Watchliste nicht leer ist, dann werden wir es durchlufen 
		if (repo.wlen != 0) {
			//repo.read("user");
			cout << endl << "Here are all the movies from your watchlist:" << endl;
			for (int i = 0; i < repo.wlen; i++) {
				cout << "Title: " << repo.watchlist[i].getTitle() << ", Genre: " << repo.watchlist[i].getGenre() << \
					", Year: " << repo.watchlist[i].getYear() << ", Likes: " << repo.watchlist[i].getLikes() << endl;
			}
		}
		else {
			cout << endl << "Wow! You have seen all the movies from your watchlist" << endl << "The watchlist is now empty! Good job! :D" << endl;
		}
	}

	// eine Funktion um die Filme auch als Benutzer und als Admin hinzufugen
	// option = user/admin
	Movie* add_movie(Movie m, string option) {
	
		bool found = false;
		for (int i = 0; i < repo.length; i++) {
			// uberprufen ob der Film in der Datenbank existiert (wir uberprufen auch das Jahr, weil einen Film in verschiedenen Jahren veroffentlich werden kann)
			if (repo.movies[i].getTitle() == m.getTitle() && repo.movies[i].getYear() == m.getYear()) {
				found = true;
			}
		}
		// wenn der Film nicht existiert und wir als Admin arbeiten => den Film in der Datenbank hinzufugen
		if (!found && option == "admin") {
			repo.movies[repo.length] = m;
			repo.length++;
			repo.write("admin");
			cout << "YAY! You just added " << m.getTitle() << " in the list!" << endl;
			return repo.movies;
		}
		// wenn der Film nicht existiert und wir als Benutzer arbeiten => kann der Film nicht in der Watchliste hinzugefugt werden 
		else if (!found && option == "user") {
			cout << "Sorry, the movie doesn't exist :(" << endl;
			return repo.watchlist;
		}
		// wenn der Film existiert und wir als Admin arbeiten => kann der Film nicht in der Datenbank noch einmal hinzugefugt werden 
		else if (found && option == "admin") {
			cout << "Sorry, the movie already exists..." << endl;
			return repo.movies;
		}
		// wenn der Film existiert und wir als Benutzer arbeiten => suchen wir den Film in der Watchliste 
		else if (found && option == "user") {
			bool wfound = false;
			for (int j = 0; j < repo.wlen; j++) {
				if (repo.watchlist[j].getTitle() == m.getTitle() && repo.watchlist[j].getYear() == m.getYear()) {
					wfound = true;
				}
			}
			// wenn wir den Film nicht gefunden haben => wird es hinzugefugt
			if (!wfound) {
				repo.watchlist[repo.wlen] = m;
				repo.wlen++;
				repo.write("user");
				cout << endl << "YAY! You just added " << m.getTitle() << " in your watchlist!" << endl;
			}
			// wenn wird den Film gefunden haben => Nachricht
			else {
				cout << "Oww... it seems like you really like this movie, because you wanted to add it again in your watchlist!" << endl;
			}
			return repo.watchlist;
		}

	}


	Movie* delete_movie_list(string title, int year) {
		//Loscht durch den Administratormode ein Film aus der Liste
		int found = -1;
		//Sucht den Film und speichert die Position
		for (int i = 0; i < repo.length; i++) {
			if (repo.movies[i].getTitle() == title && repo.movies[i].getYear() == year) {
				found = i;
				break;
			}
		}
		//Verschiebt im Vektor und so wird der Film mit dem gegebenen Titel und Jahr geloscht
		if (found != -1) {
			for (int j = found + 1; j < repo.length; j++) {
				repo.movies[j - 1] = repo.movies[j];
			}
			repo.length--;
			repo.write("admin");
			cout << "You just deleted the movie: " << title << " from the list! Hope you are happy..." << endl;
		}
		else {
			cout << "The movie you wanted to delete was not in the list...Try to delete another movie, if you want to." << endl;
		}
		return repo.movies;
	}

	Movie* delete_movie_watchlist(string title, int year) {
		//Loscht ein Film aus der Watchiste des Users
		int found = -1;
		if (repo.wlen == 0) {
			cout << "Your watchlist is empty. Try adding a movie first.";
		}
		else {
			for (int i = 0; i < repo.wlen; i++) {
				if (repo.watchlist[i].getTitle() == title && repo.watchlist[i].getYear() == year) {
					found = i;
					break;
				}
			}
			//Verschiebt im Vektor und so wird der Film mit dem gegebenen Titel und Jahr geloscht
			if (found == -1) {
				cout << "The movie you wanted to delete was not in the list...Try to delete another movie, if you want to." << endl;
			}
			else {
				for (int j = found + 1; j < repo.wlen; j++) {
					repo.watchlist[j - 1] = repo.watchlist[j];
				}
				repo.wlen--;
				repo.write("user");
				found = true;
				cout << "You just deleted the movie: " << title << " from the list! If you liked it, you can support them with a Like . If you didn't, sorry." << endl;
				cout << "Like/Not: ";
				string option;
				cin >> option;
				if (option == "Like") {
					for (int i = 0; i < repo.length; i++) {
						if (repo.movies[i].getTitle() == title && repo.movies[i].getYear() == year) {
							repo.movies[i].setLikes(repo.movies[i].getLikes() + 1);
							cout << "\nThank you for your support!" << endl;
							break;
						}
					}
				}
			}
		}
		return repo.watchlist;
	}

	// option = title/genre/year/likes/trailer
	void edit_movie(string title, int year, string option) {
		bool found = false;
		if (option == "title") {
			// der Film in der Datenbank suchen; wenn wir es gefunden haben => andern wir den Titel mit new_title
			for (int i = 0; i < repo.length; i++) {
				if (repo.movies[i].getTitle() == title && repo.movies[i].getYear() == year) {
					cout << "New title: ";
					string new_title;
					cin.get();
					getline(cin, new_title, '\n');
					repo.movies[i].setTitle(new_title);
					cout << "Great! You just updated the title!" << endl;
					found = true;
				}
			}
			repo.write("admin");
		}

		else if (option == "genre") {
			// der Film in der Datenbank suchen; wenn wir es gefunden haben => andern wir das Genre mit new_genre
			for (int i = 0; i < repo.length; i++) {
				if (repo.movies[i].getTitle() == title && repo.movies[i].getYear() == year) {
					cout << "New genre: ";
					string new_genre;
					cin >> new_genre;
					repo.movies[i].setGenre(new_genre);
					cout << "Great! You just updated the genre!" << endl;
					found = true;
				}
			}
			repo.write("admin");
		}

		else if (option == "year") {
			// der Film in der Datenbank suchen; wenn wir es gefunden haben => andern wir das Jahr mit new_year
			for (int i = 0; i < repo.length; i++) {
				if (repo.movies[i].getTitle() == title && repo.movies[i].getYear() == year) {
					cout << "New year: ";
					int new_year;
					cin >> new_year;
					while (cin.fail()) {
						cout << "Please enter a valid year" << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Year: ";
						cin >> year;
					}
					repo.movies[i].setYear(new_year);
					cout << "Great! You just updated the year!" << endl;
					found = true;
				}
			}
			repo.write("admin");
		}

		else if (option == "likes") {
			// der Film in der Datenbank suchen; wenn wir es gefunden haben => andern wir die Anzahl von Likes mit new_likes
			for (int i = 0; i < repo.length; i++) {
				if (repo.movies[i].getTitle() == title && repo.movies[i].getYear() == year) {
					cout << "New number of likes: ";
					int new_like;
					cin >> new_like;
					repo.movies[i].setLikes(new_like);
					cout << "Great! You just updated the likes!" << endl;
					found = true;
				}
			}
			repo.write("admin");
		}

		else if (option == "trailer") {
			// der Film in der Datenbank suchen; wenn wir es gefunden haben => andern wir den Trailer mit new_trailer
			for (int i = 0; i < repo.length; i++) {
				if (repo.movies[i].getTitle() == title && repo.movies[i].getYear() == year) {
					cout << "New url for trailer: ";
					CString new_trailer;
					// wir lesen den URL als Char
					char myString[256];
					cin >> myString;
					// wir verwandeln dem Char in CString
					new_trailer = CString(myString);
					repo.movies[i].setTrailer(new_trailer);
					cout << "Great! You just updated the url!" << endl;
					found = true;
				}
			}
			repo.write("admin");
		}

		// wenn die Option nicht gultig ist => Nachricht
		else {
			cout << "Sorry, the option is not valid..." << endl;
		}

		if (!found) {
			cout << "The movie is not in the list. Try to edit another movie.";
		}
	}
	
};