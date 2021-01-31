SRCS=$(wildcard src/*)
DEPS=$(patsubst src/%,deps/%.d,$(SRCS))
OBJS=$(patsubst src/%,objs/%.o,$(SRCS))

build: $(OUTDIR)libc.a

include $(BASEDIR)/compile.Makefile