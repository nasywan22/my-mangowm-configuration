#!/usr/bin/env bash

LAYOUT_LIST_PATH="/home/gallahard/.config/mango/layout_switcher_script/layout-list.txt"
PARAMETER="Find Layout"

LAYOUT_CHOICE=$(rofi -dmenu -input $LAYOUT_LIST_PATH -p $PARAMETER)

mmsg dispatch setlayout,$LAYOUT_CHOICE
pkill -SIGRTMIN+8 waybar