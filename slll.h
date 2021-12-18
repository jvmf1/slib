#pragma once

typedef struct sl_ll_entry {
	struct sl_ll_entry *next;
	struct sl_ll_entry *prev;
	void *data;
} sl_ll_entry;

typedef struct sl_ll {
	sl_ll_entry *head;
	sl_ll_entry *tail;
	void (*free_data_function)(void*);
} sl_ll;

sl_ll_entry* sl_ll_entry_create(void *data); 

void sl_ll_entry_free(sl_ll *ll, sl_ll_entry *entry);

sl_ll* sl_ll_create();

void sl_ll_free(sl_ll *ll);

int sl_ll_push(sl_ll *ll, void *data);

void sl_ll_pop(sl_ll *ll);

void sl_ll_remove(sl_ll *ll, sl_ll_entry *entry);

void sl_ll_print(sl_ll *ll);

int sl_ll_insert_after(sl_ll *ll, sl_ll_entry *entry, void *data);

int sl_ll_insert_before(sl_ll *ll, sl_ll_entry *entry, void *data);

