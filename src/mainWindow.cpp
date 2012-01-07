#include "mainWindow.moc"

#include <QtGui/QMenuBar>
#include <QtCore/QResource>
#include <QtGui/QDockWidget>

#include <iostream>

t_mainWindow::t_mainWindow(void)
{
    mdiArea = new QMdiArea;
    setCentralWidget(mdiArea);
    pEditor = new t_libraryEditor;

    createDock();
    createMenu();
    createToolBar();
    QResource::registerResource("resource.rcc");
//  mdiArea->setViewMode(QMdiArea::TabbedView); //Enable this when we have more than one window

    connect(pEditorAction, SIGNAL(triggered()), this, SLOT(openPartEditor()));
    connect(openLibraryAction, SIGNAL(triggered()), this, SLOT(openLibraryEditor()));
    connect(actionGroup, SIGNAL(triggered(QAction*)), pEditor, SLOT(buttonClicked(QAction*)));
    connect(partListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(itemListSelected()));
}

void t_mainWindow::createMenu(void)
{
    QMenuBar *menuB = new QMenuBar;
    QMenu *fileMenu;
    QMenu *newMenu;
    QMenu *openMenu;
    QMenu *viewMenu;
    fileMenu = menuB->addMenu("&File");
    newMenu = fileMenu->addMenu("&New");
    openMenu = fileMenu->addMenu("&Open");
    pEditorAction = newMenu->addAction("&Library");
    openLibraryAction = openMenu->addAction("&Library");
    viewMenu = menuB->addMenu("&View");
    viewMenu->addAction(dock->toggleViewAction());
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

void t_mainWindow::createDock(void)
{
    dock = new QDockWidget("Items in Library", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    partListWidget = new QListWidget(dock);
    dock->setWidget(partListWidget);
    dock->hide();
    addDockWidget(Qt::RightDockWidgetArea, dock);
}

void t_mainWindow::openPartEditor(void)
{
    partEditorWindow = mdiArea->addSubWindow(pEditor);
    partEditorWindow->showMaximized();
}

void t_mainWindow::openLibraryEditor(void)
{
    partEditorWindow = mdiArea->addSubWindow(pEditor);
    partEditorWindow->showMaximized();
    pEditor->openLib();
    dock->show();
    partListWidget->clear();
    for(uint16_t i = 0; i != pEditor->library->components.size(); ++i)
    {
        new QListWidgetItem(QString::fromStdString(pEditor->library->components.at(i)->name), partListWidget);
    }
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

void t_mainWindow::itemListSelected(void)
{
    std::string tmpStr = partListWidget->currentItem()->text().toStdString();
    for(uint16_t i = 0; i != partListWidget->count(); ++i)
    {
        if(tmpStr == pEditor->library->components.at(i)->name)
        {
            pEditor->currentComponent = pEditor->library->components.at(i);
            pEditor->haveComp = true;
        }
    }
}
