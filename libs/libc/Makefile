SRCS=$(wildcard *.c)
DEPS=$(patsubst %.c,deps/%.d,$(SRCS))
OBJS=$(patsubst %.c,objs/%.o,$(SRCS))

build: $(OUTDIR)libc.a

include $(BASEDIR)/compile.Makefile