#include <stdio.h>
#include <ncurses.h>
#include <curl/curl.h>

void ui(void)
{
  initscr();
  printw("Hello World!!!");
  refresh();
  getch();
  endwin();
}

int main(int argc, char *argv[])
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "localhost:8080/books.xml");
    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }

  return 0;
}
