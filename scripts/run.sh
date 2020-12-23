#!/bin/bash

if [ $# != 4 ]; then
	echo "ERROR: Not the right amount or arguments"
	echo "./scripts/run.sh <BINARIES FOLDER> <EMULATOR TO USE> <BUILD TYPE> <TARGET ARCHITECTURE>"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "ERROR:" $1 "doesn't exist"
	exit 1
fi

if [ $3 != "debug" -a $3 != "release" ]; then
	echo "ERROR: Invalid build type" $3
	exit 1
fi

if [[ ! -f "scripts/run-"$4"-"$2".sh" ]]; then
	echo "ERROR: Unsupported architecture / emulator combinaison :" $4 "/" $2
	exit 1
fi

./scripts/run-$4-$2.sh $1 $3
