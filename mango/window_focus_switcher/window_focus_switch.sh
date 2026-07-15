#!/usr/bin/env bash

WINDOW_ID=$(./get_all_windows | rofi -dmenu -p "find window" | grep -oE '^[0-9]+')

mmsg dispatch focusid client,$WINDOW_ID