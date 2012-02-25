#include <string>
#include <cstdio>

#include "Color.h"
#include "ncurses.h"
#include "Player.h"
#include "PlaylistController.h"
#include "PlaylistWindow.h"

using std::string;

extern PlaylistController plc;
extern string* strinput(const char* prepend = "");

template<typename... T>
static void dispmsg( WINDOW* win, const char* fmt, T... args) {
	int rows, cols;
	getmaxyx ( win, rows,   cols );
	mvwprintw( win, rows-1, 0, fmt, args... );
}

PlaylistWindow::PlaylistWindow(WINDOW* w, Color& cm, Player& p) :
 	Window(w,cm), player(&p) {
	if(plc.size()) {
		selection = plc.getselection()->begin();
		selectionoffset = 0;
	}
}

void PlaylistWindow::command(const string& s) {
}

void PlaylistWindow::control(const int c) {
	string *s, *f;
	switch (c) {
		case '\n':
			// This is a bit of a mess =/
			s = strinput();
			if(s->length()) {
				f = strinput();
				if(f->length()) {
					addshow(*s,*f);
				}
			}
			delete(s);delete(f); // strinput() uses new
			break;
		case KEY_LEFT:
		case 'u':
			//TODO: unmark last played file
		case KEY_UP:
			if(plc.size() && selection != plc.getselection()->begin()) {
				--selection;
				--selectionoffset;
			}
			break;
		case KEY_RIGHT:
		case 'p':
			if(plc.size()) {
				player->play(selection->file);
				selection->watch();
				plc.getselection()->change();
			}
		case 'r':
		case KEY_DOWN:
			if(plc.size() && selection != plc.getselection()->end()-1) {
				++selection;
				++selectionoffset;
			}
			break;
		case 'd':
			del();
			break;
		case 'w':
			selection->watch();
			break;
		case '/':
			s = strinput("/");
			{
				auto i = selection;
				for(; i < plc.getselection()->end(); ++i) {
					if( i->print().find(*s) != std::string::npos) {
						selection = i;
						drawit();
						break;
					}
				}
				if(i == plc.getselection()->end()) {
					dispmsg(stdscr, "Could not find \"%s\"", s->c_str());
				}
			}
			delete(s);
			break;
		default:
			break;
	}	
}

void PlaylistWindow::del() {
	string* s = strinput("Are you sure you want to delete this item? [y/N] ");
	if(s->length()) {
		if(*s == "y" || *s == "Y") {
			plc.getselection()->deleteselection(selection);
			delete(s);
			selection = plc.getselection()->begin();
			auto i = selection + selectionoffset, j = plc.getselection()->end();
			selection = (i < j) ? i : j-1;
		}
	}
}

void PlaylistWindow::drawit() {
	werase(window);
	unsigned int row = 3, rows, cols, count = 0;
	getmaxyx(window,rows,cols);

	drawheaders(cols);

	size_t offset = 0;
	if(plc.getselection()->size() > rows) {
		size_t center = (rows-row)/2;
		if(selectionoffset > center) {
			offset = selectionoffset - center;
		}
		if(plc.getselection()->size() - offset < (rows-row)) {
			offset -= (rows-row) - (plc.getselection()->size() - offset);
		}
		count = offset;
	}

	if(plc.size()) {
		for(auto i = plc.getselection()->begin() + offset;
			i < plc.getselection()->end() && row < rows; ++i, ++row) {

			if(selection == i) {
				wattr_on ( window, COLOR_PAIR(colormanager->find("red")), NULL);
				mvwprintw( window, row, 0, "%d\t%s", ++count, i->print().c_str());
				mvwprintw( window, row, cols - 3, "[%d]", i->getwatched());
				wattr_off( window, COLOR_PAIR(colormanager->find("red")), NULL);
			}
			else {
				mvwprintw( window, row, 0, "%d\t%s", ++count, i->print().c_str());
				mvwprintw( window, row, cols - 3, "[%d]", i->getwatched());
			}

		}
	}

	wrefresh(window);
}

void PlaylistWindow::drawheaders(unsigned int cols) {
	mvwhline ( window, 0, 0, ACS_HLINE, cols);
	mvwprintw( window, 1, 0, "#\tName");
	mvwprintw( window, 1, cols - strlen("Watched"), "Watched");
	mvwhline ( window, 2, 0, ACS_HLINE, cols);
}

void PlaylistWindow::selected() {
	// Find the first unwatched in this session of watching
	// That is, the first show that we have watched less than the prior shows
	selection = plc.getselection()->first();
	selectionoffset = selection - plc.getselection()->begin();
}

void PlaylistWindow::addshow(string& name, string& file, showtype type) {
	if(plc.size()) {
		Show s(file,name,type);
		plc.getselection()->add(s);
		if(plc.getselection()->size() == 1) {
			selectionoffset = 0;
		}
		selection = plc.getselection()->begin() + selectionoffset;
	}
}

