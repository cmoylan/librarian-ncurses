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


int window_initialize(void)
{
  ITEM **my_items;
  int c;
  MENU *my_menu;
  int n_choices, i;
  ITEM *cur_item;

  // Initialize curses
  initscr();
  start_color();
  cbreak(); // line buffering disabled
  noecho(); // don't echo to stdscr
  keypad(stdscr, TRUE); // get Fx and arrow keys
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

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
  endwin();

  return 0;
}


void func(char *name)
{
  move(20, 0);
  clrtoeol();
  mvprintw(20, 0, "Item selected is %s", name);
}


void window_main(void)
{
  window_initialize();
}
