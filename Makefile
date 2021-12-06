CC=cc
INCLUDEDESTDIR=/usr/include
LIBDESTDIR=/usr/lib
CFLAGS=-Wall
LIBFLAGS=-fPIC
OBJ=slll.o slstr.o
SRC=slll.c slstr.c
HEADERS=slll.h slstr.h
NAME=libslib

all: $(NAME)

slll.o: slll.c slll.h
	$(CC) $(CFLAGS) $(LIBFLAGS) slll.c -c

slstr.o: slstr.c slstr.h
	$(CC) $(CFLAGS) $(LIBFLAGS) slstr.c -c

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
