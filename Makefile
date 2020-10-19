TARGET=i686-elf

CC=$(TARGET)-gcc
CCFLAGS=-Wall -Wextra -ffreestanding -fno-exceptions -mgeneral-regs-only -c -Iinclude/

LD=$(TARGET)-gcc
LDFLAGS=-ffreestanding -nostdlib -lgcc

AS=$(TARGET)-as
ASFLAGS=

AR=$(TARGET)-ar
ARFLAGS=rcs

LIB_DEBUG=bin/debug/lib.a

KERNEL_DEBUG=bin/debug/kernel.bin
KERNELOBJ=start.o main.o serial.o asm.o

LIBOBJ=math.o

MKDIR=mkdir

clean:
	rm -rf bin

bin:
	$(MKDIR) bin
	$(MKDIR) bin/debug
	$(MKDIR) bin/release
	$(MKDIR) bin/debug/kernel
	$(MKDIR) bin/release/kernel
	$(MKDIR) bin/debug/lib
	$(MKDIR) bin/release/lib

debug-run: debug
	qemu-system-i386 -m 32M -kernel $(KERNEL_DEBUG) -serial stdio

debug: bin $(LIB_DEBUG) $(KERNEL_DEBUG)

$(KERNEL_DEBUG): $(patsubst %.o,bin/debug/kernel/%.o,$(KERNELOBJ)) $(LIB_DEBUG)
	$(LD) $(LDFLAGS) -g -T kernel/linker.ld $^ -o $@

bin/debug/kernel/%.o: kernel/%.c include/*.h include/kernel/*.h
	$(CC) $(CCFLAGS) -g -o $@ $<

bin/debug/kernel/%.o: kernel/%.s
	$(AS) $(ASFLAGS) -g -o $@ $<


$(LIB_DEBUG): $(patsubst %.o,bin/debug/lib/%.o,$(LIBOBJ))
	$(AR) $(ARFLAGS) $@ $^

bin/debug/lib/%.o: lib/%.c include/*.h
	$(CC) $(CCFLAGS) -g -o $@ $<