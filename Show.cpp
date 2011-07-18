#include "Show.h"
#include <string>

using std::string;

Show::Show(const Show& other) {
	name = other.name;
	file = other.file;
	type = other.type;
}

string Show::print() {
	return name;
}

