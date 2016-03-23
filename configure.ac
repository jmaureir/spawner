AC_INIT([spawner], [0.1], [jcm@dim.uchile.cl],
             [spawner], [http://tbd.com/])
AC_PREREQ([2.59])
AC_CONFIG_SRCDIR([src/main.cc])
AM_INIT_AUTOMAKE([1.10 -Wall no-define foreign])
AC_CONFIG_HEADERS([config.h])
CFLAGS="${CFLAGS=}"

AC_HEADER_STDC
AC_SUBST(CFLAGS)
AC_SUBST(LDFLAGS)
AC_CHECK_LIB(pthread, pthread_create)
AC_CHECK_HEADERS(getopt.h)

AC_SEARCH_LIBS([clock_gettime],[rt posix4])

AC_CHECK_FUNCS(clock_gettime, [], [
  AC_CHECK_LIB(rt, clock_gettime, [
    AC_DEFINE(HAVE_CLOCK_GETTIME, 1)
    G_THREAD_LIBS="$G_THREAD_LIBS -lrt"
    G_THREAD_LIBS_FOR_GTHREAD="$G_THREAD_LIBS_FOR_GTHREAD -lrt"
  ])
])


AC_PROG_CXX
AC_LANG([C++])
AC_PROG_INSTALL


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
