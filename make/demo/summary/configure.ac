#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([summary], [1.0.0], [fgh1987168@gmail.com])
AC_CONFIG_SRCDIR([src/person/main.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE(summary, 1.0.0)
AC_PROG_RANLIB

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 doc/Makefile
                 man/Makefile
                 script/Makefile
                 src/Makefile
                 src/lib/Makefile
                 src/person/Makefile])


AC_OUTPUT
