#ifndef GAME_H
#define GAME_H

#include "BoardWidget.h"
#include "AI.h"
#include "Board.h"
#include "Player.h"

enum EndType
{
    END_TYPE_WIN,
    END_TYPE_TIE
};

class Game : public QObject
{
    Q_OBJECT

public:
    Game();

    void startMultiplayer(Player p1, Player p2);
    void startSinglePlayer(Difficulty difficulty);

    void placePiece(Player player, Quad quad);
    void quit(Player player_x);

signals:
    void update_msg_label(QString msg);

    void gameInit(Player p1, Player p2);
    void updatedGameState(Board board);
    void gameEnded(EndType endType, Player winningPlayer);

private:
    AI ai;
    Board board;

    Player playerX;
    Player playerO;

    bool turn_x;
    bool active; // TODO: game state
    bool singlePlayer;

    void init();
    void turn_cleanup();
    void ai_goes();
    QString get_turn_piece();

};

#endif // GAME_H
