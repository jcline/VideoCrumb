#ifndef PLAYLISTWINDOW_H
#define PLAYLISTWINDOW_H

#include <string>

#include "Color.h"
#include "ncurses.h"
#include "Playlist.h"
#include "Show.h"
#include "Window.h"


class PlaylistWindow : public Window {
	public:
		Playlist playlist;

		PlaylistWindow(){}
		PlaylistWindow(WINDOW* w, Color& cm);
		PlaylistWindow(WINDOW* w, Color& cm, Playlist& p);

		~PlaylistWindow(){}

		void command(const std::string& s);
		void control(const int c);
		void drawit();

	private:
		decltype(playlist.begin()) selection;
		unsigned int selectionoffset;

		void addshow(std::string& name, std::string& file, unsigned short type = 0);

};

#endif
