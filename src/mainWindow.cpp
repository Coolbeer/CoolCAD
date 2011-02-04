#include "mainWindow.h"

t_mainWindow::t_mainWindow(void)
{
    mainWidget = new QGraphicsView;

    setCentralWidget(mainWidget);
}