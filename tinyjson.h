#ifndef _TINYJSON_H_
#define _TINYJSON_H_

#define TJSON_API

#define TJSON_NUMBER_ERROR -25215910

typedef enum {
    TJSON_NULL = 0,
    TJSON_NUMBER,
    TJSON_BOOL,
    TJSON_STRING,
    TJSON_ARRAY,
    TJSON_OBJECT
} TJSON_TYPE_;

typedef struct tjson_s tjson_t;

#if defined(__cplusplus)
extern "C" {
#endif

TJSON_API tjson_t* tjson_open(const char* filename);
TJSON_API tjson_t* tjson_parse(const char* json_str);
TJSON_API const char* tjson_print(tjson_t* json);
TJSON_API int tjson_save(tjson_t* json, const char* filename);

TJSON_API tjson_t* tjson_create(TJSON_TYPE_ type);
TJSON_API void tjson_clear(tjson_t* json);
TJSON_API void tjson_delete(tjson_t* json);

TJSON_API tjson_t* tjson_create_null();
TJSON_API tjson_t* tjson_create_number(double value);
TJSON_API tjson_t* tjson_create_string(const char* value);
TJSON_API tjson_t* tjson_create_bool(int value);
TJSON_API tjson_t* tjson_create_array(void);
TJSON_API tjson_t* tjson_create_object(void);

TJSON_API void tjson_set_name(tjson_t* json, const char* name);
TJSON_API const char* tjson_get_name(tjson_t* json);

TJSON_API void tjson_set_number(tjson_t* json, double value);
TJSON_API void tjson_set_string(tjson_t* json, const char* value);
TJSON_API void tjson_set_bool(tjson_t* json, int value);

TJSON_API double tjson_to_number(tjson_t* json);
TJSON_API const char* tjson_to_string(tjson_t* json);
TJSON_API int tjson_to_bool(tjson_t* json);

/*=============*
 *    Array    *
 *=============*/

TJSON_API tjson_t* tjson_array_set(tjson_t* array, int index, tjson_t* value);
TJSON_API tjson_t* tjson_array_get(tjson_t* array, int index);
TJSON_API void tjson_array_push(tjson_t* array, tjson_t* value);
TJSON_API tjson_t* tjson_array_pop(tjson_t* array);
TJSON_API tjson_t* tjson_array_last(tjson_t* array);

TJSON_API void tjson_array_set_number(tjson_t* array, int index, double value);
TJSON_API void tjson_array_set_string(tjson_t* array, int index, const char* value);
TJSON_API void tjson_array_set_bool(tjson_t* array, int index, int value);
TJSON_API void tjson_array_set_array(tjson_t* array, int index, tjson_t* value);
TJSON_API void tjson_array_set_object(tjson_t* array, int index, tjson_t* value);

TJSON_API double tjson_array_opt_number(tjson_t* array, int index, double opt);
TJSON_API const char* tjson_array_opt_string(tjson_t* array, int index, const char* opt);
TJSON_API int tjson_array_opt_bool(tjson_t* array, int index, int opt);
TJSON_API tjson_t* tjson_array_opt_array(tjson_t* array, int index, tjson_t* opt);
TJSON_API tjson_t* tjson_array_opt_object(tjson_t* array, int index, tjson_t* opt);

#define tjson_array_get_number(array, name) tjson_array_opt_number(array, name, TJSON_NUMBER_ERROR)
#define tjson_array_get_string(array, name) tjson_array_opt_string(array, name, NULL)
#define tjson_array_get_bool(array, name) tjson_array_opt_bool(array, name, TJSON_NUMBER_ERROR)
#define tjson_array_get_array(array, name) tjson_array_opt_array(array, name, NULL)
#define tjson_array_get_object(array, name) tjson_array_opt_object(array, name, NULL)

TJSON_API void tjson_array_push_number(tjson_t* array, double value);
TJSON_API void tjson_array_push_string(tjson_t* array, const char* value);
TJSON_API void tjson_array_push_bool(tjson_t* array, int value);
TJSON_API void tjson_array_push_array(tjson_t* array, tjson_t* value);
TJSON_API void tjson_array_push_object(tjson_t* array, tjson_t* value);

TJSON_API double tjson_array_pop_number(tjson_t* array);
TJSON_API const char* tjson_array_pop_string(tjson_t* array);
TJSON_API int tjson_array_pop_bool(tjson_t* array);
TJSON_API tjson_t* tjson_array_pop_array(tjson_t* array);
TJSON_API tjson_t* tjson_array_pop_object(tjson_t* array);

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

TJSON_API double tjson_object_opt_number(tjson_t *object, const char *name, double opt);
TJSON_API const char* tjson_object_opt_string(tjson_t *object, const char *name, const char *opt);
TJSON_API int tjson_object_opt_bool(tjson_t *object, const char *name, int opt);
TJSON_API tjson_t* tjson_object_opt_array(tjson_t *object, const char *name, tjson_t *opt);
TJSON_API tjson_t* tjson_object_opt_object(tjson_t *object, const char *name, tjson_t *opt);

#define tjson_object_get_number(object, name) tjson_object_opt_number(object, name, TJSON_NUMBER_ERROR)
#define tjson_object_get_string(object, name) tjson_object_opt_string(object, name, NULL)
#define tjson_object_get_bool(object, name) tjson_object_opt_bool(object, name, TJSON_NUMBER_ERROR)
#define tjson_object_get_array(object, name) tjson_object_opt_array(object, name, NULL)
#define tjson_object_get_object(object, name) tjson_object_opt_object(object, name, NULL)

#if defined(__cplusplus)
}
#endif

