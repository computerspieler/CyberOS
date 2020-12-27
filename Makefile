include config.Makefile

ifeq ($(TARGET_ARCHITECTURE),x86)
	COMPILER_PREFIX=i686-elf
endif

ifneq ($(findstring debug,$(MAKECMDGOALS)),)
	BUILD_TYPE=debug
else ifneq ($(findstring release,$(MAKECMDGOALS)),)
	BUILD_TYPE=release
else
	BUILD_TYPE=none
endif

ifeq ($(ENABLE_BUILD_NUMBER_SYSTEM),1)
	BUILD_NUMBER=$(words $(wildcard build.$(TARGET_ARCHITECTURE).*) future_binary_folder)
else
	BUILD_NUMBER=0
endif

CC=@$(COMPILER_PREFIX)-gcc
CCFLAGS=-Wall -Wextra -ffreestanding -fno-exceptions -mgeneral-regs-only -c -Iinclude/ -D BUILD_NO=$(BUILD_NUMBER) \
	-finline-functions

LD=@$(COMPILER_PREFIX)-gcc
LDFLAGS=-ffreestanding -nostdlib -lgcc

AS=@$(COMPILER_PREFIX)-as
ASFLAGS=

AR=@$(COMPILER_PREFIX)-ar
ARFLAGS=rcs

ifeq ($(BUILD_TYPE),debug)
	CCFLAGS+=-g -ggdb -O0
	ASFLAGS+=-g -ggdb
	LDFLAGS+=-g
endif

ifeq ($(BUILD_TYPE),release)
	CCFLAGS+=-O2
endif


MKDIR=@mkdir -p
DEL=@rm -rf
ECHO=@echo
COPY=@cp

ifneq ($(BUILD_TYPE),none)
	BINDIR=build.$(TARGET_ARCHITECTURE).$(BUILD_TYPE).$(BUILD_NUMBER)
	ISODIR=$(BINDIR)/iso
	ISONAME=$(BINDIR)/build.$(BUILD_NUMBER).$(BUILD_TYPE).iso

	KERNELOBJ=$(patsubst kernel/%,$(BINDIR)/kernel/%.o, \
		$(wildcard kernel/*.c) $(wildcard kernel/*.s) \
		$(wildcard kernel/arch/$(TARGET_ARCHITECTURE)/*.c) \
		$(wildcard kernel/arch/$(TARGET_ARCHITECTURE)/*.s) \
	)
	LIBOBJ=$(patsubst lib/%,$(BINDIR)/lib/%.o, \
		$(wildcard lib/*.c) \
	)

	ifeq ($(ENABLE_BUILD_NUMBER_SYSTEM),1)
		DEPFILES=
	else
		DEPFILES=$(patsubst %.o,%.d,$(LIBOBJ) $(KERNELOBJ))
	endif
endif

.PHONY: clean

debug: build
debug-run: debug run

release: build
release-run: release run

run: scripts/run-$(TARGET_ARCHITECTURE)-$(EMULATOR).sh
	$(ECHO) RUN
	@./scripts/run-$(TARGET_ARCHITECTURE)-$(EMULATOR).sh $(ISONAME) $(BUILD_TYPE) $(BINDIR)/logs $(BINDIR)

clean:
	$(ECHO) CLEAN binaries folders
	$(DEL) build.$(TARGET_ARCHITECTURE).debug.0
	$(DEL) build.$(TARGET_ARCHITECTURE).release.0

mrproper: clean
	$(ECHO) CLEAN all binaries folders
	$(DEL) build.*

build: $(ISONAME)

$(ISONAME): $(BINDIR) $(BINDIR)/lib.a $(BINDIR)/kernel.elf
	$(ECHO) BUILD disk image
	$(COPY) $(BINDIR)/kernel.elf $(ISODIR)
	$(COPY) $(BINDIR)/lib.a $(ISODIR)
	@./scripts/create-grub-iso.sh $(ISODIR) $(ISONAME)

$(BINDIR):
	$(ECHO) MKDIR build directories: $(BINDIR)
	$(MKDIR) $(BINDIR)/logs
	$(MKDIR) $(BINDIR)/kernel
	$(MKDIR) $(BINDIR)/kernel/arch/$(TARGET_ARCHITECTURE)
	$(MKDIR) $(BINDIR)/lib
	$(MKDIR) $(ISODIR)
	$(MKDIR) $(ISODIR)/boot/grub

$(BINDIR)/kernel.elf: $(KERNELOBJ)
	$(ECHO) LINK $(patsubst $(BINDIR)/%,%,$@)
	$(LD) $(LDFLAGS) -T kernel/linker.ld $^ -o $@

$(BINDIR)/lib.a: CCFLAGS+=-DCOMPILE_LIBC
$(BINDIR)/lib.a: $(LIBOBJ)
	$(ECHO) AR $(patsubst $(BINDIR)/%,%,$@)
	$(AR) $(ARFLAGS) $@ $^


$(BINDIR)/%.s.o: %.s
	$(ECHO) AS $(patsubst $(BINDIR)/%,%,$@)
	$(AS) $(ASFLAGS) -o $@ $<

$(BINDIR)/%.c.o: %.c
	$(ECHO) CC $(patsubst $(BINDIR)/%,%,$@)
	$(CC) $(CCFLAGS) -o $@ $<


$(BINDIR)/%.c.d: %.c $(BINDIR)
	$(CC) $(CCFLAGS) -M -o $@ $< -MT $(patsubst %.c,$(BINDIR)/%.c.o,$<)

-include $(DEPFILES)
