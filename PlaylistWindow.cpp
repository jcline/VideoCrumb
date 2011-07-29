#include <string>

#include "Color.h"
#include "ncurses.h"
#include "Player.h"
#include "PlaylistController.h"
#include "PlaylistWindow.h"

using std::string;

extern PlaylistController plc;
extern string* strinput(const char* prepend = "");

PlaylistWindow::PlaylistWindow(WINDOW* w, Color& cm, Player& p) :
 	Window(w,cm), player(&p) {
	if(plc.size()) 
		selection = plc.getselection()->begin();
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
		case KEY_DOWN:
			if(plc.size() && selection != plc.getselection()->end()-1) {
				++selection;
				++selectionoffset;
			}
			break;
		case KEY_RIGHT:
		case 'p':
			if(plc.size())
				player->play(selection->file);
		case 'r':
			//TODO: mark last played file
		default:
			break;
	}	
}

void PlaylistWindow::drawit() {
	werase(window);
	unsigned int row = 0, rows, cols, count = 0;
	getmaxyx(window,rows,cols);

	if(plc.size()) {
		for(auto i = plc.getselection()->begin();
			i < plc.getselection()->end() && row < rows; ++i, ++row) {
			if(selection == i) {
				attron(COLOR_PAIR(colormanager->find("red")));
				mvwprintw(window, row, 0, "*%d %s", ++count, i->print().c_str());
				attroff(COLOR_PAIR(colormanager->find("red")));
			}
			else 
				mvwprintw(window, row, 0, " %d %s", ++count, i->print().c_str());
		}
	}

	wrefresh(window);
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

