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

		void add(Show s) {
			items.push_back(s);
			changed = true;
		}

		void add(Show s, size_t pos) {
			if(pos < items.size())
				items.insert(items.begin()+pos, s);
		}

		auto begin() -> decltype(items.end()) {
			return items.begin();
		}

		auto end() -> decltype(items.end()) {
			return items.end();
		}

		std::string print() {
			if(changed) {
				std::stringstream out;
				size_t i = 0;
				for(auto it = items.begin(); it < items.end(); ++it, ++i)
					out << i+1 << ": " << it->print() << '\n';
				printstr = out.str();
				changed = false;
			}

			return printstr;
		}

		std::string print(size_t pos) {
			if(pos >= 0 && pos < items.size()) {
				std::stringstream out;
				out << pos << ": " << items[pos].print();
				return out.str();
			}
			return "";
		}
				

		void remove(size_t pos) {
			if(pos < items.size())
				items.erase(items.begin()+pos);
		}

	private:
		bool changed;
		std::string printstr;

};

#endif
