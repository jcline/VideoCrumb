#include <string>

#include "Color.h"
#include "Player.h"
#include "Window.h"

using std::string;

Window::Window(WINDOW* w, Color& cm) :
	window(w), colormanager(&cm) {
}

void Window::resize() {
	int rows, cols;
	getmaxyx(stdscr, rows,   cols);
	wresize (window, rows-2, cols);
}
