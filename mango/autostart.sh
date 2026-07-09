#!/usr/bin/env bash
# LIST OF AUTOSTART APPS

# CACHY UPDATE
cachy-update --tray &
cachy-update --check &

# EASY EFFECT
sleep 1 && /usr/bin/easyeffects --hide-window --service-mode &

# CLOUDFLARE WARP
systemctl --user start warp-taskbar.service