#endif /* _TINYJSON_H_ */

#if defined(TJSON_IMPLEMENTATION)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tjson_foreach(element, array) for(element = (array != NULL) ? (array)->child : NULL; element != NULL; element = element->next)

typedef struct tjson_scanner_s tjson_scanner_t;
typedef struct tjson_token_s tjson_token_t;
typedef struct tjson_parser_s tjson_parser_t;

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
    const char* start;
    const char* current;
    int line;
};

struct tjson_token_s {
    int type;
    const char* start;
    int length;
    int line;
};

struct tjson_parser_s {
    tjson_token_t current;
    tjson_token_t previous;
    int hand_error;
    int panic_mode;
};

static tjson_scanner_t scanner;
static tjson_parser_t parser;

struct tjson_s {
    int type;
    char* name;
    union {
        char* string;
        double number;
        int boolean;
        tjson_t* child;
    };

    tjson_t* next;
};


/* scanner */
static tjson_t* s_parse_json(const char* json_str);

/* utils */
static char* s_file_read(const char* filename);

tjson_t* tjson_parse(const char* json_str) { return s_parse_json(json_str); }

tjson_t* tjson_open(const char* filename) {
    const char* source = s_file_read(filename);
    tjson_t* json = tjson_parse(source);
    free(source);
    return json;
}

tjson_t* tjson_create(TJSON_TYPE_ type) {
    if (type < TJSON_NULL || type > TJSON_OBJECT) {
        fprintf(stderr, "Invalid object type\n");
        return NULL;
    }
    tjson_t* json = (tjson_t*)malloc(sizeof(*json));
    if (!json) return NULL;
    memset(json, 0, sizeof(*json));

    json->name = NULL;
    json->type = type;
    json->next = NULL;
    json->child = NULL;
    return json;
}

void tjson_clear(tjson_t* json) {
    if (!json) return;
    if (json->type != TJSON_OBJECT && json->type != TJSON_ARRAY) return;

    tjson_t* iter = json->child;
    while (iter) {
        tjson_t* next = iter->next;
        tjson_delete(iter);
        iter = next;
    }
}

void tjson_delete(tjson_t* json) {
    if (!json) return;
    tjson_clear(json);
    if (json->type == TJSON_STRING && json->string) free(json->string);
    free(json);
}

tjson_t* tjson_create_null() { return tjson_create(TJSON_NULL); }

tjson_t* tjson_create_number(double value) {
    tjson_t* json = tjson_create(TJSON_NUMBER);
    json->number = value;
    return json;
}

tjson_t* tjson_create_string(const char* value) {
    if (!value) return NULL;
    tjson_t* json = tjson_create(TJSON_STRING);
    int size = strlen(value);
    json->string = (char*)malloc(size+1);
    strcpy(json->string, value);
    return json;
}

tjson_t* tjson_create_bool(int value) {
    tjson_t* json = tjson_create(TJSON_BOOL);
    json->boolean = value;
    return json;
}

tjson_t* tjson_create_array() { return tjson_create(TJSON_ARRAY); }

tjson_t* tjson_create_object() { return tjson_create(TJSON_OBJECT); }

void tjson_set_name(tjson_t* json, const char* name) {
    if (!json) return;
    int len = strlen(name);
    if (!json->name) {
        json->name = malloc(len + 1);
    } else {
        int name_len = strlen(json->name);
        if (name_len < len) json->name = realloc(json->name, len+1);
    }
    strcpy(json->name, name);
    json->name[len] = '\0';
}

