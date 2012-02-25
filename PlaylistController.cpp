#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include "soci/soci/src/core/soci.h"
#include "soci/soci/src/backends/sqlite3/soci-sqlite3.h"

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "PlaylistController.h"
#include "SettingsController.h"

using std::cout;
using std::map;
using std::string;
using std::vector;

using namespace soci;

using boost::filesystem::ofstream;
using boost::filesystem::ifstream;
using namespace boost::filesystem;

extern SettingsController sc;

PlaylistController::PlaylistController() {
}

void PlaylistController::addplaylist(Playlist& pl, const int pos) {
	if(pos < 0) {
		playlists.push_back(pl);
		selection = begin() + offset;
		dispoffset = size() - 1;
		dispselection = begin() + dispoffset;
	}
	else if((size_t)pos < playlists.size()) {
		playlists.insert(begin() + pos, pl);
		selection = begin() + offset;
		dispoffset = pos;
		dispselection = begin() + dispoffset;
	}
}

void PlaylistController::autoaddplaylist(path p) {
	if(!exists(p))
		return;
	if(!is_directory(p))
		return;

	string n = p.filename().string();
	if(n.empty())
		return;

	Playlist pl(n);
	map<string,string> shows;

	for(auto i = directory_iterator(p); i != directory_iterator(); ++i) {
		shows[i->path().filename().string()] = i->path().string();
	}

#if __GNUC__ <= 4 && __GNUC_MINOR__ < 6
	size_t size = shows.size();
	for(size_t i = 0; i < size; ++i) {
		Show s(shows[i].second, shows[i].first, EPISODE);
		pl.add(s);
	}
#else
	for(auto &i: shows) {
		Show s(i.second, i.first, EPISODE);
		pl.add(s);
	}
#endif
	addplaylist(pl);
}

auto PlaylistController::begin() -> decltype(playlists.begin()) {
	return playlists.begin();
}

auto PlaylistController::cbegin() -> decltype(playlists.cbegin()) {
	return playlists.cbegin();
}

void deleteselected() {}

auto PlaylistController::end() -> decltype(playlists.end()) {
	return playlists.end();
}

auto PlaylistController::cend() -> decltype(playlists.cend()) {
	return playlists.cend();
}

bool PlaylistController::empty() {
	return playlists.empty();
}

auto PlaylistController::getselection() -> decltype(selection) {
	selection = begin() + offset;
	return selection;
}

auto PlaylistController::getdispselection() -> decltype(selection) {
	dispselection = begin() + dispoffset;
	return dispselection;
}

void PlaylistController::go() {
	offset = dispoffset;
	selection = dispselection;
}

void PlaylistController::go(decltype(selection) pos) {
	//if(pos >= begin() && pos < end())
		selection = pos;
}

void PlaylistController::offsetselection(size_t o) {
	auto s = selection + o;
	if(s >= begin() && s < end()) {
		selection = s;
		offset += o;
	}
	return;
}

void PlaylistController::offsetdispselection(size_t o) {
	auto s = dispselection + o;
	if(s >= begin() && s < end()) {
		dispselection = s;
		dispoffset += o;
	}
	return;
}

/**
	Database loading and saving
*/
bool PlaylistController::loaddb() {
	bool ret = true;

	ifstream db;
	db.open(sc.data);

	size_t played, size;
	unsigned int watched;
	string name, type, file;
	
	//TODO: Better error checking
	while(db.good()) {
		db >> played >> size;
		db.ignore();
		getline(db, name);
		if(db.fail()) {
			goto cleanup;
		}

		Playlist p(name);
		for(size_t i = 0; i < size; ++i) {
			db >> watched >> type;
			db.ignore(100,'\n');
			getline(db, name);
			getline(db, file);
			// The file was incorrectly formatted
			if(db.fail()) {
				ret = false;
				goto cleanup;
			}

			Show s(file, name, Show::gettype(type), watched);
			p.add(s);
		}

		Playlist pl(p.getname(),p);
		addplaylist(pl);
	}

cleanup:
	selection = dispselection = begin();
	offset = dispoffset = 0;

	std::sort(begin(), end(), [](const Playlist& a, const Playlist& b) {
			return a.getname() < b.getname();
		}
	);

	db.close();
	return ret;
}


bool PlaylistController::savedb() {
	ofstream db;
	db.open(sc.data);

	//TODO: Better error checking
#if __GNUC__ <= 4 && __GNUC_MINOR__ < 6
	size_t size = playlists.size();
	for(size_t i = 0; i < size; ++i) {
		playlists[i].printdetail(db);
		db << '\n';
		size_t shows_size = shows.size();
		for(size_t j = 0; j < shows_size; ++j) {
			shows[j].printdetail(db);
			db << '\n';
		}
	}
#else
	for(Playlist& p : playlists) {
		p.printdetail(db);
		db << '\n';
		for(Show& s : p) {
			s.printdetail(db);
			db << '\n';
		}
	}
#endif

	db.close();

	savedb_new();

	return true;
}

