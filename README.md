# AWF - A Widget Factory (Extended)

A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme.

Debian package submitted, [rfs for awf-gtk2](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=959897) and [rfs for awf-gtk3](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=959892).

## Installation

It require *GTK 2.24+* or *GTK 3.0+ (including 3.24)* or *GTK 4.0+ (3.98+)*, and *GLIB 2.28+*.

* The *build.sh* script will compile the program with all major GTK version available: `sudo apt install dh-autoreconf libgtk2.0-dev libgtk-3-dev libgtk-4-dev` then: `bash build.sh`

* The *debian-gtkx/deb.sh* script will compile the program and create debian package: `sudo apt install autotools-dev devscripts lintian dh-autoreconf libgtk2.0-dev libgtk-3-dev libgtk-4-dev` then: `bash debian-gtkx/deb.sh`

## Screenshots

* Some options are available from command line (read -h).
* The options menu allow to run some standard dialogs.
* The menu items keyboard shortcut can be updated on hover (GTK 2.24, 3.0-3.24, *gtk-can-change-accels*).
* The plus toolbar button show/hide: arrows on notebooks, text on progress bars and scales, marks on scales.
* The refresh toolbar button and the refresh menuitem allow to reload the current theme.
* Translations: English (en), French (fr).

GTK 2

[![A widget factory - GTK 2 - Main window](images/thumbs/gtk2.png?raw=true)](images/gtk2.png?raw=true)
[![A widget factory - GTK 2 - Test menu](images/thumbs/gtk2-menu.png?raw=true)](images/gtk2-menu.png?raw=true)

GTK 3

[![A widget factory - GTK 3 - Main window](images/thumbs/gtk3.png?raw=true)](images/gtk3.png?raw=true)
[![A widget factory - GTK 3 - Test menu](images/thumbs/gtk3-menu.png?raw=true)](images/gtk3-menu.png?raw=true)

GTK 4

Coming soon.

## SIGHUP

To auto reload theme on files change, you can use [entr](https://github.com/clibs/entr).
```
sudo apt install entr
ls ~/.themes/yourtheme/gtk-3.0/*.css | entr killall -s SIGHUP awf-gtk3
```

## Copyright and Credits

This program is provided under the terms of the *GNU GPLv3* license.

* Updated by Fabrice Creuzot (luigifab)
* Forked from [awf](https://github.com/valr/awf) by Valère Monseur (valr)
* Thanks to Ottoman Kent (for testing in ubuntu and bug report)
* Thanks to Dwight Engen (for rpm specification file: awf.spec.in)
* Thanks to Josef Radinger (for sorted menus, text in progress bars, treeviews with scrollbars)