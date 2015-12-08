CC=gcc
RM=rm -f
LD=ld

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
CFLAGS=

O_TARGET=build.o

.PHONY:$(O_TARGET) clean

obj-y := $(OBJS)

%.o: %.c
ifeq ($(LIB_TYPE), so)
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<
else
	$(CC) $(CFLAGS) -c -o $@ $<
endif

$(O_TARGET): $(obj-y)
	$(RM) $@
	$(LD) $(LDFLAGS) -r -o $@ $^
	$(RM) $^

clean:
	$(RM) $(O_TARGET) $(OBJS)















