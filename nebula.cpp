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

	char c;
	
	char *menu[] = {"Start",
					"Continue",
					"About",
					"Quit"};
	
	int highlight = 0;
	int count = 4;

	char *title[] = {"           #         #",
					 "           #         #",
					 " ###  ###  ###  #  # #  ###",
					 " #  # #  # #  # #  # # #  #",
					 " #  # #### #  # #  # # #  #",
					 " #  # #    #  # #  # # # ##",
					 " #  #  ###  ##   ### #  # #",
					 "",
					 "############################"};
	
	int titleCount = 9;

	drawScreen();
	drawMenu(stdscr, LINES/2 -7, COLS/2 -14, title, titleCount, -1);
	drawMenu(stdscr, LINES/2 +3, COLS/2 -3, menu, count, highlight);

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
			if(3 == highlight)
				finish(0);
			break;
		case (char)KEY_RESIZE:
			break;
		}
		drawScreen();

		drawMenu(stdscr, LINES/2 -7, COLS/2 -14, title, titleCount, -1);
		drawMenu(stdscr, LINES/2 +3, COLS/2 -3, menu, count, highlight);
	}

	finish(0);
	return EXIT_FAILURE;
}

void finish(int sig)
{
	endwin();

	exit(EXIT_SUCCESS);
}
