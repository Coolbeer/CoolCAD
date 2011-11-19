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
//  mdiArea->setViewMode(QMdiArea::TabbedView); //Enable this when we have more than one window

    connect(pEditorAction, SIGNAL(triggered()), this, SLOT(openPartEditor()));
    connect(actionGroup, SIGNAL(triggered(QAction*)), pEditor, SLOT(buttonClicked(QAction*)));
}

void t_mainWindow::createMenu(void)
{
    QMenuBar *menuB = new QMenuBar;
    QMenu *fileMenu;
    QMenu *newMenu;
    QMenu *openMenu;
    fileMenu = menuB->addMenu("&File");
    newMenu = fileMenu->addMenu("&New");
    openMenu = fileMenu->addMenu("&Open");
    pEditorAction = newMenu->addAction("&Library");
    openLibraryAction = openMenu->addAction("&Library");

    setMenuBar(menuB);
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
    addToolBar(Qt::LeftToolBarArea, toolBar);
}

void t_mainWindow::openPartEditor(void)
{
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

