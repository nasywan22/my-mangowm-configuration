#!/usr/bin/env bash

DIMENSION=$(slurp -d)

if [ -z $DIMENSION ]; then
    notify-send "Screenshot cancelled"
    exit 1
fi

grim -g "$DIMENSION" -t jpeg -q 100 $FILE_NAME_PATH
notify-send "Screenshot captured"