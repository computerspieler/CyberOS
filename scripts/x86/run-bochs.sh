#!/bin/bash

if [ $# != 4 ]; then
	echo "ERROR: Not the right amount or arguments"
	echo "./scripts/x86/run-bochs.sh <ISO> <BUILD TYPE> <LOG OUTPUT> <BINARY FOLDER>"
fi

CONFIG_FILE="$4/bochsrc"
DEBUG_MODE=0
[ $2 = "debug" ]; DEBUG_MODE=1

# Uncomment the line below if you want to use Bochs' GUI debugger
# GUI_DEBUGGER=", options=\"gui_debug\""

if [[ ! -f $CONFIG_FILE ]]; then
	sed "s@<LOGOUT>@$3@g; s@<ISO>@$1@g; s@<DEBUG_MODE>@$DEBUG_MODE@g; s@<GUI_DEBUGGER>@$GUI_DEBUGGER@g" bochsrc.template > $CONFIG_FILE
fi

rm -rf $3
bochs -f $CONFIG_FILE -q
rm -f bx_enh_dbg.ini