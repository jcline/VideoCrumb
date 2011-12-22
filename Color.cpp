#include <iostream>
#include <map>
#include <string>

#include "Color.h"
#include "ncurses.h"

using std::map;
using std::pair;
using std::string;

Color::Color() {
}

Color::~Color() {
}

void Color::init() {
	if(has_colors() == false) {
		endwin();
		std::cerr << "Your terminal does not support colors.\n";
		exit(2);
	}
	start_color();
}

void Color::add(string name, short fg, short bg) {
	init_pair(colors.size()+1,fg,bg);
	colors.insert( pair<string,int> ( name, colors.size()+1 ));
}

int Color::find(const string& key) {
	auto ret = colors.find(key);
	if(ret == colors.end())
		return -1;
	return ret->second;
}
