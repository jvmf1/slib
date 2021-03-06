CC=cc
CFLAGS=-Wall -Wextra -fPIC -Werror
NAME=libslib

INCLUDEDESTDIR=/usr/local/include/slib
LIBDESTDIR=/usr/local/lib

$(info $$CC = $(CC))
$(info $$CFLAGS = $(CFLAGS))
$(info $$INCLUDEDESTDIR = $(INCLUDEDESTDIR))
$(info $$LIBDESTDIR = $(LIBDESTDIR))

OBJ=ll.o str.o map.o
# SRC=ll.c str.c map.c
HEADERS=ll.h str.h map.h

all: $(NAME).so

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(NAME).so: $(OBJ)
	$(CC) -shared $(OBJ) -o $@

install: $(NAME).so
	mkdir -p $(INCLUDEDESTDIR)
	mkdir -p $(LIBDESTDIR)
	cp -f $(HEADERS) $(INCLUDEDESTDIR)
	cp -f $(NAME).so $(LIBDESTDIR)

uninstall:
	for h in $(HEADERS); do \
		rm -f $(INCLUDEDESTDIR)/$$h ; \
	done
	rm -f $(LIBDESTDIR)/$(NAME).so

clean:
	rm -f *.o
	rm -f *.so
