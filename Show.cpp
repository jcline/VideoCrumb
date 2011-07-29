#include<iostream>
#include <string>

#include "Show.h"

using std::ostream;
using std::string;

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
}

Show::Show(Show& other) {
	name = other.name;
	file = other.file;
	type = other.type;
}

string Show::print() {
	return name;
}

void Show::printdetail(ostream& o) {
	o << name << '\n' << watched << ' ' << pretty(type) << ' ' << file;
}

