#ifndef GAME_H
#define GAME_H

#include "BoardWidget.h"
#include "AI.h"
#include "Board.h"
#include "Player.h"


class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    void startMultiplayer(Player p1, Player p2);
    void startSinglePlayer(Difficulty difficulty);

    bool getActive();
    void placePiece(Player player, Quad quad);
    void checkForGameOver();
    void quit(Player player_x);

    Player getPlayer1();
    Player getPlayer2();

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
    bool active_;        // TODO: game state
    bool singlePlayer;  // TODO: fix single player

    void init();
    void ai_goes();
    QString get_turn_piece();

};

#endif // GAME_H
