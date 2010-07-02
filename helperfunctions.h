#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <algorithm>
#include <fstream>
#include <vector>

#include <cstdio>
#include <cstddef>

#include <dirent.h>
#include <sys/types.h>

#include "Show.h"

struct Config {
	std::string base_dir;
	
};

enum sort_algos_t {
	ALPHA,
	R_ALPHA
};

std::vector<std::string>& getDirContents( const std::string& s );
std::vector<std::string>& getDirDirs( const std::string& s );
std::vector<std::string>& getDirFiles( const std::string& s );

//Season& makeSeasonFromDir( const std::string& base, const std::string& dir );

void readconf();
std::vector<Show>& readdb();
void savedb( const std::vector<Show>& shows );
void sortShows( std::vector<Show>& shows, const sort_algos_t a );



#endif
