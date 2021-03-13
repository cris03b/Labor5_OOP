#include "MovieInMemoryRepo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

//mode = admin/user
//if admin => read data from movie.txt
//if user => read data from watchlist.txt
void MovieInMemoryRepo::read(string mode) {
	fstream f;
	char cstring[256];
	CString word;
	char x;
	if (mode == "admin") {
		f.open("movies.txt", ios::in);
		int field_count = 0, movie_counter = 0;
		Movie movie;
		while (!f.eof()) {

			x = f.get();
			while (x != ',' && x != '\n' && !f.eof()) {
				word += x;
				x = f.get();
			}

			if (x == ',') {
				if (field_count == 0) {
					string str(CW2A(word.GetString()));
					movie.setTitle(str);
				}
				else if (field_count == 1) {
					string str(CW2A(word.GetString()));
					movie.setGenre(str);
				}
				else if (field_count == 2) {
					int x = _ttoi(word);
					movie.setYear(x);
				}
				else if (field_count == 3) {
					int x = _ttoi(word);
					movie.setLikes(x);
				}
				field_count++;
			}

			else if (x == '\n' || f.eof()) {
				field_count = 0;
				movie.setTrailer(word);
				movies[movie_counter] = movie;
				movie_counter++;

			}
			word = '\0';
		}
		f.close();
		length = movie_counter;
	}
	else {
		f.open("watchlist.txt", ios::in);
		int field_count = 0, movie_counter = 0;
		Movie movie;
		while (!f.eof()) {

			x = f.get();
			while (x != ',' && x != '\n' && !f.eof()) {
				word += x;
				x = f.get();
			}

			if (x == ',') {
				if (field_count == 0) {
					string str(CW2A(word.GetString()));
					movie.setTitle(str);
				}
				else if (field_count == 1) {
					string str(CW2A(word.GetString()));
					movie.setGenre(str);
				}
				else if (field_count == 2) {
					int x = _ttoi(word);
					movie.setYear(x);
				}
				else if (field_count == 3) {
					int x = _ttoi(word);
					movie.setLikes(x);
				}
				field_count++;
			}

			else if (x == '\n' || f.eof()) {
				field_count = 0;
				movie.setTrailer(word);
				watchlist[movie_counter] = movie;
				movie_counter++;

			}
			word = '\0';
		}
		wlen = movie_counter;
		f.close();
	}
	
}

//mode = admin/user
//if admin => write data in movie.txt
//if user => write data in watchlist.txt
void MovieInMemoryRepo::write(string mode) {
	if (mode == "admin") {
		fstream f;
		f.open("movies.txt", ios::out);
		for (int i = 0; i < length - 1; i++) {
			f << movies[i].getTitle() << "," << movies[i].getGenre() << "," << movies[i].getYear() << "," \
				<< movies[i].getLikes() << "," << CT2A(movies[i].getTrailer()) << endl;
		}
		f << movies[length - 1].getTitle() << "," << movies[length - 1].getGenre() << "," << movies[length - 1].getYear() << "," \
			<< movies[length - 1].getLikes() << "," << CT2A(movies[length - 1].getTrailer());
		f.close();
	}
	else {
		fstream f;
		f.open("watchlist.txt", ios::out);
		for (int i = 0; i < wlen - 1; i++) {
			f << watchlist[i].getTitle() << "," << watchlist[i].getGenre() << "," << watchlist[i].getYear() << "," \
				<< watchlist[i].getLikes() << "," << CT2A(watchlist[i].getTrailer()) << endl;
		}
		f << watchlist[wlen - 1].getTitle() << "," << watchlist[wlen - 1].getGenre() << "," << watchlist [wlen - 1] .getYear() << "," \
			<< watchlist[wlen - 1].getLikes() << "," << CT2A(watchlist[wlen - 1].getTrailer());
		f.close();
	}
}