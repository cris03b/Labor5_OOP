#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include "MovieInMemoryRepo.h"
using namespace std;

class CSV {
public:
	CSV() { }

	void write_csv(string filename, vector<pair<string, vector<string>>> dataset) {
		fstream myFile(filename); // Create an output filestream object
		myFile.open(filename, ios::out);
		for (int j = 0; j < dataset.size(); j++) {
				myFile << dataset.at(j).first << ", "; //write column names separated by ","
			if (j != dataset.size() - 1) { 
				myFile << ", ";
			}
		}
		myFile << "\n";

		for (int i = 0; i < dataset.at(0).second.size(); i++) {
			myFile << dataset.at(0).second.at(i) << ", " << dataset.at(1).second.at(i) << \
				", " << dataset.at(2).second.at(i) << ", " << dataset.at(3).second.at(i) << \
				", " << "=HYPERLINK(\" " << dataset.at(4).second.at(i) << "\")" << endl;

		}
		myFile.close();
	}

	void csv_file(Movie w_list[], int len) {
		vector<string> v1;
		vector<string> v2;
		vector<string> v3;
		vector<string> v4;
		vector<string> v5;
		//populate table with data from watchlist
		for (int i = 0; i < len; i++) {
			//CString cstr(word.c_str());
			v1.push_back(w_list[i].getTitle());
			v2.push_back(w_list[i].getGenre());
			//n = repository.watchlist[i].getYear();
			//str = to_string(n);
			v3.push_back(to_string(w_list[i].getYear()));
			//n = repository.watchlist[i].getLikes();
			//str = to_string(n);
			v4.push_back(to_string(w_list[i].getLikes()));
			wstring ws(w_list[i].getTrailer());
			string s = string(ws.begin(), ws.end());
			v5.push_back(s);
		}

		vector<pair<string, vector<string>>> vals = { {"Title", v1}, {"Genre", v2}, { "Year", v3 }, \
		{"Likes", v4}, {"Link", v5} };
		//vector< pair<string, vector<CString>>> url = { {"Link", v5} };

		write_csv("Watchlist.csv", vals);

	}
};