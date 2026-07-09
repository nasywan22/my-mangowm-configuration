#!/usr/bin/env bash

BLUETOOTH_STATE=$(bluetoothctl show E8:FB:1C:72:2B:24 | grep -Fi "powered:" | cut -d ":" -f 2)

if [ $BLUETOOTH_STATE -a $BLUETOOTH_STATE = "yes" ]; then
    echo "turn off the bluetooth"
    bluetoothctl power off
else
    echo "turn on the bluetooth"
    bluetoothctl power on
fi