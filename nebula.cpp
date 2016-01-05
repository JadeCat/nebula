#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>
#include <locale.h>
#include <string.h>

#include "drawing.h"

void finish(int sig);

int main (int argc, char **argv)
{
	setlocale(LC_ALL, "");
	initialize();

	drawScreen();

	char c;
	
	char *menu[] = {"Start",
					"About",
					"Quit"};
	int highlight = 0;
	int count = 3;

	while((c = getch()) != 'q')
	{
		switch(c)
		{
		case (char)KEY_UP:
			highlight = (highlight -1 +count) % count;
			break;
		case (char)KEY_DOWN:
			highlight = (highlight +1) % count;
			break;
		case 13: // for some reason KEY_ENTER is 'W'. Yes, really.
			if(2 == highlight)
				finish(0);
			break;
		}
		drawScreen();

		drawMenu(stdscr, menu, count, highlight);
	}

	finish(0);
	return EXIT_FAILURE;
}

void finish(int sig)
{
	endwin();

	exit(EXIT_SUCCESS);
}
