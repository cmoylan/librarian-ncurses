#include <string.h>
#include <curl/curl.h>


char *LIBRARIAN_URL = "http://localhost:8080";
char *EXTENSION = ".xml";
char *DATA_DIR;

void query_server(char *path);
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
  query_server(path);

  // TODO: initialize curl here
  // TODO: set the appropriate callback depending on what we're querying
}


/**
 *  basic query function
 */
void query_server(char *path)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, path);

    // silence curl
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, process_results);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }
}


/**
 *  do something with the data that comes back from the server
 */
size_t process_results( char *ptr, size_t size, size_t nmemb, void *userdata)
{
  return fwrite(ptr, size, nmemb, userdata);
}

