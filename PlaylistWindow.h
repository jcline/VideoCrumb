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

		void command(const std::string& s);
		void control(const int c);
		void drawit();

	private:
		Player* player;
		decltype(plc.getselection()->begin()) selection;
		unsigned int selectionoffset;

		void addshow(std::string& name, std::string& file, showtype type = EPISODE);

};

#endif
