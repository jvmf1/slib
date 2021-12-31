#pragma once
#include <stddef.h>

typedef struct sl_map_entry {
	char *key;
	void *data;
	struct sl_map_entry *next;
} sl_map_entry;

typedef struct sl_map {
	size_t size;
	sl_map_entry **entries;
	void (*free_data_function)(void*);
} sl_map;


sl_map* sl_map_create(size_t size);

void sl_map_free(sl_map *map);

size_t sl_map_hash(const char *str, sl_map* m);

sl_map_entry* sl_map_entry_create(const char *key, void *data);

void sl_map_entry_free(sl_map *m, sl_map_entry *entry);

int sl_map_insert(sl_map *m, const char *key, void *data);

int sl_map_remove(sl_map *m, const char *key);

void* sl_map_get(sl_map *m, const char *key);

void sl_map_print(sl_map *m);

// sl_map_resize does not free the original map
sl_map* sl_map_resize(sl_map *m, size_t size);
