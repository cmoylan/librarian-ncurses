#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "window.c"

// Config vars
// TODO: move these into a config file
//char LIBRARIAN_URL[] = "http://localhost:8080/books.xml";
char LIBRARIAN_URL[] = "http://localhost:8080/bookshelves.xml";



void query_server(void)
// to stdout
size_t do_stuff( char *ptr, size_t size, size_t nmemb, void *userdata)
{
  //return fwrite(ptr, size, nmemb, userdata);
  printf("boom");
}


{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, LIBRARIAN_URL);

    // silence curl
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, do_stuff);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }
}

/** main
 *
 *  It all starts here.
 */
int main(int argc, char *argv[])
{
  query_server();

  return 0;
}
