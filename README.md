# installation
```sh
git clone https://github.com/jvmf1/slib
cd slib
sudo make install
```

# slstr.h example
```c
#include <slib/slstr.h>

int main() {

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
	// trims all '\n' chars at the beginning and end of the string
	sl_str_trim(os, '\n');
	printf("you are using:%s\n", os->data);
	sl_str_free(os);
	pclose(f);
}

```
# slll.h + slstr.h example
```c
#include <slib/slstr.h>
#include <string.h>
#include <slib/slll.h>

// create a free function with void* arg so slll can free everything correctly
void free_data(void *data) {
	sl_str *str = ((sl_str*)data);
	sl_str_free(str);
}


int main() {
	// you can make your linked list with any *type or *struct
	sl_ll *ll = sl_ll_create();
	// sets free data function
	ll->free_data_function=free_data;
	
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

	// finally free the linked list
	sl_ll_free(ll);
}

```
# slmap.h + slstr.h example
```c
#include <slib/slstr.h>
#include <slib/slmap.h>

// create a free function with void* arg so slmap can free everything correctly
void free_data(void *data) {
	sl_str *str = ((sl_str*)data);
	sl_str_free(str);
}


int main() {
	sl_map *map = sl_map_create(1);
	// set map data free function
	map->free_data_function=free_data;

	sl_map_insert(map, "20", sl_str_create("twenty"));
	sl_map_insert(map, "1", sl_str_create("one"));
	sl_map_insert(map, "15", sl_str_create("fifteen"));
	sl_map_print(map);

	sl_str *str = ((sl_str*)sl_map_get(map, "20"));
	if (str!=NULL)
		printf("found:%s\n", str->data);

	sl_map_remove(map, "15");
	sl_map_print(map);

	sl_map *new_map = sl_map_resize(map, 5);
	sl_map_free(map);
	sl_map_print(new_map);
	sl_map_free(new_map);
}


```
