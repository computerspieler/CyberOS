#!/bin/bash

if [ $2 = "debug" ]; then
	qemu-system-i386 -m 32M -kernel $1/kernel.bin -serial stdio -s -S &
	gdb << EOF
	file $1/kernel.bin
	target remote localhost:1234
	continue
EOF
elif [ $2 = "release" ]; then
	qemu-system-i386 -m 32M -kernel $1/kernel.bin -serial stdio
fi