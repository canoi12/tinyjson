#include "tinyjson.h"

static char* file_read(const char *filename) {
  FILE *fp;
  fp = fopen(filename, "rb");
  if (!fp) {
    fprintf(stderr, "Failed to open %s\n", filename);
    exit(12);
  }

  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *buffer = (char*)malloc(size+1);
  if (!buffer) {
    fprintf(stderr, "Failed to read %s, not enough memory", filename);
    exit(12);
  }
  size_t bytes_read = fread(buffer, sizeof(char), size, fp);
  if (bytes_read < size) {
    fprintf(stderr, "Failed to read %s", filename);
    fclose(fp);
    exit(12);
  }

  buffer[bytes_read] = '\0';
  fclose(fp);

  return buffer;
}

static int is_digit(char c) {
  return c >= '0' && c <= '9';
}

static int is_alpha(char c) {
  return c >= 'a' && c <= 'z';
}

static int is_at_end() {
  return *scanner.current == '\0';
}

static char advance_scanner() {
  scanner.current++;
  return scanner.current[-1];
}

static char peek() {
  return *scanner.current;
}

static char peek_next() {
  if (is_at_end()) return '\0';
  return scanner.current[1];
}

static void skip_whitespace() {
  for (;;) {
    char c = peek();
    switch(c) {
      case ' ':
      case '\r':
      case '\t':
        advance_scanner();
        break;
      case '\n':
        scanner.line++;
        advance_scanner();
        break;
      default:
        return;
    }
  }
}

static TJSON_TOKEN_ identifier_type() {
  switch(scanner.start[0]) {
    case 'n': return TJSON_TOKEN_NULL;
    case 't': return TJSON_TOKEN_TRUE;
    case 'f': return TJSON_TOKEN_FALSE;
  }

  return TJSON_TOKEN_IDENTIFIER;
}

static tjson_token_t string() {
  while (peek() != '"' && !is_at_end()) {
    if (peek() == '\n') scanner.line++;
    advance_scanner();
  }

  if (is_at_end()) return tjson_error_token("Unterminated string");

  advance_scanner();
  return tjson_make_token(TJSON_TOKEN_STRING);
}

static tjson_token_t number() {
  // printf("teste\n");
  while (is_digit(peek())) advance_scanner();

  if (peek() == '.' && is_digit(peek_next())) {
    advance_scanner();
    while (is_digit(peek())) advance_scanner();
  }

  return tjson_make_token(TJSON_TOKEN_NUMBER);
}

static tjson_token_t identifier() {
  while (is_alpha(peek())) advance_scanner();

  return tjson_make_token(identifier_type());
}

void tjson_init_scanner(const char *json_str) {
  scanner.start = json_str;
  scanner.current = json_str;
  scanner.line = 1;
  // printf("Scanner %s\n", json_str);
}

tjson_token_t tjson_scan_token() {
  skip_whitespace();
  scanner.start = scanner.current;
  // printf("testew: %s\n", scanner.start);

  if (is_at_end()) return tjson_make_token(TJSON_TOKEN_EOF);

  char c = advance_scanner();

  if (is_alpha(c)) return identifier();
  if (is_digit(c)) return number();

  // printf("%s\n", scanner.start);

  switch(c) {
    case '{': return tjson_make_token(TJSON_TOKEN_LBRACE);
    case '}': return tjson_make_token(TJSON_TOKEN_RBRACE);
    case '[': return tjson_make_token(TJSON_TOKEN_LSQUAR);
    case ']': return tjson_make_token(TJSON_TOKEN_RSQUAR);
    case ',': return tjson_make_token(TJSON_TOKEN_COMMA);
    case '.': return tjson_make_token(TJSON_TOKEN_DOT);
    case '-': return tjson_make_token(TJSON_TOKEN_MINUS);
    case ':': return tjson_make_token(TJSON_TOKEN_COLON);
    case '"': return string();
  }
  // printf("qqq\n");


  return tjson_error_token("Unexpected character."); 
}

tjson_token_t tjson_make_token(TJSON_TOKEN_ type) {
  tjson_token_t token;
  token.type = type;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.line = scanner.line;
  // printf("%d: %.*s\n", token.line, token.length, token.start);

  return token;
}

