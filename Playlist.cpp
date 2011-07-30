#include "Playlist.h"
#include <ostream>
#include <sstream>
#include <string>

using std::ostream;
using std::string;
using std::stringstream;

Playlist::Playlist() {changed = true;}

Playlist::Playlist(string& n) : name(n) {changed = true;}

Playlist::Playlist(string& n, const Playlist& b) :
	name(n), items(b.items) {
	changed = true;
}

Playlist::Playlist(string& n, Show& s) :
	name(n) {
	add(s);
}

void Playlist::add(Show& s) {
	items.push_back(s);
	changed = true;
}

void Playlist::add(Show& s, size_t pos) {
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
	stringstream out;
	if(changed) {
		size_t played = 0;
		out << '[' << played << '/' << items.size() << "]  " << name;

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
		
void Playlist::printdetail(ostream& o) {
	size_t played = 0;
	o << played << ' ' << items.size() << ' ' << name;
}

void Playlist::remove(size_t pos) {
	if(pos < items.size())
		items.erase(items.begin()+pos);
}

const size_t Playlist::size() {
	return items.size();
}
