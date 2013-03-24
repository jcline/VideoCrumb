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
	plc.autoaddplaylist(n);
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
			if(!plc.empty()) {
				plc.go();
				switchwin("Playlist");
			}
			break;
    case 'd':
      del();
      break;
		case '/':
			s = strinput("/");
			for(auto i = plc.getdispselection(); i < plc.end(); ++i) {
				if( i->print().find(*s) != std::string::npos) {
					plc.offsetdispselection( i - plc.getdispselection() );
					drawit();
					break;
				}
			}
			delete(s);
			break;
		default:
			break;
	}
}

void ShowsWindow::del() {
  string* s = strinput("Are you sure you want to delete this item? [y/N] ");
  if (s->length()) {
    if (*s == "y" || *s == "Y") {
      plc.deleteselected();
      delete(s);
      auto i = plc.getdispselection()->begin() + plc.getdispoffset();
      auto j = plc.getdispselection()->end();
      if (distance(i, j)) {
        plc.offsetdispselection(-1);
      }
    }
  }
}

void ShowsWindow::drawit() {
	werase(window);

	unsigned int rows, cols, row = 3;
	getmaxyx(window,rows,cols);

	drawheaders(cols);

	for(auto i = plc.begin(); i < plc.end() && row < rows; ++i, ++row) {
		if(plc.getdispselection() == i) {
			wattr_on(window, COLOR_PAIR(colormanager->find("red")), NULL);
			mvwprintw(window,row,0,"%s",i->print().c_str());
			wattr_off(window, COLOR_PAIR(colormanager->find("red")), NULL);
		}
		else
			mvwprintw(window,row,0,"%s",i->print().c_str());
	}

	wrefresh(window);
}

void ShowsWindow::drawheaders(unsigned int cols) {
	mvwhline(window, 0, 0, ACS_HLINE, cols);
	mvwprintw(window, 1, 0, "Watched/Total\tName");
	mvwhline(window, 2, 0, ACS_HLINE, cols);
}
