#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "ncurses.h"
#include "term.h"

#include "Color.h"
#include "Player.h"
#include "Playlist.h"
#include "Show.h"
#include "Window.h"

#include "DatabaseManager.h"

#include "PlaylistController.h"
#include "SettingsController.h"

#include "PlaylistWindow.h"
#include "SettingsWindow.h"
#include "ShowsWindow.h"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

using std::cerr;
using std::get;
using std::string;
using std::tuple;
using std::vector;

void draw();
void drawwin();
bool input();
string* strinput(const char* prepend);
void switchwin(const string& name);

Color colormanager;
Player player;
DatabaseManager dbm;
PlaylistController plc;
SettingsController sc;
Window* dispwin;
// No stupid polymorphism games to stick the windows into a vector
tuple<
  PlaylistWindow,
	ShowsWindow,
	SettingsWindow
	>
windows;

// Macros to make it easy to change window ordering
#define PLAYLISTWINDOW 0
#define SHOWSWINDOW 1
#define SETTINGSWINDOW 2

vector<string> winnames; // Since there is no good way to iterate over a tuple
auto winsel = winnames.begin();

int main(int argc, char **argv) {

	{
		boost::filesystem::path config_file, data_dir;
		namespace po = boost::program_options;

		po::options_description desc("Arguments:");
		desc.add_options()
			("help", "Display this message.")
			("config", po::value<std::string>(),
				"The location of the configuration file, default $XDG_CONFIG_HOME")
			("data_dir", po::value<std::string>(),
				"The location to store the database, default $XDG_DATA_HOME")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if(vm.count("help")) {
			std::cout << desc << '\n';
			return 0;
		}

		if(vm.count("config"))
			config_file =  vm["config"].as<std::string>();
		else
			config_file = "";
		if(vm.count("data_dir"))
			data_dir = vm["data_dir"].as<std::string>();
		else
			data_dir = "";

		sc.load(config_file, data_dir);
	}

	if(!plc.loaddb()) {
		cerr << "Failed to read database\n";
		return 1;
	}


	// Setup ncurses
	setlocale(LC_ALL, "");

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	// Setup colors
	colormanager.init();
	colormanager.add("red", COLOR_RED, COLOR_BLACK);
	colormanager.add("blue", COLOR_BLUE, COLOR_BLACK);

	// Setup windows
	int cols, rows;
	getmaxyx(stdscr, rows, cols);
	windows = decltype(windows) (
		PlaylistWindow(newwin(rows-2, 0, 1, 0), colormanager, player),
		ShowsWindow   (newwin(rows-2, 0, 1, 0), colormanager),
		SettingsWindow(newwin(rows-2, 0, 1, 0), colormanager)
	);

	// Window titlebar
	winnames = {
		"Playlist", 
		"Shows", 
		"Edit", 
		"Settings"
	};

	// initial window to display
	dispwin = &get<SHOWSWINDOW>(windows);
	winsel = winnames.begin() + SHOWSWINDOW;

	//TODO: deal with conf loading later
	player.setplayer("mplayer ");
	player.setarguments(" -vo vdpau ");
	player.setlatearguments(" &> /dev/null ");

	// draw() must come before drawwin()
	draw();
	drawwin();
	while(input());

	endwin();

	plc.savedb();

	return 0;
}

/*
	Draws stdscr.
*/
void draw() {
	move(0,0);
#if __GNUC__ <= 4 && __GNUC_MINOR__ < 6
	size_t size = winnames.size();
	for(size_t i = 0; i < size; ++i) {
		if(winnames[i] == *winsel) {
			attron(COLOR_PAIR(colormanager.find("blue")));
			printw("%s ", winnames[i].c_str());
			attroff(COLOR_PAIR(colormanager.find("blue")));
		}
		else
			printw("%s ", winnames[i].c_str());
	}
#else
	for(string &n : winnames) {
		if(n == *winsel) {
			attron(COLOR_PAIR(colormanager.find("blue")));
			printw("%s ", n.c_str());
			attroff(COLOR_PAIR(colormanager.find("blue")));
		}
		else
			printw("%s ", n.c_str());
	}
#endif
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
			switchwin("Playlist");
			break;
		case '2':
			switchwin("Shows");
			break;
		case '3':
			switchwin("Edit");
			break;
		case '4':
			switchwin("Settings");
			break;
		case 's':
			plc.savedb();
			break;
		case KEY_RESIZE:
			draw();
			dispwin->resize();
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

	int rows, cols;
	getmaxyx(stdscr, rows, cols);

	char* cstr = new char[cols];
	memset(cstr, 0, cols);

	mvwprintw(stdscr, rows-1, 0, "%s", prepend);
	wgetnstr (stdscr, cstr,   cols-1);

	wmove    (stdscr, rows-1, 0);
	wclrtoeol(stdscr);

	string* str = new string(cstr);
	delete[] cstr;

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
	if(name == "Playlist") {
		dispwin = &get<PLAYLISTWINDOW>(windows);
		dispwin->selected();
		winsel = winnames.begin() + PLAYLISTWINDOW;
	}
	else if(name == "Shows") {
		dispwin = &get<SHOWSWINDOW>(windows);
		dispwin->selected();
		winsel = winnames.begin() + SHOWSWINDOW;
	}
	else if(0 && name == "Edit") {
		//dispwin = &get<EDITWINDOW>(windows);
		//dispwin->selected();
		//winsel = winnames.begin() + EDITWINDOW;
	}
	else if(name == "Settings") {
		dispwin = &get<SETTINGSWINDOW>(windows);
		dispwin->selected();
		winsel = winnames.begin() + SETTINGSWINDOW;
	}
	draw();
}
