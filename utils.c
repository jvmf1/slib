#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

sl_str* sl_utils_path(const char *arg) {
	sl_str *str = sl_str_create_cap(strlen(arg)+1);
	if (str == NULL)
		return NULL;
	if (arg[0] != '/') {
		if (sl_str_printf(str, "%s/%s", getenv("PWD"), arg) == -1) {
			sl_str_free(str);
			return NULL;
		}
	} else {
		memcpy(str->data, arg, str->cap);
		str->len = str->cap - 1;
	}
	sl_str_replace(str, "./", "");
	sl_str_rm_consecutive_char(str, '/');
	return str;
}

void die(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}
