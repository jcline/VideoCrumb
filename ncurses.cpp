#include <string>
#include <tuple>
#include <vector>

#include "ncurses.h"
#include "term.h"

#include "Show.h"
#include "Playlist.h"
#include "Player.h"
#include "Window.h"
#include "PlaylistWindow.h"

using std::get;
using std::string;
using std::tuple;
using std::vector;

void draw();
void drawwin();
bool input();
string& strinput(const char* prepend = "");

Window* dispwin;
tuple<PlaylistWindow> windows;

string winnames;

int main( int argc, char **argv) {

	setlocale(LC_ALL, "");

	initscr();
	cbreak();
	noecho();
	keypad( stdscr, TRUE );
	curs_set(0);

	/*
	{ // We don't want to keep around names any longer than necessary
		string names[] = {"Playlist", "Shows", "Edit", "Settings"}; 
		for(string s: names) {
			windows.( Window(newwin(0,0,1,0), s) );
			keypad(windows.back().window, TRUE);
		}

		PlaylistWindow p = windows[0];
	}*/

	windows = decltype(windows) ( PlaylistWindow(newwin(0,0,1,0), "Playlist") );
	winnames = "Playlist Shows Edit Settings";

	dispwin = &get<0>(windows);


	//TODO: deal with conf loading later

	drawwin();
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
	printw("%s", winnames.c_str());
	refresh();
}

/*
	Draws a given window.
*/
void drawwin() {
	dispwin->drawit();
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
				dispwin->input(s);
			break;
		case 's':
			break;
		case 'p':
			break;
		case 'q':
			return 0;
			break;

		case ':':
			s = strinput(":");
			if(s.length() > 0)
			{} //TODO: interpret command
			break;
		
		case '1':
			dispwin = &get<0>(windows);
			break;
		case '2':
			//dispwin = get<1>(windows);
			break;
		case '3':
			//dispwin = get<2>(windows);
			break;
		case '4':
			//dispwin = get<3>(windows);
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
string& strinput(const char* prepend) {
	nocbreak();
	echo();
	curs_set(1);

	int row,col;
	getmaxyx(dispwin->window,row,col);

	char cstr[col];
	for(int i = 0; i < col; ++i) cstr[i] = 0;

	mvwprintw(dispwin->window,row-1,0,"%s",prepend);
	wgetnstr(dispwin->window,cstr,col-1);

	wmove(dispwin->window,row-1,0);
	wclrtoeol(dispwin->window);

	string* str = new string(cstr);

	curs_set(0);
	cbreak();
	noecho();
	return *str;
}

