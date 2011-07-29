#include <string>

#include "Color.h"
#include "ncurses.h"
#include "Player.h"
#include "SettingsWindow.h"

using std::string;

SettingsWindow::SettingsWindow(WINDOW* w, Color& cm) :
 	Window(w,cm) {
}

void SettingsWindow::command(const string& s) {
}

void SettingsWindow::control(const int c) {
}

void SettingsWindow::drawit() {
	werase(window);
	wrefresh(window);
}



