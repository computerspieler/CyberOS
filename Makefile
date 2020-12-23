include config.Makefile

ifeq ($(TARGET_ARCHITECTURE),x86)
	COMPILER_PREFIX=i686-elf
endif

ifeq ($(ENABLE_BUILD_NUMBER_SYSTEM),1)
	BUILD_NUMBER=$(words $(wildcard binaries.$(TARGET_ARCHITECTURE).*) future_binary_folder)
else
	BUILD_NUMBER=0
endif

CC=@$(COMPILER_PREFIX)-gcc
CCFLAGS=-Wall -Wextra -ffreestanding -fno-exceptions -mgeneral-regs-only -c -Iinclude/ -D BUILD_NO=$(BUILD_NUMBER)

LD=@$(COMPILER_PREFIX)-gcc
LDFLAGS=-ffreestanding -nostdlib -lgcc

AS=@$(COMPILER_PREFIX)-as
ASFLAGS=

AR=@$(COMPILER_PREFIX)-ar
ARFLAGS=rcs

MKDIR=@mkdir -p
DEL=@rm -rf
ECHO=@echo

ifneq ($(findstring debug,$(MAKECMDGOALS)),)
	BUILD_TYPE=debug
endif

ifneq ($(findstring release,$(MAKECMDGOALS)),)
	BUILD_TYPE=release
endif

BINDIR=binaries.$(TARGET_ARCHITECTURE).$(BUILD_TYPE).$(BUILD_NUMBER)

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
	DEPFILES=$(patsubst %.o,$(BINDIR)/kernel/%.d,$(KERNELOBJ)) \
		$(patsubst %.o,$(BINDIR)/lib/%.d,$(LIBOBJ))
endif

ifeq ($(BUILD_TYPE),debug)
	CCFLAGS+=-g -ggdb -O0
	ASFLAGS+=-g -ggdb
	LDFLAGS+=-g
endif

ifeq ($(BUILD_TYPE),release)
	CCFLAGS+=-O2
endif

debug-run: build-img
	$(ECHO) RUN
	@./scripts/run.sh $(BINDIR) $(EMULATOR) $(BUILD_TYPE) $(TARGET_ARCHITECTURE)

release-run: build-img
	$(ECHO) RUN
	@./scripts/run.sh $(BINDIR) $(EMULATOR) $(BUILD_TYPE) $(TARGET_ARCHITECTURE)

clean:
	$(ECHO) CLEAN binaries folders
	$(DEL) binaries.*

build-img: $(BINDIR) $(BINDIR)/lib.a $(BINDIR)/kernel.bin

$(BINDIR):
	$(ECHO) MKDIR build directories: $(BINDIR)
	$(MKDIR) $(BINDIR)/boot/grub
	$(MKDIR) $(BINDIR)/kernel
	$(MKDIR) $(BINDIR)/kernel/arch/$(TARGET_ARCHITECTURE)
	$(MKDIR) $(BINDIR)/lib

$(BINDIR)/kernel.bin: $(KERNELOBJ) $(BINDIR)/lib.a
	$(ECHO) LINK $(patsubst $(BINDIR)/%,%,$@)
	$(LD) $(LDFLAGS) -T kernel/linker.ld $^ -o $@

$(BINDIR)/lib.a: $(LIBOBJ)
	$(ECHO) AR $(patsubst $(BINDIR)/%,%,$@)
	$(AR) $(ARFLAGS) $@ $^


$(BINDIR)/%.s.o: %.s
	$(ECHO) AS $(patsubst $(BINDIR)/%,%,$@)
	$(AS) $(ASFLAGS) -o $@ $<

$(BINDIR)/%.c.o: %.c
	$(ECHO) CC $(patsubst $(BINDIR)/%,%,$@)
	$(CC) $(CCFLAGS) -o $@ $<


$(BINDIR)/%.d: %.c $(BINDIR)
	$(CC) $(CCFLAGS) -M -o $@ $< -MT $(patsubst %.c,$(BINDIR)/%.o,$<)

-include $(DEPFILES)