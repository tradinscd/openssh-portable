/* config.h.in.  Generated by hand, don't use autoheader.  */

/* SSL directory.  */
#undef ssldir

/* Location of lastlog file */
#undef LASTLOG_LOCATION

/* If lastlog is a directory */
#undef LASTLOG_IS_DIR

/* Location of random number pool  */
#undef RANDOM_POOL

/* Are we using the Entropy gathering daemon */
#undef HAVE_EGD

/* Define if your ssl headers are included with #include <ssl/header.h>  */
#undef HAVE_SSL

/* Define if your ssl headers are included with #include <openssl/header.h>  */
#undef HAVE_OPENSSL

/* Define is utmp.h has a ut_host field */
#undef HAVE_HOST_IN_UTMP

/* Define is libutil has login() function */
#undef HAVE_LIBUTIL_LOGIN

/* Define if you want external askpass support */
#undef USE_EXTERNAL_ASKPASS

/* Define if libc defines __progname */
#undef HAVE___PROGNAME

/* Define if you want Kerberos 4 support */
#undef KRB4

/* Define if you want AFS support */
#undef AFS

/* Define if you want S/Key support */
#undef SKEY

/* Define if you want TCP Wrappers support */
#undef LIBWRAP

/* Define if your libraries define login() */
#undef HAVE_LOGIN

/* Define if your libraries define daemon() */
#undef HAVE_DAEMON

/* Define if you want to allow MD5 passwords */
#undef HAVE_MD5_PASSWORDS

/* Data types */
#undef HAVE_QUAD_T
#undef HAVE_INTXX_T
#undef HAVE_U_INTXX_T
#undef HAVE_UINTXX_T

@BOTTOM@

/* ******************* Shouldn't need to edit below this line ************** */

# include <sys/types.h> /* For u_intXX_t */
# include <sys/socket.h> /* For SHUT_XXXX */

#ifdef HAVE_PATHS_H
# include <paths.h> /* For _PATH_XXX */
#endif 

#ifndef SHUT_RDWR
enum
{
  SHUT_RD = 0,    /* No more receptions.  */
#define SHUT_RD   SHUT_RD
  SHUT_WR,    /* No more transmissions.  */
#define SHUT_WR   SHUT_WR
  SHUT_RDWR   /* No more receptions or transmissions.  */
#define SHUT_RDWR SHUT_RDWR
};
#endif

/* If sys/types.h does not supply intXX_t, supply them ourselves */
/* (or die trying) */
#ifndef HAVE_INTXX_T
# if (SIZEOF_SHORT_INT == 2)
#  define int16_t short int
# else
#  error "16 bit int type not found."
# endif
# if (SIZEOF_INT == 4)
#  define int32_t int
# else
#  error "32 bit int type not found."
# endif
# if (SIZEOF_LONG_INT == 8)
#  define int64_t long int
# else
#  if (SIZEOF_LONG_LONG_INT == 8)
#   define int64_t long long int
#  else
#   error "64 bit int type not found."
#  endif
# endif
#endif

/* If sys/types.h does not supply u_intXX_t, supply them ourselves */
#ifndef HAVE_U_INTXX_T
# ifdef HAVE_UINTXX_T
#  define u_int16_t uint16_t
#  define u_int32_t uint32_t
#  define u_int64_t uint64_t
# else
#  if (SIZEOF_SHORT_INT == 2)
#   define u_int16_t unsigned short int
#  else
#   error "16 bit int type not found."
#  endif
#  if (SIZEOF_INT == 4)
#   define u_int32_t unsigned int
#  else
#   error "32 bit int type not found."
#  endif
#  if (SIZEOF_LONG_INT == 8)
#   define u_int64_t unsigned long int
#  else
#   if (SIZEOF_LONG_LONG_INT == 8)
#    define u_int64_t unsigned long long int
#   else
#    error "64 bit int type not found."
#   endif
#  endif
# endif
#endif

/* If quad_t is not supplied, then supply it now. We can rely on int64_t */
/* being defined by the above */
#ifndef HAVE_QUAD_T
# define quad_t int64_t
#endif

#ifndef _PATH_LASTLOG
# ifdef LASTLOG_LOCATION
#  define _PATH_LASTLOG LASTLOG_LOCATION
# endif
#endif

#ifndef _PATH_UTMP
# ifdef UTMP_FILE
#  define _PATH_UTMP UTMP_FILE
# endif
#endif

#ifndef _PATH_WTMP
# ifdef WTMP_FILE
#  define _PATH_WTMP WTMP_FILE
# endif
#endif

#ifndef _PATH_BSHELL
# define _PATH_BSHELL "/bin/sh"
#endif

#ifndef _PATH_STDPATH
# define _PATH_STDPATH "/usr/bin:/bin:/usr/sbin:/sbin:"
#endif

#ifndef _PATH_MAILDIR
# ifdef MAILDIR
#  define _PATH_MAILDIR MAILDIR
# endif
#endif

#ifndef MAX
# define MAX(a,b) (((a)>(b))?(a):(b))
# define MIN(a,b) (((a)<(b))?(a):(b))
#endif
