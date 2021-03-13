#pragma once
#include "Domain.h"
#include <string.h>
#include <vector>

using namespace std;

template <class E>

class CrudRepo {
public:
	virtual void read(string mode) = 0;
	virtual void write(string mode) = 0;
	virtual ~CrudRepo() {};
};

class MovieInMemoryRepo : public CrudRepo<Movie>
{
public:
	Movie movies[100];
	Movie watchlist[100];
	int length = 0;
	int wlen = 0;
	void read(string mode);
	void write(string mode);
};

