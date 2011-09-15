#include <curl/curl.h>


char LIBRARIAN_URL[] = "http://localhost:8080";
//char VALID_TYPES[] = {"a", "b", "c"};

void query_server(void);


// TODO:
//
//


void fetch(char *data_type)
{
  printf("%s", data_type);
  //query_server();
}


/**
 *  do something with the data that comes back from the server
 */
size_t do_stuff( char *ptr, size_t size, size_t nmemb, void *userdata)
{
  //return fwrite(ptr, size, nmemb, userdata);
}


/**
 *  basic query function
 */
void query_server(void)
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
    printf("aaahhhh");

    curl_easy_cleanup(curl);
  }
}
