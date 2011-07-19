#include <string>
#include "ncurses.h"
#include "PlaylistWindow.h"

using std::string;

extern string& strinput(const char* prepend = "");

PlaylistWindow::PlaylistWindow(WINDOW* w, Playlist& p) :
 	Window(w) {
	playlist = playlist;
}

PlaylistWindow::PlaylistWindow(WINDOW* w) : Window(w) {
}

void PlaylistWindow::command(const string& s) {
}

void PlaylistWindow::control(const int c) {
	string s;
	switch (c) {
		case '\n':
			s = strinput();
			if(s.length())
				input(s);
			break;
		case KEY_UP:
			break;
		case KEY_DOWN:
			break;
		case KEY_RIGHT:
			break;
		case KEY_LEFT:
			break;
		default:
			break;
	}	
}

void PlaylistWindow::drawit() {
	mvwprintw(window,0,0,"%s",playlist.print().c_str());
	wrefresh(window);
}

void PlaylistWindow::input(string& s) {
	playlist.add(Show(s));
}


