#ifndef MOVIE_H
#define MOVIE_H
#include "includes.h"
#include "Episode.h"
#include "Anime.h"

class Movie : public Anime, public Episode {
	
	public:
		Movie( const int& c,
				const string& file,
				const string& n="no name",
				const string& s="");
		Movie( const int& c,
				const vector<Item>&l,
				const string& n="no name",
				const string& s="");
		~Movie();

		/* From Anime */
		string getType();
		bool playNext();

		/* From Episode */
		void add(const string& i);

	protected:

	private:

};

#endif

