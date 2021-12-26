#include "slstr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

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

void sl_str_reverse(sl_str *str) {
	char temp;
	for (size_t i=0;i<str->len/2;i++) {
		temp = str->data[i];
		str->data[i] = str->data[str->len - i - 1];
		str->data[str->len - i - 1]=temp;
	}
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
		if (ch==EOF) {
			str->data[str->len]='\0';
			return 1;
		}
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

void sl_str_trim_all(sl_str *str, const char ch) {
	size_t j = 0;
	size_t i;
	bool addchar = false;
	for (i=0;i<str->len;i++) {
		if (str->data[i]==ch) {
			if (addchar==true) {
				addchar=false;
				str->data[j]=str->data[i];
				j++;
			}
		} else {
			addchar=true;
			str->data[j]=str->data[i];
			j++;
		}
	}
	if (str->data[j]==ch && addchar==false)
		j--;
	str->len=j;
	str->data[j]='\0';
}

void sl_str_trim(sl_str *str, const char ch) {
	sl_str_trim_right(str, ch);
	sl_str_trim_left(str, ch);
}

void sl_str_trim_right(sl_str *str, const char ch) {
	if (str->len == 0)
		return;
	size_t i;
	for (i = str->len -1; i != 0; i--) {
		if (str->data[i] != ch) {
			break;
		}
	}
	if (i == 0 && str->data[0] == ch) {
		sl_str_clear(str);
		return;
	}
	str->data[i + 1] = '\0';
	str->len = i + 1;
}

void sl_str_trim_left(sl_str *str, const char ch) {
	if (str->len == 0)
		return;
	size_t i;
	for (i = 0; i < str->len; i++) {
		if (str->data[i] != ch) {
			break;
		}
	}
	if (i==str->len) {
		sl_str_clear(str);
		return;
	}
	memcpy(str->data, str->data + i, str->len -i + 1);
	str->len -= i;
}

size_t sl_str_distance (sl_str *str, sl_str * str2){
	size_t matrix[str->len + 1][str2->len + 1];
	size_t i,j;
	size_t delete, insert, substitute, minimum;
	for (i = 0; i <= str->len; i++) {
		matrix[i][0] = i;
	}
	for (i = 0; i <= str2->len; i++) {
		matrix[0][i] = i;
	}
	for (i = 1; i <= str->len; i++) {

		for (j = 1; j <= str2->len; j++) {

			if (str->data[i-1] == str2->data[j-1]) {
				matrix[i][j] = matrix[i-1][j-1];
			}
			else {

				delete = matrix[i-1][j] + 1;
				insert = matrix[i][j-1] + 1;
				substitute = matrix[i-1][j-1] + 1;
				minimum = delete;
				if (insert < minimum) {
					minimum = insert;
				}
				if (substitute < minimum) {
					minimum = substitute;
				}
				matrix[i][j] = minimum;
			}
		}
	}
	return matrix[str->len][str2->len];
}

sl_str* sl_str_fread(FILE *f) {
	fseek(f, 0, SEEK_END);
	long int size = ftell(f);
	if (size == -1)
		return NULL;
	fseek(f, 0, SEEK_SET);
	sl_str *str = sl_str_create_cap(size+1);
	if (str == NULL)
		return NULL;
	fread(str->data, size+1, 1, f);
	str->len = size;
	return str;
}

int sl_str_ccat(sl_str *str, const char ch) {
	if (str->len + 1 >= str->cap) {
		if (sl_str_incr_cap(str, 1) == -1)
			return -1;
	}
	str->len++;
	str->data[str->len - 1] = ch;
	str->data[str->len] = '\0';
	return 0;
}

int sl_str_breakline(sl_str *str, size_t count) {

	if (count == 0) {
		return 0;
	}

	size_t addcap=0;
	size_t j=0;
	size_t i;
	// get the amount to increase capacity
	for (i = 0; i < str->len; i++) {
		if (str->data[i] == '\n')
			j = 0;

		j++;
		if (j >= count) {
			addcap++;
			j = 0;
			continue;
		}
	}

	if (addcap + str->len + 1 > str->cap) {
		if (sl_str_incr_cap(str, addcap) != 0)
			return -1;
	}

	sl_str *new_str = sl_str_create_cap(str->cap);
	if (new_str == NULL)
		return -1;

	j=0;

	for (i = 0; i < str->len; i++) {
		if (str->data[i] == '\n')
			j = 0;

		j++;
		if (j > count) {
			j = 0;
			new_str->data[new_str->len] = '\n';
			new_str->data[new_str->len+1] = str->data[i];
			j++;
			new_str->len+=2;
			continue;
		}
		new_str->data[new_str->len] = str->data[i];
		new_str->len++;
	}

	str->cap = new_str->cap;
	str->len = new_str->len;
	str->data = new_str->data;
	free(new_str);

	return 0;
}
