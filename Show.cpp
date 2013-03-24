#include<iostream>
#include <sstream>
#include <string>

#include "Show.h"

using std::ostream;
using std::string;
using std::stringstream;

string pretty(showtype t) {
	switch(t) {
		case COMMENTARY:
			return "COMMENTARY";
			break;
		case EPISODE:
			return "EPISODE";
			break;
		case MOVIE:
			return "MOVIE";
			break;
		case SPECIAL:
			return "SPECIAL";
			break;
		default:
			return "ERROR";
			break;
	}
}

showtype Show::gettype(const string& t) {
	if(t == "COMMENTARY") {
		return COMMENTARY;
	}
	else if(t == "EPISODE") {
		return EPISODE;
	}
	else if(t == "MOVIE") {
		return MOVIE;
	}
	else if(t == "SPECIAL") {
		return SPECIAL;
	}
	return EPISODE;
}

Show::Show(const Show& other) {
	name = other.name;
	file = other.file;
	type = other.type;
	watched = other.watched;
}

Show::Show(Show& other) {
	name = other.name;
	file = other.file;
	type = other.type;
	watched = other.watched;
}

string Show::print() {
	stringstream out;
	out << name;
	return out.str();
}

void Show::printdetail(ostream& o) {
	o << watched << ' ' << pretty(type) << '\n' << name << '\n' << file;
}

void Show::watch() {
	++watched;
}

void Show::unwatch() {
	--watched;
}

const unsigned int Show::getwatched() {
	return watched;
}
