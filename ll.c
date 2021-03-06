#include "ll.h"
#include <stdio.h>
#include <stdlib.h>

sl_ll_entry* sl_ll_entry_create(void *data) {
	sl_ll_entry *entry = malloc(sizeof(sl_ll_entry));
	entry->next=NULL;
	entry->prev=NULL;
	entry->data=data;
	return entry;
}

void sl_ll_entry_free(sl_ll *ll, sl_ll_entry *entry) {
	if (ll->free_data_function!=NULL)
		ll->free_data_function(entry->data);
	free(entry);
}

sl_ll* sl_ll_create() {
	sl_ll *ll = malloc(sizeof(sl_ll));
	ll->head=NULL;
	ll->tail=NULL;
	ll->free_data_function=NULL;
	return ll;
}

void sl_ll_pop(sl_ll *ll) {
	// there is no entries
	if (ll->head==NULL) return;

	if (ll->head==ll->tail) {
		// there is only one entry
		sl_ll_entry_free(ll,ll->head);
		ll->head=NULL;
		ll->tail=NULL;
		return;
	}
	if (ll->head->next==ll->tail) {
		// there is two entries
		sl_ll_entry_free(ll,ll->tail);
		ll->head->next=NULL;
		ll->tail=ll->head;
		return;
	}
	// there is 3+
	sl_ll_entry *last = ll->tail;
	ll->tail=ll->tail->prev;
	ll->tail->next=NULL;
	sl_ll_entry_free(ll,last);
}

void sl_ll_remove(sl_ll *ll, sl_ll_entry *entry) {
	if (entry==NULL) return;
	if (ll->head==NULL) return;
	if (ll->head->next==NULL) {
		// is the only entry
		sl_ll_entry_free(ll,entry);
		ll->head=NULL;
		ll->tail=NULL;
		return;
	}

	// there is 2 entries
	if (ll->head->next==ll->tail) {
		if (entry==ll->tail) {
			sl_ll_entry_free(ll,ll->tail);
			ll->head->next=NULL;
			ll->head->prev=NULL;
			ll->tail=ll->head;
			return;
		} else {
			sl_ll_entry_free(ll,ll->head);
			ll->tail->next=NULL;
			ll->tail->prev=NULL;
			ll->head=ll->tail;
			return;
		}
	}

	if (entry==ll->head) {
		// is the first entry
		entry->next->prev=NULL;
		ll->head=entry->next;
		sl_ll_entry_free(ll,entry);
		return;
	}

	if (entry==ll->tail) {
		// is the last entry
		entry->prev->next=NULL;
		ll->tail=entry->prev;
		sl_ll_entry_free(ll,entry);
		return;
	}

	entry->prev->next=entry->next;
	entry->next->prev=entry->prev;
	sl_ll_entry_free(ll,entry);
}

int sl_ll_push(sl_ll *ll, void *data) {
	sl_ll_entry *new_entry = sl_ll_entry_create(data);
	if (new_entry==NULL) return -1;
	if (ll->head==NULL) {
		// is empty
		ll->head=new_entry;
		ll->tail=new_entry;
		return 0;
	}

	new_entry->prev=ll->tail;
	ll->tail->next=new_entry;
	ll->tail=new_entry;
	return 0;
}

int sl_ll_insert_after(sl_ll *ll, sl_ll_entry *entry, void *data) {
	sl_ll_entry *new_entry = sl_ll_entry_create(data);
	if (new_entry==NULL) return -1;
	if (ll->head==NULL) {
		// linked list is empty
		ll->head=new_entry;
		ll->tail=new_entry;
		return 0;
	}
	new_entry->prev=entry;
	new_entry->next=entry->next;
	if (entry->next==NULL) {
		// is inserting in the last position
		entry->next=new_entry;
		ll->tail=new_entry;
		return 0;
	}
	entry->next->prev=new_entry;
	entry->next=new_entry;
	return 0;
}

int sl_ll_insert_before(sl_ll *ll, sl_ll_entry *entry, void *data) {
	sl_ll_entry *new_entry = sl_ll_entry_create(data);
	if (new_entry==NULL) return -1;
	if (ll->head==NULL) {
		// linked list is empty
		ll->head=new_entry;
		ll->tail=new_entry;
		return 0;
	}
	new_entry->next=entry;
	new_entry->prev=entry->prev;
	if (entry->prev==NULL) {
		// is inserting in the first position
		entry->prev=new_entry;
		ll->head=new_entry;
		return 0;
	}
	entry->prev->next=new_entry;
	entry->prev=new_entry;
	return 0;
}

void sl_ll_free(sl_ll *ll) {
	sl_ll_entry *current = ll->head;
	if (current==NULL) {
		free(ll);
		return;
	}
	
	sl_ll_entry *next;
	while(current!=NULL) {
		next = current->next;
		sl_ll_entry_free(ll,current);
		current=next;
	}

	free(ll);
}

void sl_ll_print(sl_ll *ll) {
	printf("ll %p head:%p tail:%p\n", ll, ll->head, ll->tail);
	sl_ll_entry *current = ll->head;
	while (current!=NULL) {
		printf("\t%p data:%p\tprev:%p next:%p\n", current, current->data, current->prev, current->next);
		current=current->next;
	}
}
