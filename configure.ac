#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.69)
AC_INIT(hdbench, 0.20)
AC_CONFIG_SRCDIR(src/hdbench.c)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS(config.h)

# Checks for programs.
AC_PROG_MAKE_SET
AC_PROG_CC
AM_PROG_CC_STDC
AC_PROG_INSTALL

# Checks for libraries.
AM_PATH_GTK_2_0([2.10.0],,AC_MSG_ERROR([Gtk+ 2.10.0 or higher required.]))
AC_SEARCH_LIBS(XClearWindow, X11)

# Checks for header files.
AC_PATH_X
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([fcntl.h libintl.h limits.h stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_FORK
AC_CHECK_FUNCS([alarm gettimeofday memset strchr strstr strtol strtoul])

AC_CONFIG_FILES([Makefile
                 doc/Makefile
                 src/Makefile])
AC_OUTPUT
