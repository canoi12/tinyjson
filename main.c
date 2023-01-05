#include "tinyjson.h"

#include <stdio.h>
#include <string.h>

static void print_object(tjson_t *json, int tabs);
static void print_array(tjson_t *json, int tabs);

void print_array(tjson_t *json, int tabs) {
  tjson_t *iter = NULL;
  /* printf("teste %p\n", json->child); */
  printf("<array> [\n");
  int i = 0;
  char tabs_str[tabs];
  memset(tabs_str, ' ', tabs);
  for (iter = tjson_get_child(json); iter != NULL; iter = tjson_get_next(iter)) {
    printf("%s", tabs_str);
    switch (tjson_get_type(iter)) {
      case TJSON_NULL: 
        printf("%d: <null>\n", i);
        break;
      case TJSON_NUMBER:
        printf("%d: <number>(%g)\n", i, tjson_to_number(iter));
        break;
      case TJSON_STRING:
        printf("%d: <string>(%s)\n", i, tjson_to_string(iter));
        break;
      case TJSON_BOOL:
        printf("%d: <bool>(%s)\n", i, tjson_to_bool(iter) ? "true" : "false");
        break;
      case TJSON_ARRAY:
        print_array(iter, tabs+1);
        break;
      case TJSON_OBJECT:
        print_object(iter, tabs+1);
    }
    i++;
  }
  printf("%.*s]\n", tabs-1 < 0 ? 0 : tabs-1, tabs_str);
}

void print_object(tjson_t *json, int tabs) {
  tjson_t *iter = NULL;
  printf("<object> {\n");
  char tabs_str[tabs];
  memset(tabs_str, ' ', tabs);
  iter = tjson_get_child(json);
  for (iter = tjson_get_child(json); iter != NULL; iter = tjson_get_next(iter)) {
    printf("%s", tabs_str);
    printf("%s: ", tjson_get_name(iter));
    switch (tjson_get_type(iter)) {
      case TJSON_NULL: 
        printf("<null>\n");
        break;
      case TJSON_NUMBER:
        printf("<number>(%g)\n", tjson_to_number(iter));
        break;
      case TJSON_STRING:
        printf("<string>(\"%s\")\n", tjson_to_string(iter));
        break;
      case TJSON_BOOL:
        printf("<bool>(%s)\n", tjson_to_bool(iter) ? "true" : "false");
        break;
      case TJSON_ARRAY:
        print_array(iter, tabs+1);
        break;
      case TJSON_OBJECT:
        print_object(iter, tabs+1);
    }
  }
  printf("%.*s}\n", tabs-1 < 0 ? 0 : tabs-1, tabs_str);
}

int main(int argc, char **argv) {
  tjson_t *json = NULL;
  if (argc < 2) printf("Usage: ./tjson [filename]\n");
  else json = tjson_open(argv[1]);

  /* tjson_t *json = tjson_open("tileset.json"); */
  if (json) print_object(json, 1);
  tjson_delete(json);
  /* free(json);
  printf("%p\n", json); */
  return 0;
}