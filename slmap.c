#include "slmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sl_map* sl_map_create(const unsigned int size) {
	sl_map *map = malloc(sizeof(sl_map));
	if (map==NULL) return NULL;
	map->size=size;
	map->entries=malloc(sizeof(sl_map_entry*)*size);
	if (map->entries==NULL) return NULL;
	for (unsigned int i=0;i<size;i++) {
		map->entries[i]=NULL;
	}
	return map;
}

void sl_map_free(sl_map *m) {
	for (unsigned int i=0;i<m->size;i++) {
		if (m->entries[i]==NULL) continue;
		sl_map_entry *tmp = m->entries[i];
		sl_map_entry *next;
		while (tmp!=NULL) {
			next = tmp->next;
			sl_map_entry_free(m, tmp);
			tmp=next;
		}
	}
	free(m->entries);
	free(m);
}

unsigned int sl_map_hash(const char *str, sl_map* m) {
	unsigned long hash = 5381;
	char ch;

	for (int i=0;i<strlen(str);i++) {
		ch = str[i];
		hash = ((hash >> 5) + hash) + ch;
	}

	return hash % m->size;
}

sl_map_entry* sl_map_entry_create(const char *key, void *data) {
	sl_map_entry *entry = malloc(sizeof(sl_map_entry));
	if (entry==NULL) return NULL;
	entry->key=malloc(strlen(key)+1);
	if (entry->key==NULL) {
		free(entry);
		return NULL;
	}
	strcpy(entry->key, key);
	entry->next=NULL;
	entry->data=data;
	return entry;
}

void sl_map_entry_free(sl_map *m, sl_map_entry *entry) {
	free(entry->key);
	m->free_data_function(entry->data);
	free(entry);
}

int sl_map_insert(sl_map *m, const char *key, void *data) {
	unsigned int hash = sl_map_hash(key, m);
	sl_map_entry *tmp = m->entries[hash];
	sl_map_entry *last;
	if (tmp==NULL) {
		// is empty
		m->entries[hash]=sl_map_entry_create(key, data);
		if (m->entries[hash]==NULL) return -1;
		return 0;
	}

	while (tmp!=NULL) {
		if (strcmp(key, tmp->key)==0) {
			// is overwriting data
			m->free_data_function(tmp->data);
			tmp->data=data;
			return 0;
		}
		last=tmp;
		tmp=tmp->next;
	}
	tmp=sl_map_entry_create(key, data);
	if (tmp==NULL) return -1;
	last->next=tmp;
	return 0;
}

int sl_map_remove(sl_map *m, const char *key) {
	unsigned int hash = sl_map_hash(key, m);
	sl_map_entry *tmp = m->entries[hash];
	sl_map_entry *last=NULL;

	while (tmp!=NULL) {
		if (strcmp(key, tmp->key)==0) {
			if (last==NULL) {
				if (tmp->next==NULL) {
					// is the first and only
					sl_map_entry_free(m, tmp);
					m->entries[hash]=NULL;
					return 0;
				} else {
					// is the first
					m->entries[hash]=tmp->next;
					sl_map_entry_free(m, tmp);
					return 0;
				}
			}
			last->next=tmp->next;
			sl_map_entry_free(m, tmp);
			return 0;
		}
		last=tmp;
		tmp=tmp->next;
	}
	return -1;
}

void* sl_map_get(sl_map *m, const char *key) {
	unsigned int hash = sl_map_hash(key, m);
	sl_map_entry *tmp = m->entries[hash];

	while (tmp!=NULL) {
		if (strcmp(key, tmp->key)==0) {
			return tmp->data;
		}
		tmp=tmp->next;
	}
	return NULL;
}

void sl_map_print(sl_map *m) {
	printf("map:%p size:%i\n", m, m->size);
	for (unsigned int i=0;i<m->size;i++) {
		if (m->entries[i]==NULL) continue;
		sl_map_entry *tmp = m->entries[i];
		printf("\tentry[%d]\n", i);
		while (tmp!=NULL) {
			printf("\t\t%p key:'%s' data:%p next:%p\n", tmp, tmp->key, tmp->data, tmp->next);
			tmp=tmp->next;
		}
	}
}

sl_map* sl_map_resize(sl_map *m, unsigned int size) {
	sl_map *new_map = sl_map_create(size);
	if (new_map==NULL) return NULL;
	new_map->free_data_function=m->free_data_function;

	for (unsigned int i=0;i<m->size;i++) {
		if (m->entries[i]==NULL) continue;
		sl_map_entry *tmp = m->entries[i];
		while (tmp!=NULL) {
			if (sl_map_insert(new_map, tmp->key, tmp->data)<0) {
				sl_map_free(new_map);
				return NULL;
			}
			tmp=tmp->next;
		}
	}
	return new_map;
}
