CC=cc
INCLUDEDESTDIR=/usr/include/slib
LIBDESTDIR=/usr/lib
CFLAGS=-Wall
LIBFLAGS=-fPIC
OBJ=slll.o slstr.o slmap.o
SRC=slll.c slstr.c slmap.c
HEADERS=slll.h slstr.h slmap.h
NAME=libslib

all: $(NAME)

slll.o: slll.c slll.h
	$(CC) $(CFLAGS) $(LIBFLAGS) slll.c -c

slstr.o: slstr.c slstr.h
	$(CC) $(CFLAGS) $(LIBFLAGS) slstr.c -c

slmap.o: slmap.c slmap.h
	$(CC) $(CFLAGS) $(LIBFLAGS) slmap.c -c

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