const char* tjson_get_name(tjson_t* json) {
    if (!json) return NULL;
    return (const char*)json->name;
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
    if (!array) return;
    tjson_t *number = tjson_create_number(value);
    if (!tjson_array_set(array, index, number)) tjson_delete(number);
}

void tjson_array_set_string(tjson_t *array, int index, const char* value) {
    if (!array) return;
    tjson_t *string = tjson_create_string(value);
    if (!tjson_array_set(array, index, string)) tjson_delete(string);
}

void tjson_array_set_bool(tjson_t *array, int index, int value) {
    if (!array) return;
    tjson_t *boolean = tjson_create_bool(value);
    if (!tjson_array_set(array, index, boolean)) tjson_delete(boolean);
}

void tjson_array_set_array(tjson_t *array, int index, tjson_t *value) {
    tjson_array_set(array, index, value);
}

void tjson_array_set_object(tjson_t *array, int index, tjson_t *value) {
    tjson_array_set(array, index, value);
}

double tjson_array_opt_number(tjson_t *array, int index, double opt) {
    tjson_t *number = tjson_array_get(array, index);
    if (!number) return opt;
    if (number->type != TJSON_NUMBER) return opt;
    return number->number;
}

const char* tjson_array_opt_string(tjson_t *array, int index, const char* opt) {
    tjson_t *string = tjson_array_get(array, index);
    if (!string) return opt;
    if (string->type != TJSON_STRING) return opt;
    return string->string;
}

int tjson_array_opt_bool(tjson_t *array, int index, int opt) {
    tjson_t *boolean = tjson_array_get(array, index);
    if (!boolean) return opt;
    if (boolean->type != TJSON_BOOL) return opt;

    return boolean->boolean;
}

tjson_t* tjson_array_opt_array(tjson_t *array, int index, tjson_t* opt) {
    tjson_t *item = tjson_array_get(array, index);
    if (!item) return opt;
    if (item->type != TJSON_ARRAY) return opt;
    return item;
}

tjson_t* tjson_array_opt_object(tjson_t *array, int index, tjson_t* opt) {
    tjson_t *item = tjson_array_get(array, index);
    if (!item) return opt;
    if (item->type != TJSON_OBJECT) return opt;
    return item;
}

void tjson_array_push_number(tjson_t *array, double value) {
    if (!array) return;
    tjson_t *number = tjson_create_number(value);
    tjson_array_push(array, number);
}

void tjson_array_push_string(tjson_t *array, const char* value) {
    if (!array) return;
    tjson_t *string = tjson_create_string(value);
    tjson_array_push(array, string);
}

void tjson_array_push_bool(tjson_t *array, int value) {
    if (!array) return;
    tjson_t *boolean = tjson_create_bool(value);
    tjson_array_push(array, boolean);
}

void tjson_array_push_array(tjson_t *array, tjson_t *value) {
    tjson_array_push(array, value);
}

void tjson_array_push_object(tjson_t *array, tjson_t *value) {
    tjson_array_push(array, value);
}

double tjson_array_pop_number(tjson_t *array) {
    tjson_t *last = tjson_array_pop(array);
    if (!last) return TJSON_NUMBER_ERROR;
    double value = last->number;
    tjson_delete(last);

    return value;
}

const char* tjson_array_pop_string(tjson_t *array);

int tjson_array_pop_bool(tjson_t *array) {
    tjson_t *last = tjson_array_pop(array);
    if (!last) return TJSON_NUMBER_ERROR;
    int value = last->boolean;
    tjson_delete(last);

    return value;
}
tjson_t* tjson_array_pop_array(tjson_t *array) {
    return tjson_array_pop(array);
}
tjson_t* tjson_array_pop_object(tjson_t *array) {
    return tjson_array_pop(array);
}


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
    if (!tjson_object_set(object, name, number)) tjson_delete(number);
}

void tjson_object_set_string(tjson_t *object, const char *name, const char* value) {
    tjson_t *string = tjson_create_string(value);
    if (!tjson_object_set(object, name, string)) tjson_delete(string);
}

void tjson_object_set_bool(tjson_t *object, const char *name, int value) {
    tjson_t *boolean = tjson_create_bool(value);
    if (!tjson_object_set(object, name, boolean)) tjson_delete(boolean);
}

void tjson_object_set_array(tjson_t *object, const char *name, tjson_t *value) {
    tjson_object_set(object, name, value);
}

void tjson_object_set_object(tjson_t *object, const char *name, tjson_t *value) {
    tjson_object_set(object, name, value);
}