tjson_token_t tjson_error_token(const char *message) {
  tjson_token_t token;
  token.type = TJSON_TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = scanner.line;

  return token;
}

static void error_at(tjson_token_t *token, const char *message) {
  if (parser.panic_mode) return;
  parser.panic_mode = 1;

  fprintf(stderr, "[tinyjson]:%d Error", token->line);

  if (token->type == TJSON_TOKEN_EOF) fprintf(stderr, " at end");
  else fprintf(stderr, " at %.*s,", token->length, token->start);

  fprintf(stderr, " %s\n", message);
  parser.hand_error = 1;
}

static void error_at_current(const char *message) {
  error_at(&parser.current, message);
}

static void advance_parser() {
  parser.previous = parser.current;

  for (;;) {
    parser.current = tjson_scan_token();
    // printf("teste %d\n", parser.current.type);
    if (parser.current.type != TJSON_TOKEN_ERROR) break;

    error_at_current(parser.current.start);
  }
}

static void consume_parser(TJSON_TOKEN_ token_type, const char *message) {
  if (parser.current.type == token_type) {
    advance_parser();
    return;
  }

  error_at_current(message);
}

char *parse_cstring(tjson_token_t *token) {
  char *string = (char*)malloc(token->length-1);
  memcpy(string, token->start+1, token->length-2);
  string[token->length-2] = '\0';

  return string;
}

static tjson_t* parse_number(tjson_token_t *token) {
  double value = 0;
  if (token->type == TJSON_TOKEN_MINUS) {
    tjson_token_t tnext = tjson_scan_token();
    value = -strtod(tnext.start, NULL);
  }
  else value = strtod(token->start, NULL);

  return tjson_create_number(value);
}

static tjson_t *parse_string(tjson_token_t *token) {
  char *str = parse_cstring(token);
  return tjson_create_string(str);
}

static tjson_t* parse_json_token(tjson_token_t *token);

tjson_t* parse_json_object() {
  tjson_t *obj = tjson_create_object();
  tjson_token_t token = tjson_scan_token();
  while (token.type != TJSON_TOKEN_RBRACE) {
    char *name = parse_cstring(&token);
    token = tjson_scan_token();
    if (token.type != TJSON_TOKEN_COLON) {
      // fprintf(stderr, "Missing colon on line %d, after %s\n", token.line, name);
      error_at(&token, "missing ':'");
      exit(25);
    } else token = tjson_scan_token();
    // token = tjson_scan_token();

    tjson_t *val = parse_json_token(&token);
    tjson_object_set(obj, name, val);

    token = tjson_scan_token();
    // printf("teste\n");
    if (token.type == TJSON_TOKEN_COMMA) {
      token = tjson_scan_token();
      if (token.type == TJSON_TOKEN_RBRACE) {
        // fprintf(stderr, "Extra comma on line %d, after '%s'\n", token.line, name);
        error_at(&token, "extra ','");
        exit(25);
      }
    } else if (token.type != TJSON_TOKEN_RBRACE) {
      // fprintf(stderr, "Missing comma on line %d, after '%s'\n", token.line, name);
      error_at(&token, "missing ','");
      exit(25);
    }
  }

  return obj;
}

tjson_t* parse_json_array() {
  tjson_t *array = tjson_create_array();
  tjson_token_t token = tjson_scan_token();
  while (token.type != TJSON_TOKEN_RSQUAR) {
    tjson_t *val = parse_json_token(&token);
    // printf("%d\n", val->type);
    tjson_array_push(array, val);

    token = tjson_scan_token();
    // printf("teste\n");
    if (token.type == TJSON_TOKEN_COMMA) {
      token = tjson_scan_token();
      if (token.type == TJSON_TOKEN_RSQUAR) {
        // fprintf(stderr, "Extra comma on line %d, after '%s'\n", token.line, name);
        error_at(&token, "extra ','");
        exit(25);
      }
    } else if (token.type != TJSON_TOKEN_RSQUAR) {
      // fprintf(stderr, "Missing comma on line %d, after '%s'\n", token.line, name);
      error_at(&token, "missing ','");
      exit(25);
    }
  }

  return array;
}

