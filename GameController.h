#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "MyTCPServer.h"
#include "Game.h"
#include "data/Player.h"
#include "data/Message.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController();

private slots:
    void onReceivedData(QString data, int user);

    void onGameInit(Player p1, Player p2);
    void onGameStateUpdated(Player p1, Player p2, BoardModel board);
    void onGameEnded(Player winningPlayer);
    void onUserDisconnected(int user);

private:
    MyTCPServer tcp_server;
    Game game;
    QString messageStream;
    QList<Player> players;

    void processMessage(QString messageStr, int user);
    void handleGameMessage(Message msg, int user);
};

#endif // GAMECONTROLLER_H
