# © Richard Kettewell. See README.md for more info.
AC_PREREQ([2.61])
AC_INIT([rot13], [0], [rjk@greenend.org.uk])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_AUX_DIR([config.aux])
AM_INIT_AUTOMAKE([foreign])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AC_CONFIG_SRCDIR([rot13.c])
AM_CONFIG_HEADER([config.h])
AC_LANG([C])
AC_PROG_CC
AC_SET_MAKE
AC_DEFINE([_GNU_SOURCE], [1], [use GNU extensions])
if test "x$GCC" = xyes; then
  CFLAGS="$CFLAGS -Wall -W -Werror -Wpointer-arith -Wwrite-strings"
fi
AH_BOTTOM([#ifdef __GNUC__
# define attribute(x) __attribute__(x)
#else
# define attribute(x)
#endif])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
