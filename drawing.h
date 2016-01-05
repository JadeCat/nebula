#include <ncurses.h>

void drawBorder();
void drawScreen();
void initialize();
void drawMenu(WINDOW *menu_win, int y, int x, char** names, int count, int highlight);
void tinyScreenError();
