CC=cc
CFLAGS=-Wall
LIBFLAGS=-fPIC
OBJ=slll.o slstr.o
SRC=slll.c slstr.c
HEADERS=slll.h slstr.h
NAME=libslib

all: $(NAME)

$(OBJ): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) -shared $(OBJ) -o $@.so

install: $(NAME)
	cp -f $(HEADERS) /usr/local/include
	cp -f $(NAME).so /usr/local/lib

uninstall:
	for h in $(HEADERS); do \
		rm -f /usr/local/include/$$h ; \
	done
	rm -f /usr/local/lib/$(NAME).so

clean:
	rm -f *.o
	rm -f *.so
