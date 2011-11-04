#include "mainWindow.h"
#include "t_schObject.h"
#include <QtGui\QMenuBar>

t_mainWindow::t_mainWindow(void)
{
	QMenu *toolsMenu;
	QMenuBar *menuB = new QMenuBar;
	toolsMenu = menuB->addMenu("Tools");
	toolsMenu->addAction("Part Editor");


    t_schObject *testObj = new t_schObject;
    mainWidget = new QGraphicsView;
    mainScene = new QGraphicsScene;
    setCentralWidget(mainWidget);

	mainScene->addItem(testObj);
    mainWidget->setScene(mainScene);
	this->setMenuBar(menuB);
}