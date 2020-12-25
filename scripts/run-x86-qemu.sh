#!/bin/bash

if [ $# != 4 ]; then
	echo "ERROR: Not the right amount or arguments"
	echo "./scripts/run-x86-qemu.sh <ISO> <BUILD TYPE> <LOG FOLDER> <BINARY FOLDER>"
fi

qemu-system-i386 -m 32M -serial $3/serial.txt -cdrom $1