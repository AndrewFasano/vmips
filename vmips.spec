# vmips RPM spec file.
Name: vmips
Summary: A MIPS-based virtual machine simulator.
Version: 1.1.2
Release: 1
Copyright: GPL
Group: Emulators
URL: http://www.dgate.org/vmips/
Source: ftp://ftp.dgate.org/pub/vmips/snapshots/vmips-1.1.2.tar.gz
Packager: VMIPS Maintainers <vmips@dgate.org>

%description
VMIPS is a software simulator for a virtual machine based
on a MIPS R3000 CPU.  This RPM distribution is targeted for little-endian
MIPS systems using ECOFF binary format.

%prep
%setup
./configure --prefix=/usr --sysconfdir=/etc --target=mipsel-ecoff

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
* Fri Feb 21 2003 VMIPS Maintainers <vmips@dgate.org>
- Add configuration information for mipsel-ecoff.

* Mon Jul 22 2002 VMIPS Maintainers <vmips@dgate.org>
- Update hostnames.

* Sun Jun 17 2001 VMIPS Maintainers <vmips@dgate.org>
- Move vmipsrc to /etc, and make it a config file

* Sun Jun 17 2001 VMIPS Maintainers <vmips@dgate.org>
- Add changelog to RPM spec file.
- Change maintainer address to vmips@dgate.org everywhere.

* Sun Jun 17 2001 VMIPS Maintainers <vmips@dgate.org>
- Add man page to installation.

* Sun Jun 17 2001 VMIPS Maintainers <vmips@dgate.org>
- Get rid of some directories, to quash the "File listed twice" errors from RPM.

* Sat Jun 16 2001 VMIPS Maintainers <vmips@dgate.org>
- Add include/vmips, include/vmips/asm_regnames.h to package.

* Tue Jun 05 2001 VMIPS Maintainers <vmips@dgate.org>
- Add pkgdatadir files to package: ld.script and vmipsrc.

* Mon Jun 04 2001 VMIPS Maintainers <vmips@dgate.org>
- Set prefix to /usr (as with other RPMs.)
- Add "doc" files to %doc line: AUTHORS, COPYING, ChangeLog, INSTALL,
- NEWS, README, THANKS, and VERSION.
- Add vmips.info to package.

* Tue May 29 2001 VMIPS Maintainers <vmips@dgate.org>
- Add vmipstool to package.
- Moved up from package directory to toplevel.

* Tue Aug 15 2000 VMIPS Maintainers <vmips@dgate.org>
- Original RPM spec file for vmips. 
- Needs to be munged with autoconf to contain correct VERSION.

