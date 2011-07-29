#include <string>

#include "Color.h"
#include "Player.h"
#include "Window.h"

using std::string;

Window::Window(WINDOW* w, Color& cm) :
	window(w), colormanager(&cm) {
}
