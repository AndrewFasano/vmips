# vmips RPM spec file.
Name: vmips
Summary: A MIPS-based virtual machine simulator.
Version: 1.0
Release: 1
Copyright: GPL
Group: Emulators
URL: http://sartre.dgate.org/vmips/
Source: ftp://sartre.dgate.org/pub/vmips/snapshots/vmips-1.0.tar.gz
Packager: VMIPS Maintainers <vmips@sartre.dgate.org>

%description
VMIPS is a software simulator for a virtual machine based
on a MIPS R3000 CPU.

%prep
%setup
./configure --prefix=/usr --sysconfdir=/etc

%build
make

%install
make install

%files
%doc AUTHORS COPYING ChangeLog INSTALL NEWS README THANKS VERSION
/usr/bin/vmips
/usr/bin/vmipstool
/usr/info/vmips.info
/usr/man/man1/vmips.1
/usr/include/vmips/asm_regnames.h
/usr/share/vmips/ld.script
%config /etc/vmipsrc

%changelog
* Sun Jun 17 2001 VMIPS Maintainers <vmips@sartre.dgate.org>
- Move vmipsrc to /etc, and make it a config file

* Sun Jun 17 2001 VMIPS Maintainers <vmips@sartre.dgate.org>
- Add changelog to RPM spec file.
- Change maintainer address to vmips@sartre.dgate.org everywhere.

* Sun Jun 17 2001 VMIPS Maintainers <vmips@sartre.dgate.org>
- Add man page to installation.

* Sun Jun 17 2001 VMIPS Maintainers <vmips@sartre.dgate.org>
- Get rid of some directories, to quash the "File listed twice" errors from RPM.

* Sat Jun 16 2001 VMIPS Maintainers <vmips@sartre.dgate.org>
- Add include/vmips, include/vmips/asm_regnames.h to package.

* Tue Jun 05 2001 VMIPS Maintainers <vmips@sartre.dgate.org>
- Add pkgdatadir files to package: ld.script and vmipsrc.

* Mon Jun 04 2001 VMIPS Maintainers <vmips@sartre.dgate.org>
- Set prefix to /usr (as with other RPMs.)
- Add "doc" files to %doc line: AUTHORS, COPYING, ChangeLog, INSTALL,
- NEWS, README, THANKS, and VERSION.
- Add vmips.info to package.

* Tue May 29 2001 VMIPS Maintainers <vmips@sartre.dgate.org>
- Add vmipstool to package.
- Moved up from package directory to toplevel.

* Tue Aug 15 2000 VMIPS Maintainers <vmips@sartre.dgate.org>
- Original RPM spec file for vmips. 
- Needs to be munged with autoconf to contain correct VERSION.
