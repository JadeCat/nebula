#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>
#include <locale.h>
#include <string.h>

#include "drawing.h"

#define MIN_LINES	16
#define MIN_COLS	64

void initialize()
{
	initscr();
	keypad(stdscr, TRUE);
	use_default_colors();
	raw();
	nonl();
	noecho();

	start_color();
	curs_set(0);

	init_pair(1, COLOR_WHITE,	-1);
	init_pair(2, COLOR_RED,		-1);
	init_pair(3, COLOR_GREEN,	-1);
	init_pair(4, COLOR_YELLOW,	-1);
	init_pair(5, COLOR_BLUE,	-1);
	init_pair(6, COLOR_CYAN,	-1);
	init_pair(7, COLOR_MAGENTA,	-1);

	attrset(COLOR_PAIR(1));
}

void drawBorder()
{
	border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

	for(int i=1; i<COLS -1; i++)
		for(int j=1; j<LINES -1; j++)
			mvaddstr(j, i,	" ");
}

void drawScreen()
{
	if(COLS < MIN_COLS || LINES < MIN_LINES)
	{
		tinyScreenError();
		return;
	}


	drawBorder();
	refresh();
}

void drawMenu(WINDOW *menu_win, char** names, int count, int highlight)
{
	for(int i=0; i<count; i++)
		if(i == highlight)
		{
			wattron(menu_win, A_REVERSE);
			mvwaddstr(menu_win,i,0,names[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwaddstr(menu_win,i,0,names[i]);
}

void tinyScreenError()
{
	for(int i=0; i<COLS; i++)
		for(int j=0; j<LINES; j++)
			mvaddstr(j, i,	" ");

	mvprintw(0,0,"%dx%d min, sorry ;_;", MIN_COLS, MIN_LINES);
}
