bin_PROGRAMS = cooleda
cooleda_SOURCES = \
	main.cpp \
	mainWindow.cpp \
	pwanmath.cpp \
	t_schObject.cpp \
	t_libraryeditor.cpp \
	t_symbol.cpp \
	t_infoWindow.cpp

mainWindow.moc:mainWindow.h
mainWindow.cpp:mainWindow.moc

t_schObject.moc:t_schObject.h
t_schObject.cpp:t_schObject.moc

t_libraryeditor.moc:t_libraryeditor.h
t_libraryeditor.cpp:t_libraryeditor.moc


.h.moc:
	moc $< -o$@

CLEANFILES = *~ *moc

AM_CXXFLAGS = $(QtCore_CFLAGS) $(QtGui_CFLAGS) -Wall -Wextra -pedantic -std=c++0x
AM_LDFLAGS = $(QtCore_LIBS) $(QtGui_LIBS)
