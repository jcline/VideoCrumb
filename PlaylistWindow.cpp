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
	unsigned int row = 0, rows, cols, count = 0;
	getmaxyx(window,rows,cols);

	size_t offset = 0;
	if(plc.getselection()->size() > rows) {
		size_t center = rows/2;
		if(selectionoffset > center) {
			offset = selectionoffset - center;
		}
		if(plc.getselection()->size() - offset < rows) {
			offset -= rows - (plc.getselection()->size() - offset);
		}
		count = offset;
	}

	if(plc.size()) {
		for(auto i = plc.getselection()->begin() + offset;
			i < plc.getselection()->end() && row < rows; ++i, ++row) {

			if(selection == i) {
				attron(COLOR_PAIR(colormanager->find("red")));
				mvwprintw(window, row, 0, "*%d\t%s", ++count, i->print().c_str());
				attroff(COLOR_PAIR(colormanager->find("red")));
			}
			else 
				mvwprintw(window, row, 0, " %d\t%s", ++count, i->print().c_str());

		}
	}

	wrefresh(window);
}

void PlaylistWindow::selected() {
	if(selection < plc.getselection()->begin() ||
			selection >= plc.getselection()->end())
	{
		selection = plc.getselection()->begin();
		selectionoffset = 0;
	}
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

