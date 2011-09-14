#include <ncurses.h>

void ui(void)
{
  initscr();
  printw("Hello World!!!");
  refresh();
  getch();
  endwin();
}
