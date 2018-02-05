# We define symbols:
CC = gcc
CCOPTS = -O3 -Wall
DEPS = db.h

%.o: %.c $(DEPS)
	$(CC) $(CCOPTS) -c -o $@ $<

BINARIES = db.o
ALL = phonebook

# First "non wild card" --> default to execute when typing "make"
all: $(ALL)

clean:
	rm -f $(ALL) $(BINARIES)

phonebook: phonebook.o $(BINARIES)
	$(CC) $(CCOPTS) $^ -o $@
