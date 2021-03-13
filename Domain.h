#pragma once
#include <Windows.h>
#include <atlstr.h>
#include <string>

using namespace std;

class Movie {
protected:
	string title, genre;
	int year, likes;
	CString trailer;

public:
	Movie() {
		this->title = "";
		this->genre = "";
		this->year = 0;
		this->likes = 0;
		this->trailer = "";
	}

	Movie(string title, string genre, int year, int likes, CString trailer) {
		this->title = title;
		this->genre = genre;
		this->year = year;
		this->likes = likes;
		this->trailer = trailer;
	}

	//getters
	string getTitle() { return title; }
	string getGenre() { return genre; }
	int getYear() { return year; }
	int getLikes() { return likes; }
	CString getTrailer() { return trailer; }

	//setters
	void setTitle(string newTitle) { title = newTitle; }
	void setGenre(string newGenre) { genre = newGenre; }
	void setYear(int newYear) { year = newYear; }
	void setLikes(int newLikes) { likes = newLikes; }
	void setTrailer(CString newTrailer) { trailer = newTrailer; }

};
