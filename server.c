#include "globals.h"

#include <string.h>
#include <curl/curl.h>



char *LIBRARIAN_URL = "http://localhost:8080";
char *EXTENSION = ".xml";
char *DATA_DIR;
char BOOKS_CACHE[256];

void query_server(char *path, size_t (*callback));
size_t process_results( char *ptr, size_t size, size_t nmemb, void *userdata);
void create_cache_file_paths(void);



// .cachefiles we will have: books, bookshelves, checkouts



void fetch(char *data_type)
{
  FILE *file;
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

  create_cache_file_paths();

  printf("querying path: %s\n", path);
  // Clear the .cache files
  //file = fopen(BOOKS_CACHE, "w");
  //fclose(file);
  //query_server(path, process_results);

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
  printf("books cache in proc res is %s\n", BOOKS_CACHE);
  FILE *file;
  int write_size;

  file = fopen(BOOKS_CACHE, "a");
  clearerr(file);

  if (file != NULL) {
    write_size = fwrite(ptr, size, nmemb, file);
    fclose(file);
  }

  return write_size;
}


/**
 *  Create the .cache file paths
 **/
void create_cache_file_paths(void)
{
  char books[] = "books.cache";
  char books_path[
    strlen(CONFIG_DIR)
    + strlen(books)
    + 1];  // add 1 for slash

  sprintf(books_path, "%s/%s", CONFIG_DIR, books);
  strncpy(BOOKS_CACHE, books_path, sizeof(BOOKS_CACHE));
  printf("books cache is %s: \n", BOOKS_CACHE);

  // TODO: also do this for bookshelves and checkouts
}
