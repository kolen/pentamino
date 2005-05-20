SUBDIRS = gui

AM_CPPFLAGS = -DDATADIR=\"$(datadir)/$(PACKAGE_NAME)-$(PACKAGE_VERSION)/\" @CPPFLAGS@

bin_PROGRAMS = pentamino

pentamino_SOURCES = \
	Main.cpp \
	Main.h \
	Shell.cpp \
	Shell.h \
	Sprite.cpp \
	Sprite.h \
	SDLInterface.h \
	SDLInterface.cpp \
	GameField.cpp \
	GameField.h \
	Shape.cpp \
	Shape.h \
	shapes.cpp \
	File.cpp \
	File.h \
	Service.h \
	I18n.cpp \
	I18n.h

pentamino_LDADD = gui/libgui.a

#
#
# $Log: Makefile.am,v $
# Revision 1.3  2005/05/20 12:52:15  kolen
# New I18n class
#
# Revision 1.2  2005/05/20 11:28:11  kolen
# Directory search from autoconf.
# Fixed missing files in "make install"
# Added install
#
#
