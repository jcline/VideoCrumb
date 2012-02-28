#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include "boost/filesystem.hpp"

class SettingsController {
	private:
		typedef boost::filesystem::path bfp;
	public:
		bfp config, data, home, db;

		void load(bfp c = "", bfp d = "");
};

#endif
