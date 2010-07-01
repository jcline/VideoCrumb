#include "headers/Item.h"

Item::Item() {}

Item::Item(const string& f) {
	file = f;
}

Item::~Item() {
}

int Item::open() {
	string mp("mplayer -aid 1 \"" + file + "\"");
	system(mp.c_str());
	return 0;
}

string Item::print() {
	return file;
}
