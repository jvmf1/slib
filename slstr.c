#include "slstr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sl_str_replace_char(sl_string *str, const char old, const char new) {
	if (new=='\0') return -1;
	for (unsigned int i=0;i<str->len;i++) {
		if (str->data[i]==old) str->data[i]=new;
	}
	return 0;
}

int sl_str_replace_charn(sl_string *str, const unsigned int n, const char new) {
	if (new=='\0' && n <= str->len) {
		str->len=n;
		str->data[n]=new;
		return 0;
	}
	if (n >= str->len) return -1;
	str->data[n]=new;
	return 0;
}

void sl_str_clear(sl_string *str) {
	str->len=0;
	str->data[0]='\0';
}

int sl_str_trim_cap(sl_string *str) {
	char *new_data = malloc(sizeof(char)*str->len+1);
	if (new_data==NULL) return -1;
	for(unsigned int i=0;i<str->len+1;i++) {
		new_data[i]=str->data[i];
	}
	free(str->data);
	str->data=new_data;
	str->cap=str->len+1;
	return 0;
}

sl_string* sl_str_reverse(sl_string *str) {
	char temp;
	for (unsigned int i=0;i<str->len/2;i++) {
		temp = str->data[i];
		str->data[i] = str->data[str->len - i - 1];
		str->data[str->len - i - 1]=temp;
	}
	return str;
}

sl_string* sl_str_create(const char *s) {
	sl_string *str = malloc(sizeof(sl_string));
	if (str != NULL) {
		str->len = strlen(s);
		str->cap = str->len + 1;
		str->data = malloc(sizeof(char) * str->cap);
		if (str->data==NULL) {
			free(str);
			return NULL;
		}
		for (unsigned int i=0;i<str->len;i++) {
			str->data[i]=s[i];
		}
	}
	return str;
}

sl_string* sl_str_create_cap(size_t cap) {
	if (cap==0) return NULL;
	sl_string *str = malloc(sizeof(sl_string));
	if (str != NULL) {
		str->len = 0;
		str->cap = cap;
		str->data = malloc(sizeof(char) * str->cap);
		if (str->data==NULL) {
			free(str);
			return NULL;
		}
	}
	return str;
}

// get stdin and increases capacity by cap_incr when needed
int sl_str_gets(sl_string *str, size_t cap_incr) {
	char ch;
	size_t necessary_cap;
	int sucess;
	while((ch=getc(stdin))!='\n') {
		// new char + null;
		necessary_cap = str->len + 2;
		if (str->cap < necessary_cap) {
			sucess = sl_str_incr_cap(str, cap_incr);
			if (sucess==-1) {
				str->data[str->len]='\0';
				return -1;
			}
		}
		str->data[str->len]=ch;
		str->len++;
	}
	str->data[str->len]='\0';
	return 0;
}

// get FILE stream and increases capacity by cap_incr when needed
int sl_str_fgets(sl_string *str, FILE *stream, size_t cap_incr) {
	char ch;
	size_t necessary_cap;
	int sucess;
	while((ch=getc(stream))!=EOF) {
		// new char + null;
		necessary_cap = str->len + 2;
		if (str->cap < necessary_cap) {
			sucess = sl_str_incr_cap(str, cap_incr);
			if (sucess==-1) {
				str->data[str->len]='\0';
				return -1;
			}
		}
		str->data[str->len]=ch;
		str->len++;
	}
	str->data[str->len]='\0';
	return 0;
}

int sl_str_incr_cap(sl_string *str, size_t cap) {
	if (cap==0) return 0;
	size_t new_cap = str->cap + cap;
	char *new_data = malloc(new_cap);
	if (new_data==NULL) return -1;
	unsigned int i;
	for (i=0;i<str->len+1;i++) {
		new_data[i]=str->data[i];
	}
	str->cap=new_cap;
	free(str->data);
	str->data=new_data;
	return 0;
}

int sl_str_cat(sl_string *dest, char *str) {
	size_t len = strlen(str);
	if (len==0) return 0;
	unsigned int i;
	size_t new_len, necessary_cap;
	new_len = dest->len + len;
	necessary_cap = new_len + 1;
	if (dest->cap < necessary_cap) {
		int sucess = sl_str_incr_cap(dest, necessary_cap - dest->cap);
		if (sucess==-1) return -1;
	} 
	for (i=0;i<len+1;i++) {
		dest->data[i+dest->len]=str[i];
	}
	dest->len=new_len;

	return 0;
}		

int sl_str_scat(sl_string *dest, sl_string *str) {
	if (str->len==0) return 0;
	unsigned int i;
	size_t new_len, necessary_cap;
	new_len = dest->len + str->len;
	necessary_cap = new_len + 1;
	if (dest->cap < necessary_cap) {
		int sucess = sl_str_incr_cap(dest, necessary_cap - dest->cap);
		if (sucess==-1) return -1;
	} 
	for (i=0;i<str->len+1;i++) {
		dest->data[i+dest->len]=str->data[i];
	}
	dest->len=new_len;

	return 0;
}		

void sl_str_free(sl_string *str) {
	free(str->data);
	free(str);
}

void sl_str_print(const sl_string *str) {
	if (str->len==0)
		printf("cap:%ld\nlen:%ld\ndata:(nil)\n", str->cap, str->len);
	else
		printf("cap:%ld\nlen:%ld\ndata:%s\n", str->cap, str->len, str->data);
}

int sl_str_set(sl_string *str, const char *s) {
	size_t len = strlen(s);
	size_t necessary_cap = len + 1;
	if (str->cap < necessary_cap) {
		int sucess = sl_str_incr_cap(str, necessary_cap - str->cap);
		if (sucess==-1) return -1;
	}
	for (unsigned int i=0;i<len+1;i++) {
		str->data[i]=s[i];
	}
	str->len=len;
	return 0;
}
