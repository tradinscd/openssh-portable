/* $Id: openbsd-compat.h,v 1.9 2001/06/28 23:30:38 mouring Exp $ */

#ifndef _OPENBSD_H
#define _OPENBSD_H

#include "config.h"

/* OpenBSD function replacements */
#include "bindresvport.h"
#include "getcwd.h"
#include "realpath.h"
#include "rresvport.h"
#include "strlcpy.h"
#include "strlcat.h"
#include "strmode.h"
#include "mktemp.h"
#include "daemon.h"
#include "dirname.h"
#include "base64.h"
#include "sigact.h"
#include "inet_aton.h"
#include "inet_ntoa.h"
#include "strsep.h"
#include "vis.h"
#include "setproctitle.h"
#include "getgrouplist.h"
#include "glob.h"
#include "readpassphrase.h"

/* Home grown routines */
#include "bsd-arc4random.h"
#include "bsd-misc.h"
#include "bsd-snprintf.h"
#include "bsd-waitpid.h"

/* rfc2553 socket API replacements */
#include "fake-getaddrinfo.h"
#include "fake-getnameinfo.h"
#include "fake-socket.h"

#endif /* _OPENBSD_H */
