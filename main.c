#include "config.c"
#include "globals.h"
#include "server.c"
#include "window.c"

#include <stdio.h>


/**
 *  Main program that accepts and handles command line arguments
 *
 *  @return 0 if successful
 */
int main(int argc, char *argv[])
{
  config_initialize();
  fetch("books");
  //window_main();

  // TODO: giant case statement to parse command line options

  return 0;
}
