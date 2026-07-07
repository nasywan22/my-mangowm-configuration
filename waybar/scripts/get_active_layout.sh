#!/usr/bin/env bash

# Ambil data semua tag
DATA=$(mmsg get all-tags)

# Ekstrak layout dari tag yang aktif (is_active = true)
LAYOUT=$(echo "$DATA" | jq -r '.all_tags[].tags[] | select(.is_active == true) | .layout' | head -n1)

if [ -z "$LAYOUT" ] || [ "$LAYOUT" = "null" ]; then
    LAYOUT="?"
fi

# Mapping kode layout ke nama yang lebih mudah dibaca (sesuai daftar di wiki)
case "$LAYOUT" in
    "T")   NAME="Tile" ;;
    "S")   NAME="Scroller" ;;
    "G")   NAME="Grid" ;;
    "M")   NAME="Monocle" ;;
    "K")   NAME="Deck" ;;
    "CT")  NAME="Center Tile" ;;
    "VT")  NAME="Vert Tile" ;;
    "RT")  NAME="Right Tile" ;;
    "VS")  NAME="Vert Scroller" ;;
    "VG")  NAME="Vert Grid" ;;
    "VK")  NAME="Vert Deck" ;;
    "DW")  NAME="Dwindle" ;;
    "F")   NAME="Fair" ;;
    "VF")  NAME="Vert Fair" ;;
    *)     NAME="$LAYOUT" ;;  # fallback untuk kode yang belum dikenal
esac

# Kirim output JSON ke Waybar
echo "{\"text\": \"$NAME\", \"alt\": \"$LAYOUT\", \"class\": \"layout-$LAYOUT\"}"