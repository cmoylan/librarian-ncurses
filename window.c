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
// Function pointer to whichever function should handle getch() at any
// given moment.
void *(*GETCH_CALLBACK)(int key);
typedef struct _BookWindow_struct {
  WINDOW *browser;
  WINDOW *details;
  WINDOW *status_line;
} BookWindow;
BookWindow BOOK;


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
  //mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
  //mvprintw(LINES - 2, 0, "Up and Down arrow keys to navigate");
  //mvprintw(LINES - 4, 0, "LINES: %d", LINES);
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


void window_initialize(void)
{
  // Initialize curses
  initscr();
  start_color();
  cbreak(); // line buffering disabled
  noecho(); // don't echo to stdscr
  keypad(stdscr, TRUE); // get Fx and arrow keys

  // Initialize the colors
  //init_pair(1, COLOR_RED, COLOR_BLACK);
  //init_pair(2, COLOR_GREEN, COLOR_BLACK);
  //init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
}


void books_callback(int key)
{
  switch(key) {
    case 9:
      mvwaddstr(BOOK.browser, 5, 1, "Booh yah");
      wrefresh(BOOK.browser);
      break;
    case KEY_UP:
      //printw("blahhhh");
      //refresh();
      break;
    case 32:
      //wborder(details, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
      //werase(details);
      //wrefresh(details);
      //delwin(details);
      break;
   }
}


void window_books(void)
{
  WINDOW *details, *status_line;
  //BOOKS book;

  mvprintw(LINES-1, 0, "Press F1 to exit");
  refresh();

  // Create the windows
  BOOK.browser = newwin(LINES-2, COLS/3, 0, 0);
  box(BOOK.browser, 0, 0);
  mvwprintw(BOOK.browser, 0, 2, "[This is teh browser]");
  wrefresh(BOOK.browser);

  details = newwin(LINES-2, (COLS/3)*2, 0, COLS/3);
  //box(details, 0, 0);
  mvwprintw(details, 0, 2, "These are the details");
  wrefresh(details);

  // Set the main loop callback for this pane
  GETCH_CALLBACK = &books_callback;
}


void window_books_keypress(int key)
{
  printw("pressed key was: %d", key);
  refresh();
}


void func(char *name)
{
  move(40, 0);
  clrtoeol();
  mvprintw(40, 0, "Item selected is %s", name);
}


void window_main(void)
{
  int key;

  window_initialize();
  window_books();  // or whatever default pane is

  // For more control, change this line to:
  // while(PROGRAM_RUNNING)
  // where PROGRAM_RUNNING is a global that you can toggle anywhere
  while(key = getch()) {
    GETCH_CALLBACK(key);
  }

  // Cleanup functions
  endwin();
}
