#include <iostream>
#include <cassert>
#include "HTML.cpp"

using namespace std;

class Tests {
public:
	Tests() {

	}

	void Teste() {
		Controller controller;
		controller.repository.repo.read("admin");
		assert(controller.repository.repo.length == 10);
		assert(controller.repository.repo.wlen == 0);
		Movie m1("a", "a", 2000, 10, "https://www.google.ro/?gws_rd=ssl");
		Movie m2("b", "b", 2001, 9, "https://www.youtube.com/");
		controller.repository.add_movie(m1, "admin");
		controller.repository.add_movie(m2, "admin");
		assert(controller.repository.repo.length == 12);
		controller.repository.add_movie(m1, "user");
		controller.repository.add_movie(m2, "user");
		assert(controller.repository.repo.wlen == 2);
		controller.repository.delete_movie_watchlist("a", 2000);
		assert(controller.repository.repo.wlen == 1);
		controller.repository.delete_movie_list("b", 2001);
		assert(controller.repository.repo.length == 11);
	}
};