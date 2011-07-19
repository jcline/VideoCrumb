#ifndef WINDOW_H
#define WINDOW_H

#include "ncurses.h"
#include <string>

class Window{
	public:
		WINDOW* window;
		std::string name;

		Window(){}
		Window(WINDOW* w);
		Window(WINDOW* w, std::string n);
		Window(const Window& w);
		~Window() {}

		virtual void drawit() {}
		virtual void input(std::string s) {}

};

#endif
