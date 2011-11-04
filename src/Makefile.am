bin_PROGRAMS = cooleda
cooleda_SOURCES = \
    main.cpp \
    mainWindow.cpp \
    t_schObject.cpp

t_schObject.cpp:t_schObject.moc
#mainWindow.cpp:mainWindow.moc

t_schObject.moc:
	moc t_schObject.h -o t_schObject.moc

#mainWindow.moc:
#	moc mainWindow.h -o mainWindow.moc

CLEANFILES = *~ *moc

AM_CXXFLAGS = $(QtCore_CFLAGS) $(QtGui_CFLAGS)
AM_LDFLAGS = $(QtCore_LIBS) $(QtGui_LIBS)
