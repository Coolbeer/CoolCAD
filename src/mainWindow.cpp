#include "mainWindow.moc"

#include <QtGui/QMenuBar>
#include <QtCore/QResource>

#include <iostream>

t_mainWindow::t_mainWindow(void)
{
	mdiArea = new QMdiArea;
	setCentralWidget(mdiArea);

	createMenu();
	createToolBar();
	QResource::registerResource("resource.rcc");
//	mdiArea->setViewMode(QMdiArea::TabbedView); //Enable this when we have more than one window
}

void t_mainWindow::createMenu(void)
{
	QMenuBar *menuB = new QMenuBar;
	QMenu *toolsMenu;
	toolsMenu = menuB->addMenu("Tools");
	pEditorAction = toolsMenu->addAction("Part Editor");
	setMenuBar(menuB);

	connect(pEditorAction, SIGNAL(triggered()), this, SLOT(openPartEditor()));
}

void t_mainWindow::createToolBar(void)
{
	actionGroup = new QActionGroup(this);
	toolBar = new QToolBar;
	toolBar->setMovable(false);

	moveAction = new QAction(QIcon(":/images/arrows.png"), "Move", this);
	lineAction = new QAction(QIcon(":/images/line.png"), "Draw Line", this);
	moveAction->setCheckable(true);
	lineAction->setCheckable(true);
	actionGroup->addAction(moveAction);
	actionGroup->addAction(lineAction);
	toolBar->addActions(actionGroup->actions());
	moveAction->setChecked(true);
	addToolBar(Qt::LeftToolBarArea, toolBar);
}

void t_mainWindow::openPartEditor(void)
{
	pEditor = new t_partEditor2;
	partEditorWindow = mdiArea->addSubWindow(pEditor, Qt::Window);
	partEditorWindow->showMaximized();
}

void t_mainWindow::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	switch(key)
	{
		case Qt::Key_Escape:
			pEditor->cancel();
			break;
		default:
			break;
	}
}

