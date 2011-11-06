bin_PROGRAMS = cooleda
cooleda_SOURCES = \
	main.cpp \
	mainWindow.cpp \
	t_schObject.cpp \
	parteditor.cpp \
	parteditor2.cpp \
	t_symbol.cpp

mainWindow.moc:mainWindow.h
mainWindow.cpp:mainWindow.moc

t_schObject.moc:t_schObject.h
t_schObject.cpp:t_schObject.moc

parteditor.moc:parteditor.h
parteditor.cpp:parteditor.moc

parteditor2.moc:parteditor2.h
parteditor2.cpp:parteditor2.moc


.h.moc:
	moc $< -o$@

CLEANFILES = *~ *moc

AM_CXXFLAGS = $(QtCore_CFLAGS) $(QtGui_CFLAGS) -Wall -Wextra -pedantic -std=c++0x
AM_LDFLAGS = $(QtCore_LIBS) $(QtGui_LIBS)
