
#pragma once

#include <stddef.h>
#include <stdio.h>

typedef struct sl_str {
	size_t cap;
	size_t len;
	char *data;
} sl_str;

void sl_str_tolower(sl_str *str);

void sl_str_toupper(sl_str *str);

// replaces nth char
int sl_str_replace_charn(sl_str *str, const size_t n, const char new);

int sl_str_replace_char(sl_str *str, const char old, const char new);

void sl_str_clear(sl_str *str);

// adjust capacity to exactly fit the string
int sl_str_trim_cap(sl_str *str);

void sl_str_reverse(sl_str *str);

void sl_str_print(const sl_str *str);

sl_str* sl_str_create(const char *s);

// creates empty string with pre allocated capacity
sl_str* sl_str_create_cap(size_t cap);

void sl_str_free(sl_str *str);

// automaticly concatenates and adjust capacity if needed
int sl_str_scat(sl_str *dest, sl_str *str);

// automaticly concatenates and adjust capacity if needed
int sl_str_cat(sl_str *dest, char *str);

int sl_str_incr_cap(sl_str *str, size_t cap);

// automaticly sets string to s and adjust capacity if needed
int sl_str_set(sl_str *str, const char *s);

int sl_str_sset(sl_str *str, sl_str *s);

/* get stdin and increases cap by cap_incr when needed until '\n' or EOF
 * returns:
 *		0 if finds '\n'
 *		1 if finds EOF
 *		-1 if fail to incr cap */
int sl_str_gets(sl_str *str, size_t cap_incr);

/* get FILE stream and increases cap by cap_incr when needed until EOF
 * return:
 *		0 if finds EOF
 *		-1 if fail to incr cap */
int sl_str_fgets(sl_str *str, FILE *stream, size_t cap_incr);

/* get FILE stream and increases cap by cap_incr when needed until 'x' or EOF
 * returns:
 *		0 if finds 'x'
 *		1 if finds EOF
 *		-1 if fail to incr cap */
int sl_str_fgetsx(sl_str *str, FILE *stream, const char x, size_t cap_incr);

// removes conscultives 'ch' and 'ch' at the beginning and end
void sl_str_trim_all(sl_str *str, const char ch);

// removes 'ch' at the beginning and end
void sl_str_trim(sl_str *str, const char ch);

void sl_str_trim_right(sl_str *str, const char ch);

void sl_str_trim_left(sl_str *str, const char ch);

// calculate levenshtein distance
size_t sl_str_distance (sl_str *str, sl_str * str2);

sl_str* sl_str_fread(FILE *f);
