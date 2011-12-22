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
		// Adds a new playlist to the list of playlists
		void addplaylist(std::string& n);

		// Draws the column headers
		void drawheaders(unsigned int cols);

	public:
		ShowsWindow() {}
		ShowsWindow(WINDOW* w, Color& cm);
		~ShowsWindow() {}

		// Executes a vim-like command (TODO)
		void command(const std::string& s);
		// Interprets key presses and calls the correct functions
		void control(const int c);
		// Draws the window
		void drawit();

};

#endif
