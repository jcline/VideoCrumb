#include "headers/Movie.h"

Movie::Movie (const int& c,
		const string& file,
		const string& n,
		const string& s):
  	Anime(n,s), Episode(c,file) {

}

Movie::Movie (const int& c,
		const vector<Item>& l,
		const string& n,
		const string& s):
  	Anime(n,s), Episode(c,l) {

}

Movie::~Movie() {
	return;
}

void Movie::add(const string& i) {
	Episode::add(i);
}

string Movie::getType () {
	return "Movie";
}

bool Movie::playNext() {
	play();
	return true;
}
