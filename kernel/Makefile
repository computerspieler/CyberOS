SRCS=arch/$(TARGET_ARCHITECTURE)/start.s \
	 $(wildcard *.c) \
	 $(wildcard *.s) \
	 $(filter-out arch/$(TARGET_ARCHITECTURE)/start.s,$(wildcard arch/$(TARGET_ARCHITECTURE)/*.s)) \
	 $(wildcard arch/$(TARGET_ARCHITECTURE)/*.c)

LIBDEP=libc

$(OUTDIR)kernel.bin: CCFLAGS+=-Iarch/$(TARGET_ARCHITECTURE)
$(OUTDIR)kernel.bin: LDFLAGS+=-T linker.ld
build: $(OUTDIR)kernel.bin

include $(BASEDIR)/compile.Makefile