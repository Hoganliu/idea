CC=gcc
RM=rm -f
AR=ar

SO_TARGET=libcrypto2.so
L_TARGET=libcrypto2.a

subdir-y += des/


obj-y += $(addsuffix build.o, $(subdir-y))


define make_subdir
	@for subdir in $(subdir-y) ; do\
		$(MAKE) -C $$subdir $1;\
	done;
endef

.PHONY:all subdirs_so subdirs_a test

all:$(SO_TARGET) $(L_TARGET) test

$(SO_TARGET):subdirs_so
	$(RM) $@
	$(CC) -shared -o $@ $(obj-y)

$(L_TARGET): subdirs_a
	$(RM) $@
	$(AR) rcs $@ $(obj-y)

subdirs_so:
	$(call make_subdir, LIB_TYPE=so)

subdirs_a:
	$(call make_subdir, LIB_TYPE=a)
	
clean:
	$(call make_subdir, clean)
	$(RM) $(SO_TARGET) $(L_TARGET) test

test:
	$(CC) -o test test.c -static -L. -lcrypto2


