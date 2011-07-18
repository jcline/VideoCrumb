#include "helperfunctions.h"

using namespace std;

namespace helpers {

	static int all ( const struct dirent *unused ) {
		return 1;
	}

	static int dirs ( const struct dirent *unused ) {
		if (unused->d_type == DT_DIR) {
			if (unused->d_name[0] == '.')
				return 0;
			return 1;
		}
		return 0;
	}

	static int files ( const struct dirent *unused ) {
		if (unused->d_type == DT_REG)
			return 1;
		return 0;
	}

	bool alpha( Show s1, Show s2 ) {
		return ( s1.name < s2.name );
	}
	bool r_alpha( Show s1, Show s2 ) {
		return ( s1.name > s2.name );
	}
}

vector<string>& getDirContents( const string& s ) {
	vector<string> *v = new vector<string>();
	struct dirent **entries;

	int n = scandir(s.c_str(), &entries, helpers::all, alphasort);
	v->reserve(n);
	if (n >= 0) {
		int i;
		for (i = 0; i < n; ++i)
			v->push_back( entries[i]->d_name );
	}

	return *v;
}

vector<string>& getDirDirs( const string& s ) {
	vector<string> *v = new vector<string>();
	struct dirent **entries;

	int n = scandir(s.c_str(), &entries, helpers::dirs, alphasort);
	if (n >= 0) {
		int i;
		for (i = 0; i < n; ++i)
			v->push_back( entries[i]->d_name );
	}

	return *v;
}

vector<string>& getDirFiles( const string& s ) {
	vector<string> *v = new vector<string>();
	struct dirent **entries;

	int n = scandir(s.c_str(), &entries, helpers::files, alphasort);
	if (n >= 0) {
		int i;
		for (i = 0; i < n; ++i)
			v->push_back( entries[i]->d_name );
	}

	return *v;
}



/*
Season& makeSeasonFromDir( const string& base, const string& dir ) {

	vector<string> v = getDirFiles(base + dir + "/");

	Season *s = new Season( v.size(), dir );

	vector<string>::iterator iv;
	for ( iv = v.begin(); iv < v.end(); ++iv) {
		s->add( base + dir + "/" + *iv );
	}


	return *s;
}
*/
void readconf() {
	return;
}

vector<Show>& readdb() {
	vector<Show> *v = new vector<Show>();
	ifstream db;
	
	db.open( "/home/vil/.local/share/AM/db" );

	while ( db.good() ) {
		string name;
		int next, size, i;
		getline( db, name, '\n' );
		if ( name.compare( "" ) == 0 )
			break;
		Show s( name );
		db >> next >> size;
		db.ignore(10000,'\n');

		for ( i = 0; i < size; ++i ) {
			string aname;
			int anext, acount, asize, j;
			getline( db, aname, '\n' );
			db >> anext >> acount >> asize;
			db.ignore(10000,'\n');

//			Season *season = new Season( asize, aname );
			for( j = 1; j <= acount; ++j ) {
				string file;
				getline( db, file, '\n' );
//				season->add( file );
			}
//			season->setNext( anext );

//			s.add( *season );

		}

		v->push_back( s );

	}

	sortShows( *v, ALPHA );

	return *v;
}

void savedb( const vector<Show>& shows ) {
	ofstream db;
	db.open("/home/vil/.local/share/AM/db", ios::out | ios::trunc);
	
	vector<Show>::const_iterator it;
	for( it = shows.begin(); it < shows.end(); ++it)
  {}
//		db << *it; 

	db.close();
}

void sortShows( vector<Show>& shows, const sort_algos_t a ) {

	bool (*func)( Show, Show ) = NULL;

	switch (a) {
		case ALPHA:
			func = helpers::alpha;
			break;	
		case R_ALPHA:
			func = helpers::r_alpha;
			break;
		default:
			func = helpers::alpha;
			break;
	}

	sort( shows.begin(), shows.end(), func );
}

