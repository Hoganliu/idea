CC=gcc
RM=rm -f

CFLAGS=-Wall -O -g

TARGET=sudoku
SOURCES=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SOURCES))


$(TARGET):$(OBJS)
	$(CC) -o $@ $^

..c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o *~
