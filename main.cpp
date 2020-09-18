#include <QApplication>

// #include "MainWindowManager.h"
#include "GameController.h"

#include "ClientMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameController gameController;

    ClientMainWindow cmw;
    cmw.show();

    ClientMainWindow cmw2;
    cmw2.show();

    return a.exec();
}