double tjson_object_opt_number(tjson_t *object, const char *name, double opt) {
    tjson_t *item = tjson_object_get(object, name);
    if (!item) return opt;
    if (item->type != TJSON_NUMBER) return opt;
    return item->number;
}

const char* tjson_object_opt_string(tjson_t *object, const char *name, const char *opt) {
    tjson_t *item = tjson_object_get(object, name);
    if (!item) return opt;
    if (item->type != TJSON_STRING) return opt;
    return item->string;
}

int tjson_object_opt_bool(tjson_t *object, const char *name, int opt) {
    tjson_t *item = tjson_object_get(object, name);
    if (!item) return opt;
    if (item->type != TJSON_BOOL) return opt;
    return item->boolean;
}

tjson_t* tjson_object_opt_array(tjson_t *object, const char *name, tjson_t *opt) {
    tjson_t *item = tjson_object_get(object, name);
    if (!item) return opt;
    if (item->type != TJSON_ARRAY) return opt;
    return item;
}

tjson_t* tjson_object_opt_object(tjson_t *object, const char *name, tjson_t *opt) {
    tjson_t *item = tjson_object_get(object, name);
    if (!item) return opt;
    if (item->type != TJSON_OBJECT) return opt;
    return item;
}

/*==============*
 *   Scanner    *
 *==============*/

static int is_digit(char c) { return c >= '0' && c <= '9'; }
static int is_alpha(char c) { return c >= 'a' && c <= 'z'; }
static int is_at_end() { return *(scanner.current) == '\0'; }
static char advance_scanner() {
    scanner.current++;
    return scanner.current[-1];
}
static char peek() { return *(scanner.current); };
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

