#ifndef PLAYLISTWINDOW_H
#define PLAYLISTWINDOW_H

#include <string>

#include "Color.h"
#include "ncurses.h"
#include "Player.h"
#include "Playlist.h"
#include "PlaylistController.h"
#include "Show.h"
#include "Window.h"

extern PlaylistController plc;

class PlaylistWindow : public Window {
	public:
		PlaylistWindow(){}
		PlaylistWindow(WINDOW* w, Color& cm, Player& p);

		~PlaylistWindow(){}

		// Executes a vim-like command (TODO)
		void command(const std::string& s);
		// Interprets key presses and calls the correct functions
		void control(const int c);
		// Draws the window
		void drawit();

	private:
		// A pointer to the player class for this playlist
		Player* player;

		// An iterator for the currently selected item in the playlist
		decltype(plc.getselection()->begin()) selection;
		// The offset of selection from plc.getselection()->begin()
		size_t selectionoffset;

		// Adds an item to the playlist
		void addshow(std::string& name, std::string& file, showtype type = EPISODE);
		// Deletes an item from the playlist
		void del();
		// Determines the item to select when we change playlists
		void selected();

		// Draws the column headers
		void drawheaders(unsigned int cols);

};

#endif
