#ifndef SPECIAL_H
#define SPECIAL_H
#include "includes.h"
#include "Movie.h"

class Special : public Movie {

	public:
		Special( const int& c,
				const string& file,
				const string& n="no name",
				const string& s="");
		Special( const int& c,
				const vector<Item>&l,
				const string& n="no name",
				const string& s="");
		~Special();

		/* From Anime */
		string getType();

	protected:

	private:

};

#endif

