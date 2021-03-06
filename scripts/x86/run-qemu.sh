#!/bin/bash

if [ $# != 4 ]; then
	echo "ERROR: Not the right amount or arguments"
	echo "./scripts/x86/run-qemu.sh <ISO> <BUILD TYPE> <LOG OUTPUT> <BINARY FOLDER>"
fi

qemu-system-i386 -m 32M -serial stdio -cdrom $1 | tee $3