bool PlaylistController::db_create(bool exists, session& db) {

	const double version = .2;
	double v = 0;
	indicator ind;
	bool init = true, caught = false;


	// TODO: remove exists once we drop old database stuff
	if(exists) {
		try {
			db << "SELECT Number FROM Version", into(v, ind);
		}
		catch (const std::exception& e) {
			init = true;
			caught = true;
		}

		if(!caught && db.got_data()) {
			switch(ind) {
				case i_ok:
					init = false;
					break;
				case i_null:
					break;
				case i_truncated:
					break;
			}

			if(v < version) {
				init = true;
			}
		}
	}
	else
		init = true;

	if(init) {
		db << "CREATE TABLE IF NOT EXISTS Playlists ("
			"Name TEXT PRIMARY KEY ASC NOT NULL"
			")";
		db << "CREATE TABLE IF NOT EXISTS Version ("
			"Number REAL NOT NULL"
			")";

		db << "CREATE TABLE IF NOT EXISTS Shows ("
			"File TEXT PRIMARY KEY ASC NOT NULL, "
			"Name TEXT, "
			"ID INT NOT NULL, "
			"Watched INT DEFAULT 0, "
			"Type TEXT NOT NULL DEFAULT EPISODE, "
			"Playlist REFERENCES Playlists (Name) ON DELETE CASCADE ON UPDATE CASCADE"
			")";

		if(exists && !caught && v < version) {
			db << "UPDATE Version SET Number = :version", use(version);
		}
		else
			db << "INSERT INTO Version (Number) VALUES(:version)", use(version);

		// TODO: remove this once we drop old database stuff
		if(!exists) {
#if __GNUC__ <= 4 && __GNUC_MINOR__ < 6
			int order = 0;
			for(auto i = playlists.begin(); i < playlists.end(); ++i) {
				db << "INSERT INTO Playlists VALUES(:NAME)", use(playlists[i]);

				for(auto j = playlists[i].begin(); j < playlists[i].end(); ++j) {
					db << "INSERT INTO Shows VALUES(:FILE,:NAME,:WATCHED,:TYPE,:PLAYLIST)",
						 use(*j), use((*j).getname(), "PLAYLIST");

				}
			}
#else
			int order = 0;
			for(Playlist& p : playlists) {
				db << "INSERT INTO Playlists VALUES(:NAME)", use(p);

				for(Show& s : p) {

					db << "INSERT INTO Shows VALUES(:FILE,:NAME,:WATCHED,:TYPE,:PLAYLIST)",
						 use(s), use(p.getname(), "PLAYLIST");

				}
			}
#endif
		}

		db << "SELECT Number FROM Version", into(v, ind);

		if(db.got_data()) {
			switch(ind) {
				case i_ok:
					return true;
					break;
				case i_null:
					return false;
					break;
				case i_truncated:
					break;
			}
		}
	}

	return false;
}

bool PlaylistController::savedb_new() {
	bool exists = boost::filesystem::exists(sc.db);
	session db(sqlite3, sc.db.native());

	// TODO: remove exists once we drop old database stuff
	assert(db_create(exists, db));

#if __GNUC__ <= 4 && __GNUC_MINOR__ < 6
	size_t size = playlists.size();
	for(size_t i = 0; i < size; ++i) {
		if(playlists[i].haschanged()) {
			std::string name;
			indicator ind;
			db << "SELECT Name FROM Playlists WHERE Name == :OLDNAME", use(playlists[i]), into(name, ind);
			if(ind == i_ok && db.got_data()) {
				db << "UPDATE Playlists SET "
					"Name=:NAME "
					"WHERE Name == :OLDNAME", use(playlists[i]);
			}
			else {
				db << "INSERT INTO Playlists VALUES(:NAME)", use(playlists[i]);
			}
		}


		size_t shows_size = p.size();
		for(size_t j = 0; j < shows_size; ++j) {
			//s.printdetail(db);
			//db << '\n';
		}
	}
#else
	for(Playlist& p : playlists) {
		if(p.haschanged()) {
			std::string name;
			indicator ind;
			db << "SELECT Name FROM Playlists WHERE Name == :OLDNAME", use(p), into(name, ind);
			if(ind == i_ok && db.got_data()) {
				db << "UPDATE Playlists SET "
					"Name=:NAME "
					"WHERE Name == :OLDNAME", use(p);
			}
			else {
				db << "INSERT INTO Playlists VALUES(:NAME)", use(p);
			}
		}


		for(Show& s : p) {
			//s.printdetail(db);
			//db << '\n';
		}
	}
#endif

	return true;
}

size_t PlaylistController::size() { return playlists.size(); }
