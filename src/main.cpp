#include <QtGui/QApplication>

#include "mainWindow.h"

int main(int argc, char **argv)
{
    QApplication *qAp(new QApplication(argc,argv));
    t_mainWindow mainWindow;
    mainWindow.show();
    return qAp->exec();
}
