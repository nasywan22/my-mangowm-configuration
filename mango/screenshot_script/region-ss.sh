#!/usr/bin/env bash

DIMENSION=$(slurp -d)

if [ -z $DIMENSION ]; then
    notify-send "Screenshot cancelled"
    exit 1
fi

grim -g "$DIMENSION" $FILE_NAME_PATH
notify-send "Screenshot captured"