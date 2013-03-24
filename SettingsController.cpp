#include <cstdlib>
#include <iostream>
#include <string>

#include "boost/filesystem.hpp"

#include "SettingsController.h"

using std::cerr;
using std::getenv;
using std::string;

using namespace boost::filesystem;

void CheckCreatePath(path p) {
	if (!exists(p)) {
		if(!create_directory(p)) {
			cerr << "Could not create '" << p << "'.\n";
			exit(1);
		}
	}
}

void SettingsController::load(path c, path d) {
	char* p;

	p = getenv("HOME");
	if(p)
		home = path(p);
	else {
		cerr << "Could not read $HOME\n";
		exit(1);
	}

	if(c.empty()) {
		p = getenv("XDG_CONFIG_HOME");
		if(!p) {
			config = path(home);
			config /= ".config";
			CheckCreatePath(config);
		}

		config /= "videocrumb";
		CheckCreatePath(config);
	}
	else
		config = c;

	if(d.empty()) {
		p = getenv("XDG_DATA_HOME");
		if(!p) {
			data = path(home);
			data /= ".local";
			CheckCreatePath(data);

			data /= "share";
			CheckCreatePath(data);
		}
		else {
			data = p;
		}

		data /= "videocrumb";
		CheckCreatePath(data);

		db = path(data);
		data /= "dbnew";
		db /= "db.sqlite";
	}
	else
		data = d;
}
