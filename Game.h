#ifndef GAME_H
#define GAME_H

#include "data/BoardModel.h"
#include "data/Player.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    void startMultiplayer(Player p1, Player p2);

    bool getActive();
    void placePiece(Player player, Quad quad);
    void checkForGameOver();
    void quit(Player player_x);

    Player getPlayer1();
    Player getPlayer2();
    Player currentTurnPlayer();

signals:
    void update_msg_label(QString msg);

    void gameInit(Player p1, Player p2);
    void gameStateUpdated(Player p1, Player p2, BoardModel board);
    void gameEnded(Player winningPlayer);

private:
    BoardModel board;

    Player playerX;
    Player playerO;

    bool turn_x;
    bool active_;
    bool singlePlayer;

    void init();
    QString get_turn_piece();

};

#endif // GAME_H
