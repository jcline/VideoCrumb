#include <string>

#include <ncurses.h>
#include "Playlist.h"
#include "PlaylistController.h"
#include "ShowsWindow.h"

using std::string;

extern PlaylistController plc;
extern string* strinput(const char* prepend = "");
extern void switchwin(const string& name);

ShowsWindow::ShowsWindow(WINDOW* w, Color& cm) : Window(w,cm) {
}

void ShowsWindow::addplaylist(string& n) {
	Playlist pl(n);
	plc.addplaylist(pl);
}

void ShowsWindow::command(const string& s) {
}

void ShowsWindow::control(const int c) {
	string* s;
	switch(c) {
		case '\n':
			s = strinput();
			if(s->length()) {
				addplaylist(*s);
			}
			break;
		case KEY_UP:
			plc.offsetdispselection(-1);
			break;
		case KEY_DOWN:
			plc.offsetdispselection(1);
			break;
		case KEY_RIGHT:
			plc.go();
			switchwin("Playlist");
			break;
		default:
			break;
	}
}

void ShowsWindow::drawit() {
	werase(window);

	unsigned int rows, cols, row = 0;
	getmaxyx(window,rows,cols);

	for(auto i = plc.begin(); i < plc.end() && row < rows; ++i, ++row) {
		if(plc.getdispselection() == i)
			mvwprintw(window,row,0,"*%s",i->print().c_str());
		else
			mvwprintw(window,row,0," %s",i->print().c_str());
	}


	wrefresh(window);
}
