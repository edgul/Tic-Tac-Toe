#ifndef GAME_H
#define GAME_H

#include "AI.h"
#include "Board.h"
#include "Player.h"


class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    bool isSinglePlayer();
    void startMultiplayer(Player p1, Player p2);
    void startSinglePlayer(Difficulty difficulty);

    bool getActive();
    void placePiece(Player player, Quad quad);
    void checkForGameOver();
    void quit(Player player_x);

    Player getPlayer1();
    Player getPlayer2();
    Player currentTurnPlayer();

    void ai_goes();

signals:
    void update_msg_label(QString msg);

    void gameInit(Player p1, Player p2);
    void gameStateUpdated(Player p1, Player p2, Board board);
    void gameEnded(Player winningPlayer);

private:
    AI ai;
    Board board;

    Player playerX;
    Player playerO;

    bool turn_x;
    bool active_;
    bool singlePlayer;

    void init();
    QString get_turn_piece();

};

#endif // GAME_H
