# AWF - A widget factory (extended)

A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme.

Debian and Fedora packages submitted: [awf-gtk2.deb](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=959897), [awf-gtk3.deb](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=959892), [awf-gtk2.rpm](https://bugzilla.redhat.com/show_bug.cgi?id=1893321), [awf-gtk3.rpm](https://bugzilla.redhat.com/show_bug.cgi?id=1893323). Ubuntu: [PPA](https://launchpad.net/~luigifab/+archive/ubuntu/packages).

## Installation

It require *GTK 2.24+* or *GTK 3.0+ (including 3.24)* or *GTK 4.0+ (3.99+)*, and *GLIB 2.28+*.

* The *build.sh* script will compile the program with all major GTK versions available: `sudo apt install build-essential dh-autoreconf intltool libgtk2.0-dev libgtk-3-dev libgtk-4-dev` or `sudo dnf install autoconf automake gtk2-devel gtk3-devel gtk4-devel` then: `bash build.sh`

* The *debian-gtkx/deb.sh* scripts will compile the program and create debian packages: `sudo apt install dpkg-dev devscripts build-essential dh-make dh-autoreconf intltool libgtk2.0-dev libgtk-3-dev libgtk-4-dev` then: `bash debian-gtkx/deb.sh`

* The *bash fedora-gtkx/rpm.sh* scripts will compile the program and create fedora packages: `sudo dnf install rpmdevtools rpm-sign autoconf automake gtk2-devel gtk3-devel gtk4-devel` then: `bash fedora-gtkx/rpm.sh`

* Debian and Ubuntu: `sudo apt install awf-gtk2 awf-gtk3` (coming soon, or via PPA)

* Fedora: `sudo dnf install awf-gtk2 awf-gtk3` (coming soon)

## Screenshots and Features

* Some options are available from command line (read -h).
* The options menu allow to run some standard dialogs.
* The plus toolbar button show/hide: arrows on notebooks, text on progress bars and scales, marks on scales.
* The refresh toolbar button and the refresh menu item allow to reload the current theme (like the sighup signal).
* The menu items keyboard shortcut can be updated on hover (GTK 2.24 and 3.0-3.24, *gtk-can-change-accels*).
* For Ubuntu, the menu items keyboard shortcut can be updated on hover with: `export UBUNTU_MENUPROXY= && awf-gtk3`

GTK 2

[![A widget factory - GTK 2 - Main window](images/thumbs/gtk2.png?raw=true)](images/gtk2.png?raw=true)
[![A widget factory - GTK 2 - Test menu](images/thumbs/gtk2-menu.png?raw=true)](images/gtk2-menu.png?raw=true)

GTK 3

[![A widget factory - GTK 3 - Main window](images/thumbs/gtk3.png?raw=true)](images/gtk3.png?raw=true)
[![A widget factory - GTK 3 - Test menu](images/thumbs/gtk3-menu.png?raw=true)](images/gtk3-menu.png?raw=true)

GTK 4

[![A widget factory - GTK 4 - Main window](images/thumbs/gtk4.png?raw=true)](images/gtk4.png?raw=true)
[![A widget factory - GTK 4 - Test menu](images/thumbs/gtk4-menu.png?raw=true)](images/gtk4-menu.png?raw=true)

The theme used for the screenshots is available [here](https://github.com/luigifab/human-theme).

## Dev

To reload theme on files change, you can use [Entr](https://github.com/clibs/entr) and the *sighup* signal.
```
sudo apt install entr  or  sudo dnf install entr
ls ~/.themes/yourtheme/gtk-3.0/*.css | entr killall -s SIGHUP awf-gtk3
```

## Copyright and Credits

- Current version: 2.2.0 (11/11/2020)
- Compatibility: GTK 2.24 / 3.0 / 3.2 / 3.4 / 3.6 / 3.8 / 3.10 / 3.12 / 3.14 / 3.16 / 3.18 / 3.20 / 3.22 / 3.24
- Translations: English (en), French (fr)

This program is provided under the terms of the *GNU GPLv3+* license.

* Updated by Fabrice Creuzot (luigifab)
* Forked from [awf](https://github.com/valr/awf) by Valère Monseur (valr)
* Thanks to Ottoman Kent (for testing in ubuntu and bug report)
* Thanks to Dwight Engen (for rpm specification file: awf.spec.in)
* Thanks to Josef Radinger (for sorted menus, text in progress bars, treeviews with scrollbars)
