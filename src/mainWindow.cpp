#include "mainWindow.moc"

#include <QtGui/QMenuBar>
#include <QtCore/QResource>

#include <iostream>

t_mainWindow::t_mainWindow(void)
{
	mdiArea = new QMdiArea;
	setCentralWidget(mdiArea);
	pEditor = new t_partEditor2;

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

	infoAction = new QAction(QIcon(":/images/info.png"), "Info", this);
	infoAction->setCheckable(true);
	actionGroup->addAction(infoAction);

	moveAction = new QAction(QIcon(":/images/arrows.png"), "Move", this);
	moveAction->setCheckable(true);
	actionGroup->addAction(moveAction);

	lineAction = new QAction(QIcon(":/images/line.png"), "Draw Line", this);
	lineAction->setCheckable(true);
	actionGroup->addAction(lineAction);

	pinAction = new QAction(QIcon(":/images/pin.png"), "Draw a Pin", this);
	pinAction->setCheckable(true);
	actionGroup->addAction(pinAction);

	toolBar->addActions(actionGroup->actions());
	moveAction->setChecked(true);
	pEditor->setToolBarButton(MOVE);
	addToolBar(Qt::LeftToolBarArea, toolBar);

	connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(updateEditor(QAction*)));
}

void t_mainWindow::openPartEditor(void)
{
	partEditorWindow = mdiArea->addSubWindow(pEditor, Qt::Window);
	partEditorWindow->showMaximized();
}

void t_mainWindow::updateEditor(QAction *act)
{
	if(act->text() == "Move")
		pEditor->setToolBarButton(MOVE);
	else if(act->text() == "Draw Line")
		pEditor->setToolBarButton(LINE);
	else if(act->text() == "Draw a Pin")
		pEditor->setToolBarButton(PIN);
	else if(act->text() == "Info")
		pEditor->setToolBarButton(INFO);
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

