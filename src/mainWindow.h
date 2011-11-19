#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMdiSubWindow>
#include <QtGui/QKeyEvent>
#include <QtGui/QToolBar>
#include <QtGui/QActionGroup>

#include "t_libraryeditor.h"

class t_mainWindow : public QMainWindow
{
    Q_OBJECT
    public:
                        t_mainWindow();
    public slots:
        void            openPartEditor(void);
    private:
        QAction         *pEditorAction, *openLibraryAction;
        QMdiArea        *mdiArea;
        QMdiSubWindow   *partEditorWindow;
        t_libraryEditor   *pEditor;
        QToolBar        *toolBar;
        QAction         *moveAction, *lineAction, *pinAction, *infoAction;
        QActionGroup    *actionGroup;
        void            createMenu(void);
        void            testObject(void);
        void            createToolBar(void);
    protected:
        void            keyPressEvent(QKeyEvent *event);
};

#endif
