#include <string>

#include "Color.h"
#include "ncurses.h"
#include "PlaylistWindow.h"

using std::string;

extern string& strinput(const char* prepend = "");

PlaylistWindow::PlaylistWindow(WINDOW* w, Color& cm, Playlist& p) :
 	Window(w,cm) {
	playlist = playlist;
	selection = playlist.begin();
	selectionoffset = 0;
}

PlaylistWindow::PlaylistWindow(WINDOW* w, Color& cm) : Window(w,cm) {
}

void PlaylistWindow::command(const string& s) {
}

void PlaylistWindow::control(const int c) {
	string s, f;
	switch (c) {
		case '\n':
			s = strinput();
			f = strinput();
			if(s.length() && f.length())
				addshow(s,f);
			break;
		case KEY_UP:
			if(selection != playlist.begin()) {
				--selection;
				--selectionoffset;
			}
			break;
		case KEY_DOWN:
			if(selection != playlist.end()-1) {
				++selection;
				++selectionoffset;
			}
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
	//mvwprintw(window,0,0,"%s",playlist.print().c_str());

	werase(window);
	unsigned int row = 0, rows, cols, count = 0;
	getmaxyx(window,rows,cols);

	for(auto i = playlist.begin(); i < playlist.end() && row < rows; ++i, ++row) {
		if(selection == i) {
			attron(COLOR_PAIR(colormanager->find("red")));
			mvwprintw(window, row, 0, "*%d %s", ++count, i->print().c_str());
			attroff(COLOR_PAIR(colormanager->find("red")));
		}
		else 
			mvwprintw(window, row, 0, " %d %s", ++count, i->print().c_str());
	}


	wrefresh(window);
}

void PlaylistWindow::addshow(string& name, string& file, unsigned short type) {
	playlist.add(Show(name,file,type));
	if(playlist.size() == 1) {
		selectionoffset = 0;
	}
	selection = playlist.begin() + selectionoffset;
}

