#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "MyTCPServer.h"
#include "Game.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController();

private slots:
    void onReceivedData(QString data);

private:
    MyTCPServer tcp_server;
    Game game;
};

#endif // GAMECONTROLLER_H
