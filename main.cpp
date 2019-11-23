#include "ClientWindow.h"
#include <QApplication>

#include "MainWindowManager.h"
#include "GameController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameController gameController;

    ClientWindow w;
    w.set_player(true);
    w.show();

    ClientWindow w2;
    w2.set_player(false);
    w2.show();

    // MainWindowManager wm;
    // wm.show();

    return a.exec();
}
