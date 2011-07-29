#include <string>
#include <tuple>
#include <vector>

#include "ncurses.h"
#include "term.h"

#include "Color.h"
#include "Player.h"
#include "Playlist.h"
#include "PlaylistWindow.h"
#include "Settings.h"
#include "Show.h"
#include "ShowsWindow.h"
#include "Window.h"

using std::get;
using std::string;
using std::tuple;
using std::vector;

void draw();
void drawwin();
bool input();
string* strinput(const char* prepend = "");
void switchwin(const string& name);

Player player;
PlaylistController plc;
Window* dispwin;
tuple<PlaylistWindow,ShowsWindow,Settings> windows;

// Macros to make it easy to change window ordering
#define PLAYLISTWINDOW 0
#define SHOWSWINDOW 1
#define SETTINGSWINDOW 2

string winnames;

int main( int argc, char **argv) {

	setlocale(LC_ALL, "");

	initscr();
	cbreak();
	noecho();
	keypad( stdscr, TRUE );
	curs_set(0);

	// Setup colors
	Color colormanager;
	colormanager.add("red", COLOR_RED, COLOR_BLACK);

	// Setup windows
	windows = decltype(windows) ( 
		PlaylistWindow(newwin(0,0,1,0), colormanager, player),
		ShowsWindow(newwin(0,0,1,0), colormanager),
		Settings(newwin(0,0,1,0),colormanager)
	);

	// Window titlebar
	winnames = "Playlist Shows Edit Settings";

	// initial window to display
	dispwin = &get<SHOWSWINDOW>(windows);

	//TODO: deal with conf loading later
	player.setplayer("mplayer ");
	player.setarguments(" -vo vdpau ");
	player.setlatearguments(" &> /dev/null ");

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
	string* s;

	switch (in) {
		case KEY_ENTER:
		case 'q':
			return 0;
			break;

		case ':':
			s = strinput(":");
			if(s->length())
			{} //TODO: interpret command
			delete(s);
			break;
		
		case '1':
			dispwin = &get<PLAYLISTWINDOW>(windows);
			break;
		case '2':
			dispwin = &get<SHOWSWINDOW>(windows);
			break;
		case '3':
			dispwin = &get<2>(windows);
			break;
		case '4':
			//dispwin = &get<3>(windows);
			break;

		case ERR:
			break;
		default:
			dispwin->control(in);
	}

	drawwin();
	return 1;
}

/*
	Gets string input, location is the bottom of the given window.
*/
string* strinput(const char* prepend) {
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
	return str;
}


/*
	Switches to the window with the given name.
	@param name The name of the window to switch to.
*/
void switchwin(const string& name) {
	if(name == "Playlist")
		dispwin = &get<PLAYLISTWINDOW>(windows);
}
