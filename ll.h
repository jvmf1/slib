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

#define SL_LL_FOREACH(entry, tmp) \
		for( ; (entry) && ( (tmp) = ((entry)->data), 1) ; (entry) = ((entry)->next) )

#define SL_LL_FOREACH_SAFE(entry, next_entry, tmp) \
		for( ; (entry) && ((next_entry) = ((entry)->next), 1) && ((tmp) = ((entry)->data), 1) ; (entry) = (next_entry) )

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

