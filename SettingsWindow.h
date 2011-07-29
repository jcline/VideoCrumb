#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include "Color.h"
#include "ncurses.h"
#include "Player.h"
#include "Window.h"

class SettingsWindow : public Window{
	public:
		SettingsWindow() {}
		SettingsWindow(WINDOW* w, Color& cm);
		~SettingsWindow() {}

		void command(const std::string& s);
		void control(const int c);
		void drawit();

};

#endif
