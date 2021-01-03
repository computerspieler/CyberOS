#!/bin/bash

if [ $# != 2 ]; then
	echo "ERROR: Not the right amount or arguments"
	echo "./scripts/create-grub-iso.sh <ISO FOLDER> <OUTPUT ISO>"
	exit 1
fi

mkdir -p $1/boot/grub/

# Create the config file
echo "set timeout=0
menuentry \"CyberOS\" {
	multiboot /kernel.bin" > $1/boot/grub/grub.cfg

for module_folder in $1/core $1/drivers; do
	for module in $module_folder/*; do
		[[ "${module//$module_folder\//}" == "*" ]] && continue
		echo "	module /${module//$1\//}" >> $1/boot/grub/grub.cfg
	done
done

echo "}" >> $1/boot/grub/grub.cfg

grub-mkrescue -o $2 $1 2> /dev/null