#include "slstr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void sl_str_tolower(sl_str *str) {
	for(size_t i=0;i<str->len;i++) {
		str->data[i]=tolower(str->data[i]);
	}
}

void sl_str_toupper(sl_str *str) {
	for(size_t i=0;i<str->len;i++) {
		str->data[i]=toupper(str->data[i]);
	}
}

int sl_str_replace_char(sl_str *str, const char old, const char new) {
	if (new=='\0') return -1;
	for (size_t i=0;i<str->len;i++) {
		if (str->data[i]==old) str->data[i]=new;
	}
	return 0;
}

int sl_str_replace_charn(sl_str *str, const size_t n, const char new) {
	if (new=='\0' && n <= str->len) {
		str->len=n;
		str->data[n]=new;
		return 0;
	}
	if (n >= str->len) return -1;
	str->data[n]=new;
	return 0;
}

void sl_str_clear(sl_str *str) {
	str->len=0;
	str->data[0]='\0';
}

int sl_str_trim_cap(sl_str *str) {
	if(realloc(str->data, sizeof(char)*str->len+1)==NULL) return -1;
	str->cap=str->len+1;
	return 0;
}

sl_str* sl_str_reverse(sl_str *str) {
	char temp;
	for (size_t i=0;i<str->len/2;i++) {
		temp = str->data[i];
		str->data[i] = str->data[str->len - i - 1];
		str->data[str->len - i - 1]=temp;
	}
	return str;
}

sl_str* sl_str_create(const char *s) {
	sl_str *str = malloc(sizeof(sl_str));
	if (str != NULL) {
		str->len = strlen(s);
		str->cap = str->len + 1;
		str->data = malloc(sizeof(char) * str->cap);
		if (str->data==NULL) {
			free(str);
			return NULL;
		}
		memcpy(str->data, s, str->len+1);
	}
	return str;
}

sl_str* sl_str_create_cap(size_t cap) {
	if (cap==0) return NULL;
	sl_str *str = malloc(sizeof(sl_str));
	if (str != NULL) {
		str->len = 0;
		str->cap = cap;
		str->data = malloc(sizeof(char) * str->cap);
		if (str->data==NULL) {
			free(str);
			return NULL;
		}
		str->data[0]='\0';
	}
	return str;
}

// get stdin and increases capacity by cap_incr when needed
int sl_str_gets(sl_str *str, size_t cap_incr) {
	return sl_str_fgetsx(str, stdin, '\n', cap_incr);
}

// get FILE stream and increases capacity by cap_incr when needed
int sl_str_fgets(sl_str *str, FILE *stream, size_t cap_incr) {
	return sl_str_fgetsx(str, stream, EOF, cap_incr);
}

int sl_str_fgetsx(sl_str *str, FILE *stream, const char x, size_t cap_incr) {
	char ch;
	size_t necessary_cap;
	int sucess;
	while((ch=getc(stream))!=x) {
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

int sl_str_incr_cap(sl_str *str, size_t cap) {
	if (cap==0) return 0;
	size_t new_cap = str->cap + cap;
	char *new_data = malloc(new_cap);
	if (new_data==NULL) return -1;
	memcpy(new_data, str->data, sizeof(char)*str->len+1);
	str->cap=new_cap;
	free(str->data);
	str->data=new_data;
	return 0;
}

int sl_str_cat(sl_str *dest, char *str) {
	size_t len = strlen(str);
	if (len==0) return 0;
	size_t new_len, necessary_cap;
	new_len = dest->len + len;
	necessary_cap = new_len + 1;
	if (dest->cap < necessary_cap) {
		int sucess = sl_str_incr_cap(dest, necessary_cap - dest->cap);
		if (sucess==-1) return -1;
	} 
	memcpy(&dest->data[dest->len], str, len+1);
	dest->len=new_len;

	return 0;
}		

int sl_str_scat(sl_str *dest, sl_str *str) {
	if (str->len==0) return 0;
	size_t new_len, necessary_cap;
	new_len = dest->len + str->len;
	necessary_cap = new_len + 1;
	if (dest->cap < necessary_cap) {
		int sucess = sl_str_incr_cap(dest, necessary_cap - dest->cap);
		if (sucess==-1) return -1;
	} 
	memcpy(&dest->data[dest->len], str->data, str->len+1);
	dest->len=new_len;

	return 0;
}		

void sl_str_free(sl_str *str) {
	free(str->data);
	free(str);
}

void sl_str_print(const sl_str *str) {
	if (str->len==0)
		printf("cap:%ld\nlen:%ld\ndata:(nil)\n", str->cap, str->len);
	else
		printf("cap:%ld\nlen:%ld\ndata:%s\n", str->cap, str->len, str->data);
}

int sl_str_set(sl_str *str, const char *s) {
	size_t len = strlen(s);
	size_t necessary_cap = len + 1;
	if (str->cap < necessary_cap) {
		int sucess = sl_str_incr_cap(str, necessary_cap - str->cap);
		if (sucess==-1) return -1;
	}
	memcpy(str->data, s, sizeof(char)*len+1);
	str->len=len;
	return 0;
}

int sl_str_sset(sl_str *str, sl_str *s) {
	size_t necessary_cap = s->len + 1;
	if (str->cap < necessary_cap) {
		int sucess = sl_str_incr_cap(str, necessary_cap - str->cap);
		if (sucess==-1) return -1;
	}
	memcpy(str->data, s->data, sizeof(char)*s->len+1);
	str->len=s->len;
	return 0;
}
