# Generated automatically from Makefile.in by configure.
prefix=/usr/local
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
sbindir=${exec_prefix}/sbin
libdir=${exec_prefix}/lib

CC=gcc
OPT_FLAGS=-g
CFLAGS=$(OPT_FLAGS) -Wall -DETCDIR=\"${prefix}/etc\" -DHAVE_CONFIG_H
TARGETS=bin/libopenssh.a bin/openssh bin/opensshd bin/openssh-add bin/openssh-keygen bin/openssh-agent bin/openscp
LFLAGS=-L./bin
LIBS=-lopenssh -lpam -ldl -lpwdb -lz -lutil -lcrypto 
AR=ar
RANLIB=ranlib

OBJS=	authfd.o authfile.o auth-passwd.o auth-rhosts.o auth-rh-rsa.o \
		auth-rsa.o bufaux.o buffer.o canohost.o channels.o cipher.o \
		clientloop.o compress.o crc32.o deattack.o helper.o hostfile.o \
		log-client.o login.o log-server.o match.o mpaux.o packet.o pty.o \
		readconf.o readpass.o rsa.o servconf.o serverloop.o \
		sshconnect.o tildexpand.o ttymodes.o uidswap.o xmalloc.o \
		helper.o mktemp.o strlcpy.o rc4.o

all: $(OBJS) $(TARGETS)

bin/libopenssh.a: authfd.o authfile.o bufaux.o buffer.o canohost.o channels.o cipher.o compat.o compress.o crc32.o deattack.o hostfile.o match.o mpaux.o nchan.o packet.o readpass.o rsa.o tildexpand.o ttymodes.o uidswap.o xmalloc.o helper.o rc4.o mktemp.o strlcpy.o
	[ -d bin ] || mkdir bin
	$(AR) rv $@ $^
	$(RANLIB) $@

bin/openssh: ssh.o sshconnect.o log-client.o readconf.o clientloop.o
	[ -d bin ] || mkdir bin
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS) 

bin/opensshd:	sshd.o auth-rhosts.o auth-passwd.o auth-rsa.o auth-rh-rsa.o pty.o log-server.o login.o servconf.o serverloop.o
	[ -d bin ] || mkdir bin
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS) 

bin/openscp:	scp.o
	[ -d bin ] || mkdir bin
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS) 

bin/openssh-add: ssh-add.o log-client.o
	[ -d bin ] || mkdir bin
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS) 

bin/openssh-agent: ssh-agent.o log-client.o
	[ -d bin ] || mkdir bin
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS) 

bin/openssh-keygen: ssh-keygen.o log-client.o
	[ -d bin ] || mkdir bin
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS) 

clean:
	rm -f *.o core bin/* config.status config.cache config.log
	
install:
	install -d $(bindir)
	install -d $(sbindir)
	install -d $(libdir)
	install -c bin/openssh $(bindir)/openssh
	install -c bin/openscp $(bindir)/openscp
	install -c bin/openssh-add $(bindir)/openssh-add
	install -c bin/openssh-agent $(bindir)/openssh-agent
	install -c bin/openssh-keygen $(bindir)/openssh-keygen
	install -c bin/opensshd $(sbindir)/opensshd
	install -c bin/libopenssh.a $(libdir)/libopenssh.a

distclean: clean
	rm -f Makefile config.h *~
	rm -rf bin

mrproper: distclean
