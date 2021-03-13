#include "Repository.cpp"
#include <string>
#include <Windows.h>
#include <atlstr.h>

class Controller {
public:
	Repo repository;
	Controller() {

	}

	void find_movie(string genre) {
		// uberprufen ob das Genre gultig ist
		bool found = false;
		for (int j = 0; j < repository.repo.length; j++) {
			if (genre == repository.repo.movies[j].getGenre()) {
				found = true;
				break;
			}
		}
		// wenn das Genre in der Datenbank existiert => werden alle Filme mit diesem Genre gezeigt
		if (found) {
			cout << endl << "Here are the movies with that specific genre:";
			for (int i = 0; i < repository.repo.length; i++) {
				if (repository.repo.movies[i].getGenre() == genre) {
					cout << endl << "Title: " << repository.repo.movies[i].getTitle() << ", Genre: " << repository.repo.movies[i].getGenre() <<\
						", Year: " << repository.repo.movies[i].getYear() << ", Likes: " << repository.repo.movies[i].getLikes() << endl;
					// wir benutzen ShellExecute um den Link zu offnen
					ShellExecute(0, 0, repository.repo.movies[i].getTrailer(), 0, 0, SW_SHOW);
					cout << endl << "So... Did you find that movie interesting?" << endl << \
						"If you did, hurry up before you don't forget its title! Add it to your watchlist! :D" << endl \
						<< "If not, don't worry. You'll find one you like, keep searching!" << endl;
					cout << endl << "Your choice" << endl << "Add/Continue/Exit: ";
					string choice;
					cin >> choice;
					// wenn der Benutzer den Film hinzufugen mochtet, schreibt er: "Add" 
					if (choice == "Add") {
						repository.add_movie(repository.repo.movies[i], "user");
					}
					// wenn er "Exit" oder etw. anderes (aber nicht "Continue") schreibt => break
					else if (choice != "Continue") {
						break;
					}
				}
			}
			cout << endl << "That's all we have for you today, hope you found something you like!" << endl << "Come back later for new movies!" << endl;
		}

		// wenn die Benutzer ein Fragezeichnen schreibt, werden alle Filme gezeigt
		else if (genre == "?") {
			cout << endl << "Here are all the movies that we have:" << endl;
			for (int i = 0; i < repository.repo.length; i++) {
				cout << endl << "Title: " << repository.repo.movies[i].getTitle() << ", Genre: " << repository.repo.movies[i].getGenre() << \
					", Year: " << repository.repo.movies[i].getYear() << ", Likes: " << repository.repo.movies[i].getLikes() << endl;
				// wir benutzen ShellExecute um den Link zu offnen
				ShellExecute(0, 0, repository.repo.movies[i].getTrailer(), 0, 0, SW_SHOW);
				cout << endl << "So... Did you find that movie interesting?" << endl << \
					"If you did, hurry up before you don't forget the title! Add it to your watchlist! :D" << endl \
					<< "If not, don't worry. You'll find one you like, keep searching!" << endl;
				cout << endl << "Your choice" << endl << "Add/Continue/Exit: ";
				string choice;
				cin >> choice;
				// wenn der Benutzer den Film hinzufugen mochtet, schreibt er: "Add" 
				if (choice == "Add") {
					repository.add_movie(repository.repo.movies[i], "user");
				}
				// wenn er "Exit" oder etw. anderes (aber nicht "Continue") schreibt => break
				else if (choice != "Continue") {
					break;
				}
			}
			cout << endl << "That's all we have for you today, hope you found something you like!" << endl << "Come back later for new movies!" << endl;
		}

		//wenn das Genre nicht gultig ist => Nachricht
		else if (!found) {
			cout << endl << "Sorry, we don't have that movie genre :(" << endl;
		}
	}
};
