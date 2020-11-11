#!/bin/bash
# debian: sudo apt install dpkg-dev devscripts build-essential dh-make dh-autoreconf intltool libgtk-4-dev rpm
# fedora: sudo dnf install rpmdevtools rpm-sign autoconf automake gtk4-devel
# fedora: configure: error: C compiler cannot create executables? remove and reinstall glibc-devel gcc

cd "$(dirname "$0")"
version="2.2.0"
gtk="gtk4"

rm -rf builder/ ~/rpmbuild/
mkdir -p builder ~/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}

# copy to a tmp directory
if [ true ]; then
	chmod 644 awf-${gtk}.spec
	spectool -g -R awf-${gtk}.spec
else
	temp=awf-extended-${version}
	mkdir /tmp/${temp}
	cp -r ../* /tmp/${temp}/
	rm -rf /tmp/${temp}/*/builder/

	mv /tmp/${temp} builder/
	cp /usr/share/common-licenses/GPL-3 builder/${temp}/LICENSE

	cd builder/
	tar czf ${temp}.tar.gz ${temp}
	cd ..

	cp builder/${temp}.tar.gz ~/rpmbuild/SOURCES/awf-${gtk}-${version}.tar.gz
	chmod 644 awf-${gtk}.spec
fi

# create package (rpm sign https://access.redhat.com/articles/3359321)
rpmbuild --nodeps -ba awf-${gtk}.spec
rpm --addsign ~/rpmbuild/RPMS/*/*.rpm
rpm --addsign ~/rpmbuild/SRPMS/*.rpm
mv ~/rpmbuild/RPMS/*/*.rpm builder/
mv ~/rpmbuild/SRPMS/*.rpm builder/
echo "==========================="
rpm --checksig builder/*.rpm
echo "==========================="
rpmlint awf-${gtk}.spec builder/*.rpm
echo "==========================="
ls -dltrh $PWD/builder/*.rpm
echo "==========================="

# cleanup
rm -rf builder/*/ ~/rpmbuild/