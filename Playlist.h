#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Show.h"
#include <sstream>
#include <string>
#include <vector>

class Playlist {
	public:
		std::vector<Show> items;

		Playlist(const Playlist& b) {
			items = b.items;
			changed = true;
		}

		Playlist(Show& s) {
			add(s);
		}

		Playlist() : changed(true) {
		}

		~Playlist() {}

		void add(Show s);
		void add(Show s, size_t pos);
		auto begin() -> decltype(items.end());
		auto end() -> decltype(items.end());
		std::string print();
		std::string print(size_t pos);
		void remove(size_t pos);
		const size_t size();

	private:
		bool changed;
		std::string printstr;

};

#endif
