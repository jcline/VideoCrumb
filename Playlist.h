#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Show.h"
#include <sstream>
#include <string>
#include <vector>

class Playlist {
	private:
		bool changed;
		std::string printstr, name;
		std::vector<Show> items;

	public:

		Playlist();
		Playlist(std::string& n);
		Playlist(std::string& n, const Playlist& b);
		Playlist(std::string& n, Show& s);

		~Playlist() {}

		void add(Show& s);
		void add(Show& s, size_t pos);
		auto begin() -> decltype(items.end());
		auto end() -> decltype(items.end());
		std::string print();
		std::string print(size_t pos);
		void remove(size_t pos);
		const size_t size();

};

#endif
