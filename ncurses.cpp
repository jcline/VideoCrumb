
#include <string>
#include <vector>

#include "ncurses.h"
#include "term.h"

#include "Show.h"

using std::string;
using std::vector;

bool input();
string& strinput();


int main( int argc, char **argv) {

	initscr();
	cbreak();
	noecho();
	keypad( stdscr, TRUE );
	curs_set(0);

	while(input());

	endwin();

	return 0;
}

bool input() {
	int in = getch();

	switch (in) {
		case KEY_ENTER:
		case '\n':
			strinput();
			break;
		case 'q':
			return 0;
			break;
		case ERR:
			break;
	}

	return 1;
}

string& strinput() {
	string *str = new string();

	int x = 0,
			y = LINES -1;
	move( y,x );
	clrtoeol();
	curs_set(1);

	int in = getch();

	while( in != KEY_ENTER && in != KEY_CANCEL &&
			in != ERR && in != '\n' ) {
		switch (in) {
			case KEY_BACKSPACE:
			case 8:
			case 127:
				if( str->length() ) {
					str->erase( str->end()-1 );
					move( y,--x );
					clrtoeol();
				}
				break;
			default:
				*str+=(char)in;
				echochar(in);
				++x;
		}
			
		in = getch();
	}
	if( in == KEY_CANCEL || in == ERR )
		*str = "";

	curs_set(0);
	return *str;
}
