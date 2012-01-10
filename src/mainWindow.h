#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMdiSubWindow>
#include <QtGui/QKeyEvent>
#include <QtGui/QToolBar>
#include <QtGui/QActionGroup>
#include <QtGui/QListWidget>
#include <QtGui/QScrollArea>

#include "t_libraryeditor.h"

class t_mainWindow : public QMainWindow
{
    Q_OBJECT
    public:
                        t_mainWindow();
    public slots:
        void            openPartEditor(void);
        void            openLibraryEditor(void);
        void            itemListSelected(void);
    private:
        QAction         *pEditorAction, *openLibraryAction;
        QMdiArea        *mdiArea;
        QMdiSubWindow   *partEditorWindow;
        QScrollArea     *sArea;
        t_libraryEditor  *pEditor;
        QToolBar        *toolBar;
        QAction         *moveAction, *lineAction, *pinAction, *infoAction;
        QActionGroup    *actionGroup;
        QListWidget     *partListWidget;
        QDockWidget     *dock;
        void            createMenu(void);
        void            testObject(void);
        void            createToolBar(void);
        void            createDock(void);
    protected:
        void            keyPressEvent(QKeyEvent *event);
};

#endif
