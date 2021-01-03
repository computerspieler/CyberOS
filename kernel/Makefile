SRCS=$(wildcard src/*)
DEPS=$(patsubst src/%,deps/%.d,$(SRCS))
OBJS=$(patsubst src/%,objs/%.o,$(SRCS))

$(OUTDIR)kernel.bin: LDFLAGS+=-T linker.ld
build: $(OUTDIR)kernel.bin

CONFIG_MAKEFILE=../config.Makefile
include ../compile.Makefile