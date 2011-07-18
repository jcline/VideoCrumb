#include <string>
#include <vector>

#include "ncurses.h"
#include "term.h"

#include "Show.h"
#include "Playlist.h"

using std::string;
using std::vector;

void draw();
void drawwin();
bool input();
string& strinput();

WINDOW* dispwin;
struct wind{
	WINDOW* win;
	string name;
};

vector<wind> windows;

Playlist* playlist;


int main( int argc, char **argv) {

	setlocale(LC_ALL, "");

	initscr();
	cbreak();
	noecho();
	keypad( stdscr, TRUE );
	curs_set(0);

	{ // We don't want to keep around names any longer than necessary
		string names[] = {"Playlist", "Shows", "Edit"}; 
		windows.reserve(sizeof(names)/sizeof(string)); // Allocate space in vector
		for(string s: names) {
			wind n;
			n.win = newwin(0,0,1,0);
			n.name = s;
			windows.push_back(n);
			keypad(windows.back().win, TRUE);
		}
	}
	dispwin = windows.front().win;
	playlist = new Playlist();


	//TODO: deal with conf loading later

	draw();
	while(input());

	endwin();

	return 0;
}

/*
	Draws stdscr.
*/
void draw() {
	move(0,0);
	for(wind &i: windows) {
		if(i.win == dispwin)
			printw("%s ", i.name.c_str());
		else
			printw("%s ", i.name.c_str());
	}
}

/*
	Draws a given window.
*/
void drawwin() {
	mvwprintw(dispwin,0,0,"%s",playlist->print().c_str());
	wrefresh(dispwin);
}

/*
	Control inputs (up/down/add, etc).
*/
bool input() {
	int in = getch();
	string s;

	switch (in) {
		case KEY_ENTER:
		case '\n':
			s = strinput();
			if(s.length() > 0)
				playlist->add(Show(s));
			break;
		case 'q':
			return 0;
			break;
		case ERR:
			break;
	}

	drawwin();
	return 1;
}

/*
	Gets string input, location is the bottom of the given window.
*/
string& strinput() {
	nocbreak();
	echo();
	curs_set(1);

	int row,col;
	getmaxyx(dispwin,row,col);

	char cstr[col];
	for(int i = 0; i < col; ++i) cstr[i] = 0;

	mvwgetnstr(dispwin,row-1,0,cstr,col-1);

	wmove(dispwin,row-1,0);
	wclrtoeol(dispwin);

	string* str = new string(cstr);

	curs_set(0);
	cbreak();
	noecho();
	return *str;
}

