#!/bin/bash

gtk="gtk3"
version="2.1.0"
cd debian-${gtk}/
rm -rf builder/

# copy to a tmp directory
mkdir builder
mkdir builder/awf-${gtk}-${version}
touch builder/awf-${gtk}-${version}/NEWS
touch builder/awf-${gtk}-${version}/AUTHORS
touch builder/awf-${gtk}-${version}/README
touch builder/awf-${gtk}-${version}/ChangeLog
cp -r ../icons              builder/awf-${gtk}-${version}/
cp -r ../src                builder/awf-${gtk}-${version}/
cp awf-${gtk}.desktop       builder/awf-${gtk}-${version}/
cp ../Makefile.am           builder/awf-${gtk}-${version}/
cp ../configure.ac          builder/awf-${gtk}-${version}/
cp /usr/share/common-licenses/GPL-3 builder/awf-${gtk}-${version}/COPYING
sed -i 's/ -eq 2/ -eq -1/g' builder/awf-${gtk}-${version}/configure.ac
sed -i 's/ -eq 4/ -eq -1/g' builder/awf-${gtk}-${version}/configure.ac
for file in builder/awf-${gtk}-${version}/icons/*/*/*; do mv $file ${file/\/awf./\/awf-${gtk}.}; done
for file in builder/awf-${gtk}-${version}/src/po/*.po; do
	lang=$(basename "$file" .po)
	mkdir -p builder/awf-${gtk}-${version}/locale/${lang}/LC_MESSAGES
	msgfmt   builder/awf-${gtk}-${version}/src/po/${lang}.po -o builder/awf-${gtk}-${version}/locale/${lang}/LC_MESSAGES/awf-${gtk}.mo
done

cd builder/
tar czf awf-${gtk}-${version}.tar.gz awf-${gtk}-${version}/
cd ..

# create package
cd builder/awf-${gtk}-${version}/
dh_make -s -y -f ../awf-${gtk}-${version}.tar.gz
rm -f debian/*ex debian/*EX debian/README* debian/*doc*
mkdir debian/upstream
cp ../../control   debian/
cp ../../changelog debian/
cp ../../copyright debian/
cp ../../install   debian/
cp ../../watch     debian/
cp ../../rules     debian/
cp ../../lintian   debian/awf-${gtk}.lintian-overrides
cp ../../upstream  debian/upstream/metadata
dpkg-buildpackage -us -uc
cd ..
debsign awf-${gtk}_${version}-*.changes
cd ..

# cleanup
rm -rf builder/awf-${gtk}-${version}/ builder/awf-${gtk}-${version}.tar.gz