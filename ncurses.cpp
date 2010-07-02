
#include "ncurses.h"
#include "Show.h"

bool input();

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
	unsigned int in = getch();

	switch (in) {
		case 'q':
			return 0;
			break;
	}

	return 1;
}
