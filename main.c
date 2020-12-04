#include "src/tinyjson.h"

static void print_object(tjson_t *json, int tabs);
static void print_array(tjson_t *json, int tabs);

void print_array(tjson_t *json, int tabs) {
	tjson_t *iter = NULL;
	// printf("teste %p\n", json->child);
	printf("<array> [\n");
	int i = 0;
	char tabs_str[tabs];
	memset(tabs_str, ' ', tabs);
	tjson_foreach(iter, json) {
		printf("%s", tabs_str);
		switch (iter->type) {
			case TJSON_NULL: 
				printf("%d: <null>\n", i);
				break;
			case TJSON_NUMBER:
				printf("%d: <number>(%g)\n", i, iter->number);
				break;
			case TJSON_STRING:
				printf("%d: <string>(%s)\n", i, iter->string);
				break;
			case TJSON_BOOL:
				printf("%d: <bool>(%s)\n", i, iter->boolean ? "true" : "false");
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
	// printf("teste %p\n", json->child);
	printf("<object> {\n");
	char tabs_str[tabs];
	memset(tabs_str, ' ', tabs);
	tjson_foreach(iter, json) {
		printf("%s", tabs_str);
		printf("%s: ", iter->name);
		switch (iter->type) {
			case TJSON_NULL: 
				printf("<null>\n");
				break;
			case TJSON_NUMBER:
				printf("<number>(%g)\n", iter->number);
				break;
			case TJSON_STRING:
				printf("<string>(\"%s\")\n", iter->string);
				break;
			case TJSON_BOOL:
				printf("<bool>(%s)\n", iter->boolean ? "true" : "false");
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

	// tjson_t *json = tjson_open("tileset.json");
	if (json) print_object(json, 1);
	return 0;
}