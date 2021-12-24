CC=cc
CFLAGS=-Wall -Wextra -fPIC
NAME=libslib

OS=$(shell uname)
ifeq ($(OS), Linux)
	INCLUDEDESTDIR=/usr/include/slib
	LIBDESTDIR=/usr/lib
else
	# BSD
	INCLUDEDESTDIR=/usr/local/include/slib
	LIBDESTDIR=/usr/local/lib
endif

OBJ=slll.o slstr.o slmap.o
# SRC=slll.c slstr.c slmap.c
HEADERS=slll.h slstr.h slmap.h

all: $(NAME)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(NAME): $(OBJ)
	$(CC) -shared $(OBJ) -o $@.so

install: $(NAME)
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
