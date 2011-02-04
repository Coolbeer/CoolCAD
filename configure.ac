AC_INIT([cooleda], [0.0], [hightower@tregt.net])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_PROG_CXX

PKG_CHECK_MODULES([QtCore], [QtCore >= 4.6.3])
AC_SUBST(QtCore_CFLAGS)
AC_SUBST(QtCore_LIBS)

PKG_CHECK_MODULES(QtGui, QtGui >= 4.6.3)
AC_SUBST(QtGui_CFLAGS)
AC_SUBST(QtGui_LIBS)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
