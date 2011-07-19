#include "Playlist.h"
#include <string>

using std::string;
using std::stringstream;

void Playlist::add(Show s) {
	items.push_back(s);
	changed = true;
}

void Playlist::add(Show s, size_t pos) {
	if(pos < items.size())
		items.insert(items.begin()+pos, s);
	changed = true;
}

auto Playlist::begin() -> decltype(items.end()) {
	return items.begin();
}

auto Playlist::end() -> decltype(items.end()) {
	return items.end();
}

string Playlist::print() {
	if(changed) {
		stringstream out;
		size_t i = 0;
		for(auto it = items.begin(); it < items.end(); ++it, ++i)
			out << i+1 << ": " << it->print() << '\n';
		printstr = out.str();
		changed = false;
	}

	return printstr;
}

string Playlist::print(size_t pos) {
	if(pos >= 0 && pos < items.size()) {
		stringstream out;
		out << pos << ": " << items[pos].print();
		return out.str();
	}
	return "";
}
		

void Playlist::remove(size_t pos) {
	if(pos < items.size())
		items.erase(items.begin()+pos);
}