tjson_t* parse_json_token(tjson_token_t *token) {
  // tjson_t *json = tjson_create(TJSON_)
  switch (token->type) {
    case TJSON_TOKEN_LBRACE:
      return parse_json_object();
    case TJSON_TOKEN_LSQUAR:
      return parse_json_array();
    case TJSON_TOKEN_MINUS:
    case TJSON_TOKEN_NUMBER:
      return parse_number(token);
    case TJSON_TOKEN_STRING:
      return parse_string(token);
    case TJSON_TOKEN_TRUE:
      return tjson_create_bool(1);
    case TJSON_TOKEN_FALSE:
      return tjson_create_bool(0);
    case TJSON_TOKEN_NULL:
      return tjson_create_null();
    case TJSON_TOKEN_ERROR:
      {
        error_at(token, token->start);
        exit(50);
      }
  }


  // error_at(token, "unkown symbol");
  return NULL;
}

tjson_t* tjson_parse(const char *json_str) {
  // printf("testandow\n");
  // advance_scanner();
  // tjson_scan_token();
  tjson_init_scanner(json_str);
  parser.hand_error = 0;
  parser.panic_mode = 0;
  tjson_token_t token = tjson_scan_token();
  tjson_t *json = parse_json_token(&token);
  // while (token.type != TJSON_TOKEN_EOF) {
  //  switch (token.type) {
  //    case TJSON_TOKEN_NULL:

  //  }
  // }
  // return NULL;
  return json;
}

tjson_t* tjson_open(const char *filename) {
  const char *source = file_read(filename);
  tjson_t *json = tjson_parse(source);
  free((char*)source);

  return json;
}

tjson_t* tjson_create(TJSON_TYPE_ type) {
  tjson_t *json = malloc(sizeof(*json));
  json->name = NULL;
  json->type = type;
  json->next = NULL;
  json->child = NULL;

  return json;
}

tjson_t* tjson_create_null() {
  tjson_t *json = tjson_create(TJSON_NULL);

  return json;
}
tjson_t* tjson_create_number(double value) {
  tjson_t *json = tjson_create(TJSON_NUMBER);
  json->number = value;

  return json;
}
tjson_t* tjson_create_string(const char *value) {
  if(!value) return NULL;
  tjson_t *json = tjson_create(TJSON_STRING);
  int size = strlen(value);
  json->string = malloc(size);
  strcpy(json->string, value);

  return json;
}
tjson_t* tjson_create_bool(int value) {
  tjson_t *json = tjson_create(TJSON_BOOL);
  json->boolean = value;

  return json;
}
tjson_t* tjson_create_array() {
  tjson_t *json = tjson_create(TJSON_ARRAY);
  return json;
}
tjson_t* tjson_create_object() {
  tjson_t *json = tjson_create(TJSON_OBJECT);
  return json;
}

void tjson_set_name(tjson_t *json, const char *name) {
  if (!json) return;
  int len = strlen(name);
  if (!json->name) {
    json->name = malloc(len+1);
  } else {
    int name_len = strlen(json->name);
    if (name_len < len) json->name = realloc(json->name, len+1);
  }

  strcpy(json->name, name);
  json->name[len] = '\0';
}

const char* tjson_get_name(tjson_t *json) {
  return json->name;
}

/*=============*
 *    Array    *
 *=============*/

tjson_t* tjson_array_set(tjson_t *array, int index, tjson_t *value) {
  if (!array) return NULL;
  if (!value) return NULL;

  tjson_t *iter = array->child;
  if (index < 0) index = 0;

  if (index == 0) {
    array->child = value;
    value->next = iter;
  }

  int i = 0;
  while (iter->next) {
    if (i+1 == index) {
      value->next = iter->next;
      iter->next = value;
      return iter;
    }
    iter = iter->next;
    i++;
  }

  return NULL;
}

tjson_t* tjson_array_get(tjson_t *array, int index) {
  if (!array) return NULL;
  tjson_t *iter = array->child;
  if (!iter) return NULL;

  int i = 0;
  while (iter) {
    if (i == index) return iter;
    iter = iter->next;
    i++;
  }

  return NULL;
}

