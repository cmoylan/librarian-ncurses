#include "config.c"
#include "globals.h"
#include "server.c"
#include "window.c"

#include <stdio.h>

#include <libxml/parser.h>
#include <libxml/tree.h>


static void print_element_names(xmlNode* a_node)
{
  xmlNode *cur_node = NULL;

  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      printf("node type: Element, name: %s, %s\n", cur_node->name, xmlNodeGetContent(cur_node));
    }

    print_element_names(cur_node->children);
  }
}


/**
 *  Main program that accepts and handles command line arguments
 *
 *  @return 0 if successful
 */
int main(int argc, char *argv[])
{
  config_initialize();
  fetch("books");

  // --- parse books with libxml
  xmlDocPtr doc;
  xmlNode *root_element = NULL;

  doc = xmlReadFile(BOOKS_CACHE, NULL, 0);
  if (doc == NULL) {
    fprintf(stderr, "Failed to parse %s\n", "books.cache");
    return;
  }

  root_element = xmlDocGetRootElement(doc);
  print_element_names(root_element);

  xmlFreeDoc(doc);
  xmlCleanupParser();


  // --- end parser

  //window_main();

  // TODO: giant case statement to parse command line options

  return 0;
}
