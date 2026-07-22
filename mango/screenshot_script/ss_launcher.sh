#!/usr/bin/env bash

export FILE_NAME_PATH="/home/gallahard/Gambar/Screenshots/$(date +'%d%m%Y%H%M').jpg"

MODES='fullscreen\nregion'
CHOOSED_MODE=$(printf $MODES | rofi -dmenu)

case $CHOOSED_MODE in
  "fullscreen"  )   /home/gallahard/.config/mango/screenshot_script/fullscreen-ss.sh  ;;
  "region"      )   /home/gallahard/.config/mango/screenshot_script/region-ss.sh      ;;
esac

echo "path  :   $FILE_NAME_PATH"

OPTIONS_AFTER_SS='save\ncopy'
CHOOSED_OPTION=$(printf $OPTIONS_AFTER_SS | rofi -dmenu)

case $CHOOSED_OPTION in
  "save"  )   notify-send "file saved at $FILE_NAME_PATH";;

  "copy")
    wl-copy <"$FILE_NAME_PATH"
    sleep 2.5s
    rm -f "$FILE_NAME_PATH"
    notify-send "file copied"
    ;;
esac
