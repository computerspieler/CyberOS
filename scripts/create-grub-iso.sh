#!/bin/bash

if [ $# != 2 ]; then
	echo "ERROR: Not the right amount or arguments"
	echo "./scripts/create-grub-iso.sh <ISO FOLDER> <OUTPUT ISO>"
	exit 1
fi

echo "
menuentry \"CyberOS\" {
	multiboot /kernel.elf
}
" > $1/boot/grub/grub.cfg
grub-mkrescue -o $2 $1