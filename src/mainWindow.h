#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsView>

class t_mainWindow : public QMainWindow
{
    public:
                        t_mainWindow();
    private:
        QGraphicsView   *mainWidget;
        QGraphicsScene  *mainScene;
		QAction			*pEditor;
		void			createMenu(void);
};

#endif