static tjson_token_t s_make_token(TJSON_TOKEN_ type) {
    tjson_token_t token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static tjson_token_t s_error_token(const char* message) {
    tjson_token_t token;
    token.type = TJSON_TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

static TJSON_TOKEN_ identifier_type() {
    switch (scanner.start[0]) {
        case 'n': return TJSON_TOKEN_NULL;
        case 't': return TJSON_TOKEN_TRUE;
        case 'f': return TJSON_TOKEN_FALSE;
    }
    return TJSON_TOKEN_IDENTIFIER;
}

static tjson_token_t string_token() {
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') scanner.line++;
        advance_scanner();
    }

    if (is_at_end()) return s_error_token("Unterminated string");

    advance_scanner();
    return s_make_token(TJSON_TOKEN_STRING);
}

static tjson_token_t number_token() {
    while (is_digit(peek())) advance_scanner();
    if (peek() == '.' && is_digit(peek_next())) {
        advance_scanner();
        while (is_digit(peek())) advance_scanner();
    }
    return s_make_token(TJSON_TOKEN_NUMBER);
}

static tjson_token_t identifier_token() {
    while (is_alpha(peek())) advance_scanner();
    return s_make_token(identifier_type());
}

static void s_init_scanner(const char* json_str) {
    scanner.start = json_str;
    scanner.current = json_str;
    scanner.line = 1;
}

static tjson_token_t s_scan_token(void) {
    skip_whitespace();
    scanner.start = scanner.current;
    if (is_at_end()) return s_make_token(TJSON_TOKEN_EOF);
    char c = advance_scanner();
    if (is_alpha(c)) return identifier_token();
    if (is_digit(c)) return number_token();

    switch(c) {
        case '{': return s_make_token(TJSON_TOKEN_LBRACE);
        case '}': return s_make_token(TJSON_TOKEN_RBRACE);
        case '[': return s_make_token(TJSON_TOKEN_LSQUAR);
        case ']': return s_make_token(TJSON_TOKEN_RSQUAR);
        case ',': return s_make_token(TJSON_TOKEN_COMMA);
        case '.': return s_make_token(TJSON_TOKEN_DOT);
        case '-': return s_make_token(TJSON_TOKEN_MINUS);
        case ':': return s_make_token(TJSON_TOKEN_COLON);
        case '"': return string_token();
    }
    return s_error_token("Unexpected character");
}

/*==============*
 *    Parser    *
 *==============*/

static void s_error_at(tjson_token_t* token, const char* message) {
    if (parser.panic_mode) return;
    parser.panic_mode = 1;
    fprintf(stderr, "[tinyjson]:%d Error", token->line);
    if (token->type == TJSON_TOKEN_EOF) fprintf(stderr, " at end");
    else fprintf(stderr, " at %.*s,", token->length, token->start);
    fprintf(stderr, " %s\n", message);
    parser.hand_error = 1;
}

#if 0
static void s_error_at_current(const char* message) {
    s_error_at(&parser.current, message);
}
#endif

static char* s_parse_cstring(tjson_token_t* token) {
    int len = token->length;
    char* string = (char*)malloc(len-1);
    memcpy(string, token->start+1, len-2);
    string[len-2] = '\0';
    return string;
}

static tjson_t* s_parse_number(tjson_token_t* token) {
    double value = 0;
    if (token->type == TJSON_TOKEN_MINUS) {
        tjson_token_t tnext = s_scan_token();
        value = -strtod(tnext.start, NULL);
    }
    else value = strtod(token->start, NULL);
    return tjson_create_number(value);
}

static tjson_t* s_parse_string(tjson_token_t* token) {
    char* str = s_parse_cstring(token);
    return tjson_create_string(str);
}

static tjson_t* s_parse_json_token(tjson_token_t* token);

static tjson_t* s_parse_object() {
    tjson_t* obj = tjson_create_object();
    tjson_token_t token = s_scan_token();
    while (token.type != TJSON_TOKEN_RBRACE) {
        char* name = s_parse_cstring(&token);
        token = s_scan_token();
        if (token.type != TJSON_TOKEN_COLON) {
            s_error_at(&token, "missing ':'");
            exit(1);
        } else token = s_scan_token();

        tjson_t* val = s_parse_json_token(&token);
        tjson_object_set(obj, name, val);

        token = s_scan_token();
        if (token.type == TJSON_TOKEN_COMMA) {
            token = s_scan_token();
            if (token.type == TJSON_TOKEN_RBRACE) {
                s_error_at(&token, "extra ','");
                exit(1);
            }
        } else if (token.type != TJSON_TOKEN_RBRACE) {
            s_error_at(&token, "missing ','");
            exit(1);
        }
    }
    return obj;
}

static tjson_t* s_parse_array() {
    tjson_t* array = tjson_create_array();
    tjson_token_t token = s_scan_token();
    while (token.type != TJSON_TOKEN_RSQUAR) {
        tjson_t* val = s_parse_json_token(&token);
        tjson_array_push(array, val);
        token = s_scan_token();
        if (token.type == TJSON_TOKEN_COMMA) {
            token = s_scan_token();
            if (token.type == TJSON_TOKEN_RSQUAR) {
                s_error_at(&token, "extra ','");
                exit(1);
            }
        } else if (token.type != TJSON_TOKEN_RSQUAR) {
            s_error_at(&token, "missing ','");
            exit(1);
        }
    }
    return array;
}

tjson_t* s_parse_json_token(tjson_token_t *token) {
    // tjson_t *json = tjson_create(TJSON_)
    switch (token->type) {
    case TJSON_TOKEN_LBRACE:
        return s_parse_object();
    case TJSON_TOKEN_LSQUAR:
        return s_parse_array();
    case TJSON_TOKEN_MINUS:
    case TJSON_TOKEN_NUMBER:
        return s_parse_number(token);
    case TJSON_TOKEN_STRING:
        return s_parse_string(token);
    case TJSON_TOKEN_TRUE:
        return tjson_create_bool(1);
    case TJSON_TOKEN_FALSE:
        return tjson_create_bool(0);
    case TJSON_TOKEN_NULL:
        return tjson_create_null();
    case TJSON_TOKEN_ERROR:
        {
        s_error_at(token, token->start);
        exit(1);
        }
    }
    s_error_at(token, "unkown symbol");
    exit(1);
    return NULL;
}

tjson_t* s_parse_json(const char* json_str) {
    s_init_scanner(json_str);
    parser.hand_error = 0;
    parser.panic_mode = 0;
    tjson_token_t token = s_scan_token();
    return s_parse_json_token(&token);
}


/*==============*
 *    Utils     *
 *==============*/

char* s_file_read(const char* filename) {
    FILE* fp;
    fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Failed to open %s\n", filename);
        return NULL;
    }
    size_t size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = (char*)malloc(size+1);
    if (!buffer) {
        fclose(fp);
        fprintf(stderr, "Failed to alloc memory for %s buffer\n", filename);
        return NULL;
    }
    size_t bytes_read;
    bytes_read = fread(buffer, sizeof(char), size, fp);
    if (bytes_read < size) {
        fprintf(stderr, "Failed to read %s\n", filename);
        free(buffer);
        fclose(fp);
        return NULL;
    }

    buffer[bytes_read] = '\0';
    fclose(fp);
    return buffer;
}

#endif /* TJSON_IMPLEMENTATION */