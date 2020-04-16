#!/bin/bash

cd "$(dirname "$0")"
if ! ./awf-gtk4 "$@"
then
    zenity --error --icon-name=awf --window-icon=awf --text="GTK 4 is not available."
fi