PROGS   = intSort strSort
CC      = gcc
CFLAGS  = -Wall -g
LDFLAGS = -Wall -g

.PHONY: all clean
all: $(PROGS)

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(PROGS) $(OBJECTS)

intSort: intSort_funcs.o intSort_main.o
	$(CC) $(LDFLAGS) $^ -o $@

strSort: strSort_funcs.o strSort_main.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(PROGS)
