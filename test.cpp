#include "headers/Show.h"
#include "headers/helperfunctions.h"

int main (int argc, char* argv[]) {

	string s("/home/vil/Anime/");
	readconf();
	vector<Show> shows;
	vector<Show>::iterator si;
/*	vector<string> v = getDirFiles(s);
	vector<string>::iterator it;
//	vector<string> t;
//	vector<string>::iterator tt;
	for (it = v.begin(); it < v.end(); ++it) {
		Show *s;

		shows.reserve( shows.size() + 1 );
		s =  new Show( it->substr( 0, it->length() - 4 ) );
		s->add( *new Movie( 1, *it) );
		shows.push_back( *s );

//		s->playIndex(1);

//		cout << it->substr( 0, it->length() - 4) << " " << *it << endl;

//		t = getdirfiles(s + *it);
//		for( tt = t.begin(); tt < t.end(); ++tt)
	}

	for (si = shows.begin(); si < shows.end(); ++si)
		cout << si->print() << endl;
*/

	vector<string> sd = getDirDirs(s);	

	vector<string>::iterator isd;
	for( isd = sd.begin(); isd < sd.end(); ++isd) {
		cout << *isd << endl;
		Show ss( *isd );
		shows.reserve( shows.size() + 1 );
		ss.add( makeSeasonFromDir( s, *isd ) );
		shows.push_back( s ); 
	}

	for( si = shows.begin(); si < shows.end(); ++si )
		cout << si->print();


	return 0;
}

