#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "includes.h"
#include "Show.h"

struct Config {
	string base_dir;
	
};

enum sort_algos_t {
	ALPHA,
	R_ALPHA
};

vector<string>& getDirContents( const string& s );
vector<string>& getDirDirs( const string& s );
vector<string>& getDirFiles( const string& s );

Season& makeSeasonFromDir( const string& base, const string& dir );

void readconf();
vector<Show>& readdb();
void savedb( const vector<Show>& shows );
void sortShows( vector<Show>& shows, const sort_algos_t a );



#endif
