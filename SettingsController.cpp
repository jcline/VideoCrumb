#include <iostream>
#include <string>

#include "boost/filesystem.hpp"

#include "SettingsController.h"

using std::cerr;
using std::string;

using namespace boost::filesystem;

SettingsController::SettingsController(path config, path data) {
	char* p;
	if(config.empty()) {
		p = getenv("XDG_CONFIG_HOME");
		if(p)
			config = path(p) / "AM";
		else {
			cerr << "Could not read $XDG_CONFIG_HOME, please use --config\n";
			exit(1);
		}
	}

	if(data.empty()) {
		p = getenv("XDG_CONFIG_HOME");
		if(p)
			data = path(p) / "AM/dbnew";
		else {
			cerr << "Could not read $XDG_CONFIG_HOME, please use --config\n";
			exit(1);
		}
	}
}
