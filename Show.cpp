#include "Show.h"
#include <string>

using std::string;

/*
Show::Show(string& f, string& n, showtype t, size_t w) :
	file(f), type(t), watched(w) {
	n = (n == "") ? f : n;
}
*/

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

