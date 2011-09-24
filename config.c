#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


char *CONFIG_DIR;


void create_or_open_config_dir(void)
{
  // --- BEGIN initialization functions --- //
  char *home_dir;
  int rc;
  DIR *config_dir;

  home_dir = getenv("HOME");
  char config_dir_name[
    strlen(home_dir)
    + strlen("/.librarian")];
  sprintf(config_dir_name, "%s/.librarian", home_dir);
  CONFIG_DIR = config_dir_name;

  // TODO: rewrite this to be one level and move it into a function
  config_dir = opendir(CONFIG_DIR);
  //printf("config_Dir: %p\n", config_dir);
  if (config_dir == NULL) {
    // create it
    rc = mkdir(CONFIG_DIR, 0700);
    //printf("rc after mkdir: %d\n", rc);
    if (rc == 1) {
      // fail
    }
  } else {
    //printf("closing directory\n");
    closedir(config_dir);
  }

  // --- END initialization functions --- //
}


void config_initialize(void)
{
  create_or_open_config_dir();
}
