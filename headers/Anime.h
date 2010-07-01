#ifndef ANIME_H
#define ANIME_H

#include "includes.h"

class Anime {
	
	public:
		Anime( const string& n="no name", const string& s="" );
		~Anime();

		void editName( const string& n );
		void editSubtext( const string& s );
		const string& printName();

		virtual void add( const string& i ) = 0;
		virtual string getType() const = 0;
		virtual int getCurrent() const = 0;
		virtual int getTotal() const = 0;
		virtual bool playNext() = 0;
		virtual bool unPlay() = 0;
		virtual const string& print() const = 0;
		virtual void setNext( const int& n ) = 0;

	protected:
		string name;
		string subtext;

	private:

};

#endif
