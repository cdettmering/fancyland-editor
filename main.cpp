#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("FancyLand");
    QCoreApplication::setOrganizationName("ShmoopaLoop Productions");
    MainWindow w;
    w.show();
    
    return a.exec();
}
