#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>



// TODO: must be a better way to do this using pointers or something
char CONFIG_DIR[256];


void create_or_open_config_dir(void)
{
  char *home_dir;
  int rc;
  DIR *config_dir;

  home_dir = getenv("HOME");
  char config_dir_name[
    strlen(home_dir)
    + strlen("/.librarian")];
  sprintf(config_dir_name, "%s/.librarian", home_dir);

  // TODO: rewrite this to be one level and move it into a function
  config_dir = opendir(config_dir_name);
  //printf("config_Dir: %p\n", config_dir);
  if (config_dir == NULL) {
    // create it
    rc = mkdir(config_dir_name, 0700);
    //printf("rc after mkdir: %d\n", rc);
    if (rc == 1) {
      // fail
    }
  } else {
    //printf("closing directory\n");
    closedir(config_dir);
  }

  // Copy the config directory into a global variable
  strncpy(CONFIG_DIR, config_dir_name, sizeof(CONFIG_DIR));
}


//void config_initialize(void)
//{
//  create_or_open_config_dir();
//}
