#include "slll.h"
#include <stdio.h>
#include <stdlib.h>

sl_ll_entry* sl_ll_entry_create(void *data) {
	sl_ll_entry *entry = malloc(sizeof(sl_ll_entry));
	entry->next=NULL;
	entry->prev=NULL;
	entry->data=data;
	return entry;
}

void sl_ll_entry_free(sl_ll_entry *entry) {
	free(entry);
}

sl_ll* sl_ll_create() {
	sl_ll *ll = malloc(sizeof(sl_ll));
	ll->head=NULL;
	ll->tail=NULL;
	return ll;
}

void sl_ll_pop(sl_ll *ll) {
	// there is no entries
	if (ll->head==NULL) return;

	if (ll->head==ll->tail) {
		// there is only one entry
		sl_ll_entry_free(ll->head);
		ll->head=NULL;
		ll->tail=NULL;
		return;
	}
	if (ll->head->next==ll->tail) {
		// there is two entries
		sl_ll_entry_free(ll->tail);
		ll->head->next=NULL;
		ll->tail=ll->head;
		return;
	}
	// there is 3+
	sl_ll_entry *last = ll->tail;
	ll->tail=ll->tail->prev;
	ll->tail->next=NULL;
	sl_ll_entry_free(last);
}

void sl_ll_popx(sl_ll *ll, sl_ll_entry *entry) {
	if (entry==NULL) return;
	if (ll->head==NULL) return;
	if (ll->head->next==NULL) {
		// is the only entry
		sl_ll_entry_free(entry);
		ll->head=NULL;
		ll->tail=NULL;
		return;
	}
	if (ll->head->next->next==NULL) {
		// is the 2nd entry
		sl_ll_entry_free(entry);
		ll->head->next=NULL;
		ll->tail=ll->head;
		return;
	}

	if (entry->next==NULL) {
		// is the last entry
		ll->tail=ll->tail->prev;
		ll->tail->next=NULL;
		sl_ll_entry_free(entry);
		return;
	}

	sl_ll_entry *tmp = entry;
	tmp->prev->next=tmp->next;
	tmp->next->prev=tmp->prev;
	sl_ll_entry_free(tmp);
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

void sl_ll_free(sl_ll *ll) {
	sl_ll_entry *current = ll->head;
	if (current==NULL) {
		free(ll);
		return;
	}
	
	while(current!=NULL) {
		sl_ll_entry_free(current);
		current=current->next;
	}

	free(ll);
}

void sl_ll_print(sl_ll *ll) {
	printf("slll %p head:%p tail:%p\n", ll, ll->head, ll->tail);
	sl_ll_entry *current = ll->head;
	while (current!=NULL) {
		printf("\t%p data:%p\tnext:%p prev:%p\n", current, current->data, current->next, current->prev);
		current=current->next;
	}
}
