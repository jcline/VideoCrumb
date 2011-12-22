#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Show.h"
#include <ostream>
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
		auto first() -> decltype(items.end());

		void change();
		void deleteselection(decltype(items.begin()) s);
		unsigned int played();
		void remove(size_t pos);

		std::string print();
		void printdetail(std::ostream& o);
		std::string print(size_t pos);

		const size_t size();

};

#endif