void tjson_array_push(tjson_t *array, tjson_t *value) {
  if (!array) return;
  if (!value) return;
  tjson_t *iter = array->child;
  if (!iter) {
    array->child = value;
    return;
  }

  while(iter->next) iter = iter->next;

  iter->next = value;
  value->next = NULL;
}
tjson_t* tjson_array_pop(tjson_t *array) {
  if (!array) return NULL;
  if (array->type != TJSON_ARRAY && array->type != TJSON_OBJECT) return NULL;

  // tjson_t *ret = NULL;

  tjson_t *iter = array->child;
  if (!iter) return NULL;
  if (!iter->next) {
    array->child = NULL;
    return iter;
  }

  while (iter->next->next) iter = iter->next;

  tjson_t *next = iter->next;
  iter->next = NULL;

  return next;
}
tjson_t* tjson_array_last(tjson_t *array) {
  tjson_t *iter = array->child;
  if (!iter) return NULL;
  while (iter->next) iter = iter->next;

  return iter;
}

void tjson_array_set_number(tjson_t *array, int index, double value) {
  tjson_t *number = tjson_create_number(value);
  tjson_array_set(array, index, number);
}

void tjson_array_set_string(tjson_t *array, int index, const char* value);
void tjson_array_set_bool(tjson_t *array, int index, int value);
void tjson_array_set_array(tjson_t *array, int index, tjson_t *value);
void tjson_array_set_object(tjson_t *array, int index, tjson_t *value);

double tjson_array_get_number(tjson_t *array, int index);
const char* tjson_array_get_string(tjson_t *array, int index);
int tjson_array_get_bool(tjson_t *array, int index);
tjson_t* tjson_array_get_array(tjson_t *array, int index);
tjson_t* tjson_array_get_array(tjson_t *array, int index);

void tjson_array_push_number(tjson_t *array, double value);
void tjson_array_push_string(tjson_t *array, const char* value);
void tjson_array_push_bool(tjson_t *array, int value);
void tjson_array_push_array(tjson_t *array, tjson_t *value);
void tjson_array_push_object(tjson_t *array, tjson_t *value);

double tjson_array_pop_number(tjson_t *array);
const char* tjson_array_pop_string(tjson_t *array);
int tjson_array_pop_bool(tjson_t *array);
tjson_t* tjson_array_pop_array(tjson_t *array);
tjson_t* tjson_array_pop_object(tjson_t *array);


/*==============*
 *    Object    *
 *==============*/

tjson_t* tjson_object_set(tjson_t *object, const char *name, tjson_t *value) {
  if (!object) return NULL;
  if (object->type != TJSON_OBJECT) return NULL;
  if (!value) return NULL;

  tjson_set_name(value, name);

  tjson_t *iter = object->child;
  if (!iter) {
    object->child = value;
    return value;
  } else {
    if (!strcmp(iter->name, name)) {
      object->child = value;
      value->next = iter->next;
      return iter;
    }
  }

  while (iter->next) {
    if (!strcmp(iter->next->name, name)) {
      tjson_t *old = iter->next;
      iter->next = value;
      value->next = old->next;
      return old;
    }
    iter = iter->next;
  }
  iter->next = value;
  value->next = NULL;

  return value;
}

tjson_t* tjson_object_get(tjson_t *object, const char *name) {
  if (!object) return NULL;
  if (object->type != TJSON_OBJECT) return NULL;

  tjson_t *el = NULL;
  tjson_foreach(el, object) {
    if (!strcmp(el->name, name)) return el;
  }

  return NULL;
}

void tjson_object_set_number(tjson_t *object, const char *name, double value) {
  tjson_t *number = tjson_create_number(value);
  tjson_object_set(object, name, number);
}

void tjson_object_set_string(tjson_t *object, const char *name, const char* value);
void tjson_object_set_bool(tjson_t *object, const char *name, int value);
void tjson_object_set_array(tjson_t *object, const char *name, tjson_t *value);
void tjson_object_set_object(tjson_t *object, const char *name, tjson_t *value);

double tjson_object_get_number(tjson_t *object, const char *name);
const char* tjson_object_get_string(tjson_t *object, const char *name);
int tjson_object_get_bool(tjson_t *object, const char *name);
tjson_t* tjson_object_get_array(tjson_t *object, const char *name);
tjson_t* tjson_object_get_object(tjson_t *object, const char *name);