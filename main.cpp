#include "ClientWindow.h"
#include <QApplication>

#include "MainWindowManager.h"
#include "GameController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameController gameController;

    ClientWindow w;
    w.show();
    ClientWindow w2;
    w2.show();

    // MainWindowManager wm;
    // wm.show();

    return a.exec();
}
