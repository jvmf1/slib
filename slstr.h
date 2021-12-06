
#pragma once

#include <stddef.h>
#include <stdio.h>

typedef struct sl_string {
	size_t cap;
	size_t len;
	char *data;
} sl_string;

// replaces nth char
int sl_str_replace_charn(sl_string *str, const unsigned int n, const char new);

int sl_str_replace_char(sl_string *str, const char old, const char new);

void sl_str_clear(sl_string *str);

// adjust capacity to exactly fit the string
int sl_str_trim_cap(sl_string *str);

sl_string* sl_str_reverse(sl_string *str);

void sl_str_print(const sl_string *str);

sl_string* sl_str_create(const char *s);

// creates empty string with pre allocated capacity
sl_string* sl_str_create_cap(size_t cap);

void sl_str_free(sl_string *str);

// automaticly concatenates and adjust capacity if needed
int sl_str_scat(sl_string *dest, sl_string *str);

// automaticly concatenates and adjust capacity if needed
int sl_str_cat(sl_string *dest, char *str);

int sl_str_incr_cap(sl_string *str, size_t cap);

// automaticly sets string to s and adjust capacity if needed
int sl_str_set(sl_string *str, const char *s);

// get stdin and increases cap by cap_incr when needed until '\n'
int sl_str_gets(sl_string *str, size_t cap_incr);

// get FILE stream and increases cap by cap_incr when needed until EOF
int sl_str_fgets(sl_string *str, FILE *stream, size_t cap_incr);
