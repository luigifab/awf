#!/bin/bash

cd "$(dirname "$0")"
if ! ./awf-gtk2
then
    zenity --error --icon-name=awf --window-icon=awf --text="GTK 2 is not available."
fi