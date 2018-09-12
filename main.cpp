#include "MainWindow.h"
#include <QApplication>

#include "MyTCPServer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyTCPServer tcp_server;

    MainWindow w;
    w.show();

    return a.exec();
}
