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

#if BOOST_FILESYSTEM_VERSION == 3
	string n = p.filename().string();
#else
	string n = p.filename();
#endif
	if(n.empty())
		return;

	Playlist pl(n);
	map<string,string> shows;

	for(auto i = directory_iterator(p); i != directory_iterator(); ++i) {
#if BOOST_FILESYSTEM_VERSION == 3
		shows[i->path().filename().string()] = i->path().string();
#else
		shows[i->path().filename()] = i->path().string();
#endif
	}

#if __GNUC__ <= 4 && __GNUC_MINOR__ < 6
	for(auto i = shows.begin(); i != shows.end(); ++i) {
		Show s((*i).second, (*i).first, EPISODE);
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

void PlaylistController::deleteselected() {
  if (!playlists.empty()) {
    playlists.erase(dispselection);
  }
}

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

size_t PlaylistController::getdispoffset() {
  return dispoffset;
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

	std::sort(begin(), end());

	db.close();
	return ret;
}


bool PlaylistController::savedb() {
	ofstream db;
	db.open(sc.data);

	//TODO: Better error checking
#if __GNUC__ <= 4 && __GNUC_MINOR__ < 6
	for(auto i = playlists.begin(); i < playlists.end(); ++i) {
		(*i).printdetail(db);
		db << '\n';
		for(auto j = (*i).begin(); j < (*i).end(); ++j) {
			(*j).printdetail(db);
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

size_t PlaylistController::size() { return playlists.size(); }
