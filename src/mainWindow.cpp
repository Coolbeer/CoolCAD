#include "mainWindow.h"
#include "t_schObject.h"
#include <QtGui/QMenuBar>
#include <QtGui/QMdiArea>


t_mainWindow::t_mainWindow(void)
{
	QMdiArea *mdiArea = new QMdiArea;

    t_schObject *testObj = new t_schObject;
    mainWidget = new QGraphicsView;
    mainScene = new QGraphicsScene;
	setCentralWidget(mdiArea);
	mdiArea->addSubWindow(mainWidget);

	mainScene->addItem(testObj);
    mainWidget->setScene(mainScene);

	createMenu();
}

void t_mainWindow::createMenu(void)
{
	QMenuBar *menuB = new QMenuBar;
	QMenu *toolsMenu;
	toolsMenu = menuB->addMenu("Tools");
	pEditor = toolsMenu->addAction("Part Editor");
	setMenuBar(menuB);
}
