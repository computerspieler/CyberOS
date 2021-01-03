# User defined variables
TARGET_ARCHITECTURE=x86

ENABLE_BUILD_NUMBER_SYSTEM=0
EMULATOR=bochs

MODULES=kernel libs/libc

# Those variables shouldn't be touched unless you know what you're doing
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
	BUILD_NUMBER=$(words $(filter-out $(wildcard *.0), $(wildcard build.$(TARGET_ARCHITECTURE).*)) future_binary_folder)
else
	BUILD_NUMBER=0
endif

CC=@$(COMPILER_PREFIX)-gcc
CCFLAGS=-Wall -Wextra -ffreestanding -fno-exceptions -mgeneral-regs-only -c -D BUILD_NO=$(BUILD_NUMBER) \
	-finline-functions -Iinclude

LD=@$(COMPILER_PREFIX)-gcc
LDFLAGS=-ffreestanding -nostdlib -lgcc

AS=@$(COMPILER_PREFIX)-as
ASFLAGS=

AR=@$(COMPILER_PREFIX)-ar
ARFLAGS=rcs

ifeq ($(BUILD_TYPE),debug)
	CCFLAGS+=-g -ggdb -O0 -DDEBUG_BUILD
	ASFLAGS+=-g -ggdb
	LDFLAGS+=-g -DDEBUG_BUILD
endif

ifeq ($(BUILD_TYPE),release)
	CCFLAGS+=-O2 -DRELEASE_BUILD
endif

MKDIR=@mkdir -p
DEL=@rm -rf
ECHO=@echo
COPY=@cp
