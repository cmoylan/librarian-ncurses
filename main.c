#include <stdio.h>
#include "config.c"
#include "server.c"
#include "window.c"



/** main
 *
 *  It all starts here.
 */
int main(int argc, char *argv[])
{
  config_initialize();
  //fetch("books");
  //window_main();

  // TODO: giant case statement to parse command line options
  // TODO: break initialization functions out

  return 0;
}
