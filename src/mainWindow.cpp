#include "mainWindow.h"
#include "t_schObject.h"
#include <QtGui/QMenuBar>
#include <QtGui/QMdiArea>


t_mainWindow::t_mainWindow(void)
{
	QAction *pEditor;
	QMenu *toolsMenu;
	QMdiArea *mdiArea = new QMdiArea;
	QMenuBar *menuB = new QMenuBar;
	toolsMenu = menuB->addMenu("Tools");
	pEditor = toolsMenu->addAction("Part Editor");

    t_schObject *testObj = new t_schObject;
    mainWidget = new QGraphicsView;
    mainScene = new QGraphicsScene;
	setCentralWidget(mdiArea);
	mdiArea->addSubWindow(mainWidget);

	mainScene->addItem(testObj);
    mainWidget->setScene(mainScene);
	this->setMenuBar(menuB);
}