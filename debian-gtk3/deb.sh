#!/bin/bash

gtk="gtk3"
version="2.0.0"
cd debian-${gtk}/
rm -rf *.deb builder/*/*

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
cp ../LICENSE               builder/awf-${gtk}-${version}/COPYING
sed -i 's/ -eq 2/ -eq -1/g' builder/awf-${gtk}-${version}/configure.ac
sed -i 's/ -eq 4/ -eq -1/g' builder/awf-${gtk}-${version}/configure.ac
for file in builder/awf-${gtk}-${version}/icons/*/*/*; do mv $file ${file/\/awf./\/awf-${gtk}.}; done

cd builder/
tar czf awf-${gtk}-${version}.tar.gz awf-${gtk}-${version}/
cd ..

# create package
cd builder/awf-${gtk}-${version}/
dh_make -s -y -f ../awf-${gtk}-${version}.tar.gz
rm -f debian/*ex debian/*EX debian/README* debian/*doc*
cp ../../control   debian/control
cp ../../changelog debian/changelog
cp ../../copyright debian/
cp ../../rules     debian/
cp ../../install   debian/install
cp ../../lintian   debian/awf-${gtk}.lintian-overrides
dpkg-buildpackage -us -uc
cd ..
debsign awf-${gtk}_${version}-1_amd64.changes
cd ..

# cleanup
rm -rf builder/awf-${gtk}-${version}/ builder/awf-${gtk}-${version}.tar.gz
rm builder/*dbg*