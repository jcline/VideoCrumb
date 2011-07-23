#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <map>

#include "ncurses.h"

class Color{
	private:
		std::map<std::string,int> colors;

	public:
		Color();
		~Color();

		void add(std::string name, short fg, short bg);
		int find(const std::string& key);


};

#endif

