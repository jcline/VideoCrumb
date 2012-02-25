#include <cstdlib>
#include <iostream>
#include <string>

#include "boost/filesystem.hpp"

#include "SettingsController.h"

using std::cerr;
using std::getenv;
using std::string;

using namespace boost::filesystem;

void SettingsController::load(path c, path d) {
	char* p;
	if(c.empty()) {
		p = getenv("XDG_CONFIG_HOME");
		if(p) {
			config = p;
			config /= "AM";
		}
		else {
			cerr << "Could not read $XDG_CONFIG_HOME, please use --config\n";
			//exit(1);
		}
	}

	if(d.empty()) {
		p = getenv("XDG_DATA_HOME");
		if(p) {
			data = p;
			data /= "AM/dbnew";
			db = p;
			db /= "AM/db.sqlite";
		}
		else {
			cerr << "Could not read $XDG_DATA_HOME, please use --data-dir\n";
			exit(1);
		}
	}

	p = getenv("HOME");
	if(p)
		home = path(p);
	else {
		cerr << "Could not read $HOME\n";
		exit(1);
	}
}
