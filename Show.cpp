#include "Show.h"
#include <string>

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

string Show::printdetail() {
	return name + '\n' + pretty(type) + ' ' + file; 
}

