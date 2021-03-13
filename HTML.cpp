#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <atlstr.h>
#include "Controller.cpp"

using namespace std;

class HTML :Controller {
	//Vererbt von dem Controller alle Funktionen und Variablen

public:
	std::string tabletext;

public:
	HTML() {

	}

	void makeGap(int gap, std::string& text) {
		//einige Tabs werden eingefugt, um der Codeteil geordent zu sein
		for (int i = 0; i < gap; i++)
			text.append(" ");
	}

	void maketablehtml(Movie m[100], int len, string s) {
		//wir erzeugen die Tabelle in html
		string chars[5] = { "Title", "Genre", "Jahr", "Likes", "Trailer Link" };
		int headgap = 3;
		int bodygap = 3;
		int tablegap = 6;
		int rowgap = 9;
		//machen einen langen string mit allen Anweisungen
		tabletext += "<html>\n";
		makeGap(headgap, tabletext);
		tabletext += "<head>\n";
		makeGap(headgap, tabletext);
		tabletext += "<title>Watchliste</title>\n";
		makeGap(headgap, tabletext);
		tabletext += "</head>\n";
		makeGap(bodygap, tabletext);
		tabletext += "<body>\n";
		makeGap(tablegap, tabletext);
		tabletext += "<table border=""1"">\n";
		makeGap(tablegap, tabletext);
		tabletext += "<tr>";
		//wir tun die Titel der Spalten
		for (int i = 0; i < 5; i++) {
			tabletext += "<td>";
			tabletext += chars[i];
			tabletext += "</td>";
		}
		//wir tun die Informationen uber die Filme in den Spalten und Zeilen
		tabletext += "</tr>\n";
		for (int i = 0; i < len; i++) {
			makeGap(headgap, tabletext);
			tabletext += "<tr>\n";
			tabletext += "<td>";
			tabletext += m[i].getTitle();
			tabletext += "</td>";
			tabletext += "<td>";
			tabletext += m[i].getGenre();
			tabletext += "</td>";
			tabletext += "<td>";
			tabletext += to_string(m[i].getYear());
			tabletext += "</td>";
			tabletext += "<td>";
			tabletext += to_string(m[i].getLikes());
			tabletext += "</td>";
			tabletext += "<td><a href =";
			wstring ws(m[i].getTrailer());
			string s = string(ws.begin(), ws.end());
			tabletext += s;
			tabletext += ">Link</a></td>";
			tabletext += "<tr>\n";
		}

		makeGap(tablegap, tabletext);
		tabletext += "</table>\n";
		makeGap(bodygap, tabletext);
		tabletext += "</body>\n";
		tabletext += "</html>\n";
		//wir offnen die Datei der Tabelle in html
		std::ofstream htmltable("Watchliste.htm", std::ios::out | std::ios::trunc);
		htmltable << tabletext;
		htmltable.close();
	}

	void executehtml(Movie m[100], int len) {
		string s = "Watchlist.htm";
		maketablehtml(m, len, s);
		CString strWebPage;
		strWebPage = "Watchliste.htm";
		//wir offnen im Browser die erzeugte Tabelle
		ShellExecute(NULL, NULL, strWebPage, NULL, NULL, SW_SHOWNORMAL);
	}
};