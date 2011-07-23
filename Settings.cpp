#include <string>

#include "Color.h"
#include "ncurses.h"
#include "Settings.h"

using std::string;

Settings::Settings(WINDOW* w, Color& cm) :
 	Window(w,cm) {
}

void Settings::command(const string& s) {
}

void Settings::control(const int c) {
}

void Settings::drawit() {
	werase(window);
	wrefresh(window);
}



