#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "MyTCPServer.h"
#include "Game.h"
#include "Player.h"
#include "Message.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController();

private slots:
    void onReceivedData(QString data, int user);

    void onGameEnded(EndType endType, Player winningPlayer);

private:
    MyTCPServer tcp_server;
    Game game;
    QString messageStream;

    void processMessage(QString messageStr, int user);

    QList<Player> players;

    void handleConnectionMessage(Message msg);
    void handleGameMessage(Message msg, int user);
};

#endif // GAMECONTROLLER_H
