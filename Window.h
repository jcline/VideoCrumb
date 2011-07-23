#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "Color.h"
#include "ncurses.h"

class Window{
	public:
		WINDOW* window;
		Color* colormanager;

		Window() {}
		Window(WINDOW* w, Color& cm);
		~Window() {}

		virtual void command(const std::string& s) {}
		virtual void control(const int c) {}
		virtual void drawit() {}

};

#endif
