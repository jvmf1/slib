# installation
```sh
git clone https://github.com/jvmf1/slib
cd slib
sudo make install
```

# slstr.h example
```c
#include <slib/slstr.h>
.
.
.
// creates initial string with capacity of 20
sl_str *str = sl_str_create_cap(20);
printf("input string: ");
// gets stdin string and increases capacity by 10 everytime when needed
sl_str_gets(str, 10);
printf("you've typed:%s\n", str->data);
sl_str_free(str);

FILE *f = popen("uname", "r");
sl_str *os = sl_str_create_cap(10);
// gets file string and increases capacity by 5 everytime when needed
sl_str_fgets(os, f, 5);
// replaces the last '\n' char with '\0'
sl_str_replace_charn(os, os->len-1, '\0');
printf("you are using:%s\n", os->data);
sl_str_free(os);
fclose(f);
```
# slll.h + slstr.h example
```c
#include <slib/slll.h>
.
.
.
// you can make your linked list with any *type or *struct
sl_ll *ll = sl_ll_create();
sl_ll_push(ll, sl_str_create("apple"));
sl_ll_push(ll, sl_str_create("tree"));
sl_ll_push(ll, sl_str_create("blue"));
sl_ll_push(ll, sl_str_create("orange"));

// iterate through linked list and delete "blue"
sl_ll_entry *entry=ll->head;
sl_ll_entry *next_entry;
while (entry!=NULL) {
	next_entry=entry->next;
	sl_str *entry_string = ((sl_str*)entry->data);
	if (strcmp("blue", entry_string->data)==0) {
		sl_ll_remove(ll, entry);
		sl_str_free(entry_string);
	}
	entry=next_entry;
}

// iterate again printing all strings
entry=ll->head;
while (entry!=NULL) {
	sl_str *entry_string = ((sl_str*)entry->data);
	printf("%s\n", entry_string->data);
	entry=entry->next;
}

// after using the linked list, free all the data
entry=ll->head;
while(entry!=NULL) {
	sl_str *entry_string = ((sl_str*)entry->data);
	sl_str_free(entry_string);
	entry=entry->next;
}

// finally free the linked list
sl_ll_free(ll);

```
