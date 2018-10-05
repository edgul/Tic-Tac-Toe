#include "ClientWindow.h"
#include <QApplication>

#include "MyTCPServer.h"
#include "MainWindowManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyTCPServer tcp_server;

    ClientWindow w;
    w.set_player(true);
    w.show();

    ClientWindow w2;
    w.set_player(false);
    w2.show();

    // MainWindowManager wm;
    // wm.show();

    return a.exec();
}
