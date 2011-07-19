#ifndef WINDOW_H
#define WINDOW_H

#include "ncurses.h"
#include <string>

class Window{
	public:
		WINDOW* window;

		Window(){}
		Window(WINDOW* w);
		~Window() {}

		virtual void command(const std::string& s) {}
		virtual void control(const int c) {}
		virtual void drawit() {}
		virtual void input(std::string& s) {}

};

#endif
