#include "headers/Show.h"
#include "headers/helperfunctions.h"

#include "ncurses.h"

#define SEL ( distance( shows.begin(), show ) )
#define DISP ( distance( top_display, show ) )

static vector<Show> shows;
static vector<Show>::iterator show;
static vector<Show>::iterator top_display;

void addShow();
void findNext();
bool input();
void moveDown();
void moveUp();
void playSelNext();
void unPlay();
string& readInput();
void showWindow();
void selDown(); 
void selPageDown();
void selPageUp();
void selUp();


void readdir() {
	string base("/home/vil/Anime/");
	vector<string> dirs = getDirDirs( base );
	vector<string>::iterator idirs;
	for( idirs = dirs.begin(); idirs < dirs.end(); ++idirs ) {
		Show s( *idirs );
		shows.reserve( shows.size() + 1 );
		s.add( makeSeasonFromDir( base, *idirs ) );
		shows.push_back( s );
	}
}



int main ( int argc, char **argv ) {

	/* Initialize ncurses */
	initscr();
	cbreak();
	noecho();
	keypad( stdscr, TRUE );
	curs_set(0);

	readconf();
	shows = readdb();
//	readdir();
	if( shows.size() > 0 ) {
		show = shows.begin();
		top_display = shows.begin();
	}

	showWindow();
	while ( input() );

	endwin();

	return 0;
}

bool input() {

	int in = getch();

	switch (in) {
		case KEY_DOWN:
			selDown();
			break;
		case KEY_UP:
			selUp();
			break;
		case KEY_NPAGE:
			selPageDown();
			break;
		case KEY_PPAGE:
			selPageUp();
			break;
		case '/':
			findNext();
			break;
		case 10:
			addShow();
			break;
		case 'p':
			in = getch();
			in -= 48;
			if( in > 0 && in < 10 )
				for( ; in > 0; --in )
					playSelNext();
			break;
		case 'n':
			playSelNext();
			break;
		case 'b':
			unPlay();
			break;
		case 'q':
			savedb( shows );
			return 0;
	}

	return 1;
}

void addShow() {
	string str = readInput();

	Show s(str);
	s.add( makeSeasonFromDir( "/home/vil/Anime/", str ) );

//	int tmp = SEL;

	shows.reserve( shows.size() + 1 );
	shows.push_back(s);

	show = shows.begin()/* + tmp */;
	top_display = shows.begin();

	sortShows( shows, ALPHA );
	clear();
	showWindow();
	savedb(shows);
}

void findNext() {
	vector<Show>::iterator it;
	string str = readInput();

	for( it = show; it < shows.end(); ++it) {
		if( str.compare( (size_t) 0, str.length(), 
				it->printName(), (size_t) 0, str.length() ) == 0 ) {
			show = it;
			if( DISP > LINES - 1 ) {
				top_display = show;
				if( distance( top_display, shows.end() ) < LINES )
					top_display = shows.end() - LINES;
			}
			break;
		}
	}
	clear();
	showWindow();
}

void playSelNext() {
	def_prog_mode();
	endwin();
	show->playNext();
	reset_prog_mode();
	clear();
	showWindow();
	savedb( shows );
}

void unPlay() {
	show->unPlay();
	mvprintw( DISP, 2, "%s", show->print().c_str() );
}

void selDown() {
	if( show < shows.end() -1 ) {
		if( DISP == LINES - 1 ) {
			++top_display;
			++show;
			clear();
			showWindow();
		}
		else {
			mvprintw( DISP, 0, " " );
			++show;
			mvprintw( DISP, 0, "*" );
		}
	}
}

void selPageDown() {
	if( show < shows.end() - 11 ) {
		if( DISP == LINES - 1 ) {
			top_display += 10;
			show += 10;
			clear();
			showWindow();
		}
		else {
			mvprintw( DISP, 0, " " );
			show += 10;
			mvprintw( DISP, 0, "*" );
		}
	}
	else if( show < shows.end() - 1 ){
		top_display = shows.end() - LINES ;
		show = shows.end() - 1;
		clear();
		showWindow();
	}
}

void selPageUp() {
	if( show > shows.begin() + 10 ) {
		if( DISP == 0 ) {
			top_display -= 10;
			show -= 10;
			clear();
			showWindow();
		}
		else {
			mvprintw( DISP, 0, " " );
			show -= 10;
			mvprintw( DISP, 0, "*" );
		}
	}
	else if( top_display > shows.begin() ) {
		top_display = shows.begin();
		show = shows.begin();
		clear();
		showWindow();
	}
}

void selUp() {
	if( show > shows.begin() ) {
		if( DISP == 0 ) {
			--top_display;
			--show;
			clear();
			showWindow();
		}
		else {
			mvprintw( DISP, 0, " " );
			--show;
			mvprintw( DISP, 0, "*" );
		}
	}
}

void showWindow() {
	vector<Show>::iterator it;
//	clear();
	int y;
	for( y = 0, it = top_display;
		  	it < shows.end() && y < LINES;
		  	++it, ++y ) {
		if( show == it )
			mvprintw( y, 0, "*" );
		mvprintw( y, 2, "%s", it->print().c_str() );
	}
	refresh();
}

string& readInput() {
	string *str = new string();
	int x, y;
	move (LINES - 1, 0);
	curs_set(1);
	int in = getch();

	while (in != 10) {
		if( in == 8 || in == 127 ) {
			*str = (*str).substr( 0, (*str).length() - 1 );
			getyx(stdscr,y,x);
			move(y,x-1);
		}
		else if ( (in > 31 && in < 127) || in > 127 ){
			(*str).push_back( in );
			addch(in);
		}
		in = getch();
	}

	curs_set(0);
	move( LINES-1 ,0 );
	clrtoeol();
	return *str;
}

