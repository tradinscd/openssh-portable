/* config.h.in.  Generated by hand, don't use autoheader.  */

/* SSL directory.  */
#undef ssldir

/* Random number pool  */
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


/* Shouldn't need to edit below this line *************************** */
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
