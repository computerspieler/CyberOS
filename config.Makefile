# User defined variables
EMULATOR=bochs

TARGET_ARCHITECTURE=x86
TARGET_MACHINE=generic
IMAGE_FS=fat12

# Those variables shouldn't be touched unless you know what you're doing
MODULES=kernel $(wildcard libs/*)

ifeq ($(TARGET_ARCHITECTURE),x86)
	COMPILER_PREFIX=i686-elf-
endif

ifneq ($(findstring debug,$(MAKECMDGOALS)),)
	BUILD_TYPE=debug
else ifneq ($(findstring release,$(MAKECMDGOALS)),)
	BUILD_TYPE=release
else
	BUILD_TYPE=none
endif

CC=@$(COMPILER_PREFIX)gcc
CCFLAGS=-Wall -Wextra -ffreestanding -fno-exceptions -mgeneral-regs-only -c \
	-finline-functions

LD=@$(COMPILER_PREFIX)gcc
ALTLD=@$(COMPILER_PREFIX)ld
LDFLAGS=-ffreestanding -nostdlib -lgcc

AS=@$(COMPILER_PREFIX)as
ASFLAGS=

AR=@$(COMPILER_PREFIX)ar
ARFLAGS=rcs

ifeq ($(BUILD_TYPE),debug)
	CCFLAGS+=-g -ggdb -DDEBUG_BUILD
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
