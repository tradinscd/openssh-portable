Summary: OpenSSH free Secure Shell (SSH) implementation
Name: openssh
Version: 1.2.1pre20
Release: 1
Packager: Damien Miller <djm@ibs.com.au>
Source0: openssh-%{version}.tar.gz
Copyright: BSD
Group: Applications/Internet
BuildRoot: /tmp/openssh-%{version}-buildroot
Obsoletes: ssh
Requires: openssl >= 0.9.4
PreReq: openssl >= 0.9.4
BuildPreReq: openssl >= 0.9.4
BuildPreReq: openssl-devel >= 0.9.4
BuildPreReq: tcp_wrappers
BuildPreReq: gnome-libs

%package clients
Summary: OpenSSH Secure Shell protocol clients
Requires: openssh
Group: System Environment/Daemons
Obsoletes: ssh-clients

%package server
Summary: OpenSSH Secure Shell protocol server (sshd)
Requires: openssh chkconfig >= 0.9
Group: System Environment/Daemons
Obsoletes: ssh-server

%package askpass
Summary: OpenSSH GNOME passphrase dialog
Group: Applications/Internet
Requires: openssh
Obsoletes: ssh-extras
Obsoletes: ssh-askpass

%description
Ssh (Secure Shell) a program for logging into a remote machine and for
executing commands in a remote machine.  It is intended to replace
rlogin and rsh, and provide secure encrypted communications between
two untrusted hosts over an insecure network.  X11 connections and
arbitrary TCP/IP ports can also be forwarded over the secure channel.

OpenSSH is OpenBSD's rework of the last free version of SSH, bringing it
up to date in terms of security and features, as well as removing all 
patented algorithms to seperate libraries (OpenSSL).

This package includes the core files necessary for both the OpenSSH
client and server.  To make this package useful, you should also
install openssh-clients, openssh-server, or both.

%description clients
Ssh (Secure Shell) a program for logging into a remote machine and for
executing commands in a remote machine.  It is intended to replace
rlogin and rsh, and provide secure encrypted communications between
two untrusted hosts over an insecure network.  X11 connections and
arbitrary TCP/IP ports can also be forwarded over the secure channel.

OpenSSH is OpenBSD's rework of the last free version of SSH, bringing it
up to date in terms of security and features, as well as removing all 
patented algorithms to seperate libraries (OpenSSL).

This package includes the clients necessary to make encrypted connections
to SSH servers.

%description server
Ssh (Secure Shell) a program for logging into a remote machine and for
executing commands in a remote machine.  It is intended to replace
rlogin and rsh, and provide secure encrypted communications between
two untrusted hosts over an insecure network.  X11 connections and
arbitrary TCP/IP ports can also be forwarded over the secure channel.

OpenSSH is OpenBSD's rework of the last free version of SSH, bringing it
up to date in terms of security and features, as well as removing all 
patented algorithms to seperate libraries (OpenSSL).

This package contains the secure shell daemon. The sshd is the server 
part of the secure shell protocol and allows ssh clients to connect to 
your host.

%description askpass
Ssh (Secure Shell) a program for logging into a remote machine and for
executing commands in a remote machine.  It is intended to replace
rlogin and rsh, and provide secure encrypted communications between
two untrusted hosts over an insecure network.  X11 connections and
arbitrary TCP/IP ports can also be forwarded over the secure channel.

OpenSSH is OpenBSD's rework of the last free version of SSH, bringing it
up to date in terms of security and features, as well as removing all 
patented algorithms to seperate libraries (OpenSSL).

This package contains the GNOME passphrase dialog.

