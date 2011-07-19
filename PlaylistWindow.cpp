#include <string>
#include "ncurses.h"
#include "PlaylistWindow.h"

using std::string;

PlaylistWindow::PlaylistWindow(WINDOW* w, Playlist& p, string n) :
 	Window(w,n) {
	playlist = playlist;
}

PlaylistWindow::PlaylistWindow(const PlaylistWindow& p) :
 	Window(p.window,p.name) {
	playlist = p.playlist;
}

void PlaylistWindow::drawit() {
	mvwprintw(window,0,0,"%s",playlist.print().c_str());
	wrefresh(window);
}

void PlaylistWindow::input(string s) {
	playlist.add(Show(s));
}


