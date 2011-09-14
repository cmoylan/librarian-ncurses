#include <stdio.h>
#include <curl/curl.h>
#include "window.c"


void query_server(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "localhost:8080/books.xml");
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
