SRCS=src/arch/$(TARGET_ARCHITECTURE)/start.s \
	 $(wildcard src/*.c) \
	 $(wildcard src/*.s) \
	 $(filter-out src/arch/$(TARGET_ARCHITECTURE)/start.s,$(wildcard src/arch/$(TARGET_ARCHITECTURE)/*.s)) \
	 $(wildcard src/arch/$(TARGET_ARCHITECTURE)/*.c)

LIBDEP=libc

$(OUTDIR)kernel.bin: LDFLAGS+=-T linker.ld
build: $(OUTDIR)kernel.bin

include $(BASEDIR)/compile.Makefile