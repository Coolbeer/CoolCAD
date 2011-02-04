#include <QtGui/QApplication>
#include <QtGui/QMainWindow>

int main(int argc, char **argv)
{
    QApplication *qAp(new QApplication(argc,argv));
    QMainWindow *mainWindow(new QMainWindow);
    mainWindow->show();
    return qAp->exec();
}
