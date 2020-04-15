#!/bin/bash

cd "$(dirname "$0")"
if ! ./awf-gtk3
then
    zenity --error --icon-name=awf --window-icon=awf --text="GTK 3 is not available."
fi