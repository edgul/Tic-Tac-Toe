#include "ClientWindow.h"
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

    return a.exec();
}
