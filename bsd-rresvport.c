/*
 * Copyright (c) 1995, 1996, 1998 Theo de Raadt.  All rights reserved.
 * Copyright (c) 1983, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 *	This product includes software developed by Theo de Raadt.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "config.h"

#ifndef HAVE_RRESVPORT_AF

#if defined(LIBC_SCCS) && !defined(lint)
static char *rcsid = "$OpenBSD: rresvport.c,v 1.4 1999/12/17 20:48:03 deraadt Exp $";
#endif /* LIBC_SCCS and not lint */

#include "includes.h"

#if 0
int
rresvport(alport)
	int *alport;
{
	return rresvport_af(alport, AF_INET);
}
#endif

int
rresvport_af(alport, af)
	int *alport;
	int af;
{
	struct sockaddr_storage ss;
	struct sockaddr *sa;
	u_int16_t *portp;
	int s;
	int salen;

	bzero(&ss, sizeof ss);
	sa = (struct sockaddr *)&ss;

	switch (af) {
	case AF_INET:
		salen = sizeof(struct sockaddr_in);
		portp = &((struct sockaddr_in *)sa)->sin_port;
		break;
	case AF_INET6:
		salen = sizeof(struct sockaddr_in6);
		portp = &((struct sockaddr_in6 *)sa)->sin6_port;
		break;
	default:
		errno = EPFNOSUPPORT;
		return (-1);
	}
	sa->sa_family = af;
	
	s = socket(af, SOCK_STREAM, 0);
	if (s < 0)
		return (-1);

	*portp = htons(*alport);
	if (*alport < IPPORT_RESERVED - 1) {
		if (bind(s, sa, salen) >= 0)
			return (s);
		if (errno != EADDRINUSE) {
			(void)close(s);
			return (-1);
		}
	}

	*portp = 0;
	if (bindresvport_af(s, sa, af) == -1) {
		(void)close(s);
		return (-1);
	}
	*alport = ntohs(*portp);
	return (s);
}

#endif /* HAVE_RRESVPORT_AF */
