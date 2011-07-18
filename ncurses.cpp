#include <string>
#include <vector>

#include "ncurses.h"
#include "term.h"

#include "Show.h"
#include "Playlist.h"

using std::string;
using std::vector;

void draw(WINDOW* win);
bool input(WINDOW* win);
string& strinput(WINDOW* win);

WINDOW* playlistwin;
Playlist playlist;


int main( int argc, char **argv) {

	initscr();
	cbreak();
	noecho();
	keypad( stdscr, TRUE );
	curs_set(0);

	playlistwin = newwin(0,0,1,0);
	keypad(playlistwin, TRUE);

	//TODO: deal with conf loading later

	while(input(playlistwin));

	endwin();

	return 0;
}

bool input(WINDOW* win) {
	int in = getch();
	string s;

	switch (in) {
		case KEY_ENTER:
		case '\n':
			s = strinput(win);
			if(s.length() > 0)
				playlist.add(Show(s));
			break;
		case 'q':
			return 0;
			break;
		case ERR:
			break;
	}

	draw(win);
	return 1;
}

string& strinput(WINDOW* win) {
	nocbreak();
	echo();
	curs_set(1);

	int row,col;
	getmaxyx(win,row,col);

	char cstr[col];
	for(int i = 0; i < col; ++i) cstr[i] = 0;

	mvwgetnstr(win,row-1,0,cstr,col-1);

	wmove(win,row-1,0);
	wclrtoeol(win);

	string* str = new string(cstr);

	curs_set(0);
	cbreak();
	noecho();
	return *str;
}

void draw(WINDOW* win) {
	mvwprintw(win,0,0,"%s",playlist.print().c_str());
	wrefresh(win);
}
