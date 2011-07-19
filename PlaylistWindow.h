#ifndef PLAYLISTWINDOW_H
#define PLAYLISTWINDOW_H

#include <string>

#include "ncurses.h"
#include "Playlist.h"
#include "Show.h"
#include "Window.h"


class PlaylistWindow : public Window {
	public:
		Playlist playlist;

		PlaylistWindow(){}
		PlaylistWindow(WINDOW* w);
		PlaylistWindow(WINDOW* w, Playlist& p);

		~PlaylistWindow(){}

		void command(const std::string& s);
		void control(const int c);
		void drawit();
		void input(std::string& s);
};

#endif
