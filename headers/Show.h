#ifndef SHOW_H
#define SHOW_H
#include "includes.h"
#include "Season.h"
#include "OAV.h"
#include "Movie.h"
#include "Special.h"

enum status_t {
	NOT_WATCHING,
	WATCHING,
	COMPLETED
};

class Show {

	friend ostream& operator<<( ostream& output, const Show& s );

	public:
		Show( const string& n );
		Show( const Show& s );
		~Show();

		Show& operator=( const Show& s );

		void add(Anime& a);
		void playIndex( const int& i );
		void playNext();
		const string& print() const;
		const string& printName() const;
		void unPlay();

	protected:
		void incNext();

	private:
		status_t status;
		string name;
		vector<Anime*> *anime_list;
		vector<Anime*>::iterator next;

};

#endif
