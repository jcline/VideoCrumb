#ifndef SHOWSWINDOW_H
#define SHOWSWINDOW_H

#include <string>
#include <vector>

#include "Color.h"
#include "ncurses.h"
#include "Player.h" // TODO: enable per show players
#include "Playlist.h"
#include "Window.h"

class ShowsWindow : public Window{

	private:
		void addplaylist(std::string& n);

	public:
		ShowsWindow() {}
		ShowsWindow(WINDOW* w, Color& cm);
		~ShowsWindow() {}

		void command(const std::string& s);
		void control(const int c);
		void drawit();

};

#endif
