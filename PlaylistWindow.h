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
		PlaylistWindow(WINDOW* w, std::string n = "") : Window(w,n) {}
		PlaylistWindow(WINDOW* w, Playlist& p, std::string n = "");
		PlaylistWindow(const PlaylistWindow& p);
		PlaylistWindow(const Window& w) : Window(w.window, w.name) {}

		~PlaylistWindow(){}

		void drawit();
		void input(std::string s);
};

#endif
