#include <string>
#include "Window.h"

using std::string;

Window::Window(const Window& w) :
	window(w.window), name(w.name) {
}

Window::Window(WINDOW* w) : window(w) {
}

Window::Window(WINDOW* w, string n) :
	window(w), name(n) {
}
