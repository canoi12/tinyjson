#ifndef TINY_JSON_H
#define TINY_JSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TJSON_API
#define tjson_foreach(element, array) for(element = (array != NULL) ? (array)->child : NULL; element != NULL; element = element->next)


typedef struct tjson_s         tjson_t;
typedef struct tjson_token_s   tjson_token_t;
typedef struct tjson_scanner_s tjson_scanner_t;
typedef struct tjson_parser_s  tjson_parser_t;

typedef enum {
  TJSON_NULL = 0,
  TJSON_NUMBER,
  TJSON_BOOL,
  TJSON_STRING,
  TJSON_ARRAY,
  TJSON_OBJECT
} TJSON_TYPE_;

typedef enum {
  TJSON_TOKEN_NULL = 0,   // Null token                 'null'
  TJSON_TOKEN_FALSE,      // False token                'false'
  TJSON_TOKEN_TRUE,       // True token                 'true'
  TJSON_TOKEN_NUMBER,     // Number token               '012..9'
  TJSON_TOKEN_STRING,     // String token               '"'
  TJSON_TOKEN_LBRACE,     // Left bracket token         '{'
  TJSON_TOKEN_RBRACE,     // Right bracket token        '}'
  TJSON_TOKEN_LSQUAR,     // Left square bracket token  '['
  TJSON_TOKEN_RSQUAR,     // Right square bracket token ']'
  TJSON_TOKEN_COMMA,      // Comma token                ','
  TJSON_TOKEN_DOT,        // Dot token                  '.'
  TJSON_TOKEN_MINUS,      // Minus token                '-'
  TJSON_TOKEN_COLON,      // Colon token                ':'
  TJSON_TOKEN_IDENTIFIER, // Identifier token
  TJSON_TOKEN_ERROR,      // Error
  TJSON_TOKEN_EOF         // End of file
} TJSON_TOKEN_;

struct tjson_scanner_s {
  const char *start;
  const char *current;
  int line;
};

tjson_scanner_t scanner;

struct tjson_token_s {
  int type;
  const char *start;
  int length;
  int line;
};

struct tjson_parser_s {
  tjson_token_t current;
  tjson_token_t previous;
  int hand_error;
  int panic_mode;
};

tjson_parser_t parser;

struct tjson_s {
  int type;
  char *name;
  union {
    char *string;
    double number;
    int boolean;
    tjson_t *child;
  };

  tjson_t *next;
};

TJSON_API void tjson_init_scanner(const char *json_str);
TJSON_API tjson_token_t tjson_scan_token();
TJSON_API tjson_token_t tjson_make_token(TJSON_TOKEN_ type);
TJSON_API tjson_token_t tjson_error_token(const char *message);

TJSON_API tjson_t* tjson_open(const char *filename);
TJSON_API tjson_t* tjson_parse(const char *json_str);
TJSON_API const char* tjson_print(tjson_t *json);
TJSON_API int tjson_save(tjson_t *json, const char *filename);

TJSON_API tjson_t* tjson_create_null();
TJSON_API tjson_t* tjson_create_number(double value);
TJSON_API tjson_t* tjson_create_string(const char *value);
TJSON_API tjson_t* tjson_create_bool(int value);
TJSON_API tjson_t* tjson_create_array();
TJSON_API tjson_t* tjson_create_object();

TJSON_API tjson_token_t* tjson_parse_null(const char *str);

TJSON_API void tjson_set_name(tjson_t *json, const char *name);
TJSON_API const char* tjson_get_name(tjson_t *json);

TJSON_API void tjson_set_number(tjson_t *number, double value);
TJSON_API void tjson_set_string(tjson_t *number, const char* value);
TJSON_API void tjson_set_bool(tjson_t *number, int value);

TJSON_API double tjson_to_number(tjson_t *number);
TJSON_API const char* tjson_to_string(tjson_t *string);
TJSON_API int tjson_to_bool(tjson_t *boolean);
// TJSON_API tjson_t* tjson_set_array(tjson_t *number, tjson_t* array);
// TJSON_API tjson_t* tjson_set_object(tjson_t *number, tjson_t* object);

/*=============*
 *    Array    *
 *=============*/

TJSON_API tjson_t* tjson_array_set(tjson_t *array, int index, tjson_t *value);
TJSON_API tjson_t* tjson_array_get(tjson_t *array, int index);
TJSON_API void tjson_array_push(tjson_t *array, tjson_t *value);
TJSON_API tjson_t* tjson_array_pop(tjson_t *array);
TJSON_API tjson_t* tjson_array_last(tjson_t *array);

TJSON_API void tjson_array_set_number(tjson_t *array, int index, double value);
TJSON_API void tjson_array_set_string(tjson_t *array, int index, const char* value);
TJSON_API void tjson_array_set_bool(tjson_t *array, int index, int value);
TJSON_API void tjson_array_set_array(tjson_t *array, int index, tjson_t *value);
TJSON_API void tjson_array_set_object(tjson_t *array, int index, tjson_t *value);

TJSON_API double tjson_array_get_number(tjson_t *array, int index);
TJSON_API const char* tjson_array_get_string(tjson_t *array, int index);
TJSON_API int tjson_array_get_bool(tjson_t *array, int index);
TJSON_API tjson_t* tjson_array_get_array(tjson_t *array, int index);
TJSON_API tjson_t* tjson_array_get_array(tjson_t *array, int index);

TJSON_API void tjson_array_push_number(tjson_t *array, double value);
TJSON_API void tjson_array_push_string(tjson_t *array, const char* value);
TJSON_API void tjson_array_push_bool(tjson_t *array, int value);
TJSON_API void tjson_array_push_array(tjson_t *array, tjson_t *value);
TJSON_API void tjson_array_push_object(tjson_t *array, tjson_t *value);

TJSON_API double tjson_array_pop_number(tjson_t *array);
TJSON_API const char* tjson_array_pop_string(tjson_t *array);
TJSON_API int tjson_array_pop_bool(tjson_t *array);
TJSON_API tjson_t* tjson_array_pop_array(tjson_t *array);
TJSON_API tjson_t* tjson_array_pop_object(tjson_t *array);

/*==============*
 *    Object    *
 *==============*/

TJSON_API tjson_t* tjson_object_set(tjson_t *object, const char *name, tjson_t *value);
TJSON_API tjson_t* tjson_object_get(tjson_t *object, const char *name);

TJSON_API void tjson_object_set_number(tjson_t *object, const char *name, double value);
TJSON_API void tjson_object_set_string(tjson_t *object, const char *name, const char* value);
TJSON_API void tjson_object_set_bool(tjson_t *object, const char *name, int value);
TJSON_API void tjson_object_set_array(tjson_t *object, const char *name, tjson_t *value);
TJSON_API void tjson_object_set_object(tjson_t *object, const char *name, tjson_t *value);

TJSON_API double tjson_object_get_number(tjson_t *object, const char *name);
TJSON_API const char* tjson_object_get_string(tjson_t *object, const char *name);
TJSON_API int tjson_object_get_bool(tjson_t *object, const char *name);
TJSON_API tjson_t* tjson_object_get_array(tjson_t *object, const char *name);
TJSON_API tjson_t* tjson_object_get_object(tjson_t *object, const char *name);

#endif