#pragma once
#include <slib/str.h>

/* used for parsing file path in argv */
sl_str* sl_utils_path(const char *arg);

/* print message and exit(EXIT_FAILURE) */
void die(const char *fmt, ...);
