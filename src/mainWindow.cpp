#include "mainWindow.h"
#include "t_schObject.h"
#include <QtGui\QMenuBar>

t_mainWindow::t_mainWindow(void)
{
	QMenuBar *menuB = new QMenuBar;
	menuB->addAction("test");

    t_schObject *testObj = new t_schObject;
    mainWidget = new QGraphicsView;
    mainScene = new QGraphicsScene;
    setCentralWidget(mainWidget);

	mainScene->addItem(testObj);
    mainWidget->setScene(mainScene);
	this->setMenuBar(menuB);
}