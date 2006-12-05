#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ(2.57)
AC_INIT(pentamino, 0.1.1, [kolen@nm.ru])
AM_INIT_AUTOMAKE(pentamino, 0.1.1)
#AM_CONFIG_SRCDIR([src/Main.cpp])
AM_CONFIG_HEADER(src/config.h)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lSDL':
AC_CHECK_LIB(SDL, SDL_Init, ,AC_MSG_ERROR([libSDL not found! Please install SDL devel package!]))
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB(pthread, pthread_create, ,AC_MSG_ERROR([libpthread not found! Please install pthread devel package!]))
AC_CHECK_LIB(SDL_image, IMG_Load, ,AC_MSG_ERROR([libSDL_Image not found! Please install SDL_Image devel package!]))



# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
#AC_CHECK_FUNCS([atexit])

#AC_CONFIG_FILES([src/Makefile])
AC_OUTPUT(Makefile src/Makefile src/gui/Makefile doc/Makefile img/Makefile maps/Makefile penta.spec)
