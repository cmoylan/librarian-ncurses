#include <ncurses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
  "Choice 1",
  "Choice 2",
  "Choice 3",
  "Choice 4",
  "Exit",
};
void func(char *name);


void window_menu(void)
{
  ITEM **my_items;
  int c;
  MENU *my_menu;
  int n_choices, i;
  ITEM *cur_item;

  // Initialize items
  n_choices = ARRAY_SIZE(choices);
  my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

  for(i = 0; i < n_choices; ++i) {
    my_items[i] = new_item(choices[i], choices[i]);
    set_item_userptr(my_items[i], func);
  }
  my_items[n_choices] = (ITEM *)NULL;

  // Create the menu
  my_menu = new_menu((ITEM **)my_items);

  // Post the menu
  mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
  mvprintw(LINES - 2, 0, "Up and Down arrow keys to navigate");
  mvprintw(LINES - 4, 0, "LINES: %d", LINES);
  post_menu(my_menu);
  refresh();

  while((c = getch()) != KEY_F(1)) {
    switch(c) {
      case KEY_DOWN:
        menu_driver(my_menu, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(my_menu, REQ_UP_ITEM);
        break;
      case 10: // Enter
      {
        ITEM *cur;
        void (*p)(char *);

        cur = current_item(my_menu);
        p = item_userptr(cur);
        p((char *)item_name(cur));
        pos_menu_cursor(my_menu);
        break;
      }
      break;
    }
  }

  // Cleanup
  unpost_menu(my_menu);
  for (i = 0; i < n_choices; ++i) {
    free_item(my_items[i]);
  }
  free_menu(my_menu);
}

/**
 *  Initialization function for the books pane
 */
void window_books_initialize(void)
{
  WINDOW *browser, *details, *status_line;
  char ch;

  browser = newwin(LINES-2, COLS/3, 0, 0);
  //box(browser, 0, 0);
  wprintw(browser, "This is teh browser");
  wrefresh(browser);

  details = newwin(LINES-2, (COLS/3)*2, 0, COLS/3);
  //box(details, 0, 0);
  wprintw(details, "These are the details");
  wrefresh(details);

  while((ch = getch()) != KEY_F(1)) {
    switch(ch) {
      case KEY_LEFT:
        wprintw(details, "Booh yah");
        wrefresh(details);
        break;
    }
  }
}


void window_initialize(void)
{
  // Initialize curses
  initscr();
  start_color();
  cbreak(); // line buffering disabled
  noecho(); // don't echo to stdscr
  keypad(stdscr, TRUE); // get Fx and arrow keys

  // Initialize the colors
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

  endwin();
}


void func(char *name)
{
  move(40, 0);
  clrtoeol();
  mvprintw(40, 0, "Item selected is %s", name);
}


void window_main(void)
{
  char ch;

  window_initialize();
  window_books_initialize();
  //window_menu();

  //printw("BLAH");
  //refresh();
  //while((ch = getch()) != KEY_F(1)) {

  //}
}
