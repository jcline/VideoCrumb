#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include <vector>

#include "Playlist.h"

class PlaylistController {
	private:
		std::vector<Playlist> playlists;
		decltype(playlists.begin()) selection, dispselection;
		size_t dispoffset, offset;
		bool changed;

	public:
		PlaylistController();

		void addplaylist(Playlist& pl, const int pos = -1);
		auto begin() -> decltype(playlists.begin());
		auto end() -> decltype(playlists.end());
		auto getselection() -> decltype(playlists.begin());
		auto getdispselection() -> decltype(playlists.begin());
		void go();
		void go(decltype(selection) pos);
		bool loaddb();
		void offsetselection(size_t o);
		void offsetdispselection(size_t o);
		bool savedb();
		size_t size();
};

#endif
