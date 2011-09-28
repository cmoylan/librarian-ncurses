#include "globals.h"

#include <string.h>
#include <curl/curl.h>



char *LIBRARIAN_URL = "http://localhost:8080";
char *EXTENSION = ".xml";
char *DATA_DIR;

void query_server(char *path, size_t (*callback));
size_t process_results( char *ptr, size_t size, size_t nmemb, void *userdata);



void fetch(char *data_type)
{
  // TODO: could also use sprintf
  // Add 1 for the slash in the URL
  char path[
    strlen(LIBRARIAN_URL)
    + strlen(data_type)
    + strlen(EXTENSION)
    + 1];

  strcpy(path, LIBRARIAN_URL);
  strcat(path, "/");
  strcat(path, data_type);
  strcat(path, EXTENSION);

  printf("querying path: %s\n", path);
  query_server(path, process_results);

  // TODO: set the appropriate callback depending on what we're querying
}


/**
 *  basic query function
 */
void query_server(char *path, size_t (*callback))
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, path);

    // silence curl
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }
}


/**
 *  Write the xml data to a cachefile
 */
size_t process_results( char *ptr, size_t size, size_t nmemb, void *userdata)
{
  char *filename = "books.cache";
  char path[
    strlen(CONFIG_DIR)
    + strlen(filename)
    + 1];  // add 1 for slash
  FILE *file;

  sprintf(path, "%s/%s", CONFIG_DIR, filename);
  //printf("path in proc res is %s\n", path);

  file = fopen(path, "w");

  if (file != NULL) {
    fwrite(ptr, size, nmemb, file);
    fclose(file);
  }
}

