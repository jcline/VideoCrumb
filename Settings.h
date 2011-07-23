#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include "Color.h"
#include "ncurses.h"
#include "Window.h"

class Settings : public Window{
	public:
		Settings() {}
		Settings(WINDOW* w, Color& cm);
		~Settings() {}

		void command(const std::string& s);
		void control(const int c);
		void drawit();

};

#endif
