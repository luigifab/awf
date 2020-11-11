Name:        awf-gtk2
Version:     2.2.0
Release:     1%{?dist}
Summary:     Theme preview application for GTK
Summary(fr): Application d'aperçu de thème pour GTK
License:     GPLv3+
URL:         https://github.com/luigifab/awf-extended
Source0:     %{url}/archive/v%{version}/%{name}-%{version}.tar.gz

BuildRequires: gtk2-devel
BuildRequires: gettext
BuildRequires: gcc
BuildRequires: autoconf
BuildRequires: automake
BuildRequires: desktop-file-utils
BuildRequires: hunspell-fr
Requires: gtk2
Requires: hicolor-icon-theme

%description %{expand:
A widget factory is a theme preview application for GTK. It displays the
various widget types provided by GTK in a single window allowing to see
the visual effect of the applied theme.

This package provides the gtk2 version.}

%description -l fr %{expand:
La fabrique à widgets est une application d'aperçu de thème pour GTK. Elle
affiche les différents types de widgets fournis par GTK dans une seule
fenêtre permettant de voir l'effet visuel du thème appliqué.

Ce paquet fournit la version gtk2.}


%prep
%setup -q -n awf-extended-%{version}
%autosetup -n awf-extended-%{version}
sed -i 's/ -eq 3/ -eq -1/g' configure.ac
sed -i 's/ -eq 4/ -eq -1/g' configure.ac
touch {NEWS,AUTHORS,README,ChangeLog}
mv LICENSE COPYING

%build
autoreconf -f -i
%configure
%make_build

%install
%make_install
mkdir -p %{buildroot}%{_datadir}/applications/
mkdir -p %{buildroot}%{_datadir}/icons/hicolor/
for file in icons/*/*/*; do mv $file ${file/\/awf./\/%{name}.}; done
cp -a icons/* %{buildroot}%{_datadir}/icons/hicolor/
for file in src/po/*.po; do
  code=$(basename "$file" .po)
  mkdir -p %{buildroot}%{_datadir}/locale/${code}/LC_MESSAGES/
  msgfmt src/po/${code}.po -o %{buildroot}%{_datadir}/locale/${code}/LC_MESSAGES/%{name}.mo
done
desktop-file-install --dir=%{buildroot}%{_datadir}/applications/ applications/%{name}.desktop
%find_lang %{name}

%files -f %{name}.lang
%license COPYING
%doc README.md
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
%{_datadir}/icons/hicolor/scalable/apps/%{name}.svg


%changelog
* Wed Nov 11 2020 Fabrice Creuzot <code@luigifab.fr> - 2.2.0-1
- Initial fedora package release (Closes: #1893321)
