#include "mainWindow.h"
#include "t_schObject.h"

t_mainWindow::t_mainWindow(void)
{
    t_schObject testObj;
    mainWidget = new QGraphicsView;
    mainScene = new QGraphicsScene;
    setCentralWidget(mainWidget);
    mainScene->addItem(&testObj);
    mainWidget->setScene(mainScene);
}