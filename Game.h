#ifndef GAME_H
#define GAME_H

#include "data/BoardModel.h"
#include "data/Player.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    void start(Player pX, Player pO);

    bool getActive();
    void placePiece(Cell cell);
    void checkForGameOver();
    void quit(PieceType quittingPiece);

    Player getPlayerX();
    Player getPlayerO();

    PieceType currentTurnPiece();

signals:
    void update_msg_label(QString msg);

    void gameInit(Player p1, Player p2);
    void gameStateUpdated(Player p1, Player p2, BoardModel board);
    void gameEnded(Player winningPlayer);

private:
    BoardModel board;

    Player playerX;
    Player playerO;

    PieceType turnPiece_;
    PieceType winner_;

    void init();
    Player winnerPlayer();

};

#endif // GAME_H
