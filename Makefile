TARGET=i686-elf

CC=$(TARGET)-gcc
CCFLAGS=-Wall -Wextra -ffreestanding -fno-exceptions -mgeneral-regs-only -c -Iinclude/

LD=$(TARGET)-gcc
LDFLAGS=-ffreestanding -nostdlib -lgcc

AS=$(TARGET)-as
ASFLAGS=

KERNEL_DEBUG=bin/debug/kernel.bin
KERNELOBJ=start.o main.o

MKDIR=mkdir

clean:
	rm -rf bin

bin:
	$(MKDIR) bin
	$(MKDIR) bin/debug
	$(MKDIR) bin/release
	$(MKDIR) bin/debug/kernel
	$(MKDIR) bin/release/kernel

debug-run: debug
	qemu-system-i386 -m 32M -kernel $(KERNEL_DEBUG) -serial stdio

debug: bin $(KERNEL_DEBUG)

$(KERNEL_DEBUG): $(patsubst %.o,bin/debug/kernel/%.o,$(KERNELOBJ))
	$(LD) $(LDFLAGS) -g -T kernel/linker.ld $^ -o $@

bin/debug/kernel/%.o: kernel/%.c include/*.h
	$(CC) $(CCFLAGS) -g -o $@ $<

bin/debug/kernel/%.o: kernel/%.s
	$(AS) $(ASFLAGS) -g -o $@ $<