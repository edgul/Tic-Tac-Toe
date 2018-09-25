#include "MainWindow.h"
#include <QApplication>

#include "MyTCPServer.h"
#include "MainWindowManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyTCPServer tcp_server;

    MainWindow w;
    w.show();

    MainWindow w2;
    w2.show();

    MainWindowManager wm;
    wm.show();

    return a.exec();
}