%changelog
* Mon Nov 15 1999 Damien Miller <djm@mindrot.org>
- Split subpackages further based on patch from jim knoble <jmknoble@pobox.com>
* Sat Nov 13 1999 Damien Miller <djm@mindrot.org>
- Added 'Obsoletes' directives
* Tue Nov 09 1999 Damien Miller <djm@ibs.com.au>
- Use make install
- Subpackages
* Mon Nov 08 1999 Damien Miller <djm@ibs.com.au>
- Added links for slogin
- Fixed perms on manpages
* Sat Oct 30 1999 Damien Miller <djm@ibs.com.au>
- Renamed init script
* Fri Oct 29 1999 Damien Miller <djm@ibs.com.au>
- Back to old binary names
* Thu Oct 28 1999 Damien Miller <djm@ibs.com.au>
- Use autoconf
- New binary names
* Wed Oct 27 1999 Damien Miller <djm@ibs.com.au>
- Initial RPMification, based on Jan "Yenya" Kasprzak's <kas@fi.muni.cz> spec.

%prep

%setup -q

%build

CFLAGS="$RPM_OPT_FLAGS" \
	./configure --prefix=/usr --sysconfdir=/etc/ssh \
                    --with-gnome-askpass --with-tcp-wrappers

make

%install
rm -rf $RPM_BUILD_ROOT
make install prefix="$RPM_BUILD_ROOT/usr"

install -d $RPM_BUILD_ROOT/etc/ssh
install -d $RPM_BUILD_ROOT/etc/pam.d/
install -d $RPM_BUILD_ROOT/etc/rc.d/init.d
install -m644 packages/redhat/sshd.pam $RPM_BUILD_ROOT/etc/pam.d/sshd
install -m755 packages/redhat/sshd.init $RPM_BUILD_ROOT/etc/rc.d/init.d/sshd
install -m600 ssh_config $RPM_BUILD_ROOT/etc/ssh/ssh_config
install -m600 sshd_config $RPM_BUILD_ROOT/etc/ssh/sshd_config

%clean
rm -rf $RPM_BUILD_ROOT

%post server
/sbin/chkconfig --add sshd
if [ ! -f /etc/ssh/ssh_host_key -o ! -s /etc/ssh/ssh_host_key ]; then
	/usr/bin/ssh-keygen -b 1024 -f /etc/ssh/ssh_host_key -N '' >&2
fi
if test -r /var/run/sshd.pid
then
	/etc/rc.d/init.d/sshd restart >&2
fi

%preun server
if [ "$1" = 0 ]
then
	/etc/rc.d/init.d/sshd stop >&2
	/sbin/chkconfig --del sshd
fi

%files
%defattr(-,root,root)
%doc ChangeLog OVERVIEW COPYING.Ylonen README README.Ylonen INSTALL UPGRADING
%attr(0755,root,root) /usr/bin/ssh-keygen
%attr(0755,root,root) /usr/bin/scp
%attr(0644,root,root) /usr/man/man1/ssh-keygen.1
%attr(0644,root,root) /usr/man/man1/scp.1
%attr(0755,root,root) %dir /etc/ssh

%files clients
%defattr(-,root,root)
%attr(4755,root,root) /usr/bin/ssh
%attr(0755,root,root) /usr/bin/ssh-agent
%attr(0755,root,root) /usr/bin/ssh-add
%attr(0644,root,root) /usr/man/man1/ssh.1
%attr(0644,root,root) /usr/man/man1/ssh-agent.1
%attr(0644,root,root) /usr/man/man1/ssh-add.1
%attr(0644,root,root) %config(noreplace) /etc/ssh/ssh_config
%attr(-,root,root) /usr/bin/slogin
%attr(-,root,root) /usr/man/man1/slogin.1

%files server
%defattr(-,root,root)
%attr(0755,root,root) /usr/sbin/sshd
%attr(0644,root,root) /usr/man/man8/sshd.8
%attr(0600,root,root) %config(noreplace) /etc/ssh/sshd_config
%attr(0600,root,root) %config(noreplace) /etc/pam.d/sshd
%attr(0755,root,root) %config /etc/rc.d/init.d/sshd

%files askpass
%defattr(-,root,root)
%attr(0755,root,root) /usr/libexec/ssh/ssh-askpass
%attr(0755,root,root) %dir /usr/libexec/ssh

