#ifndef GAME_H
#define GAME_H

#include "BoardWidget.h"
#include "AI.h"
#include "Board.h"

class Game : public QObject
{
    Q_OBJECT

public:
    Game();

    void start_multiplayer();
    void start_one_player(Difficulty difficulty);

    void board_clicked(Quad quad);

signals:
    void update_msg_label(QString msg);

private:
    AI ai;
    Board board;

    bool turn_x;
    bool active;
    bool one_player;

    void init();
    void turn_cleanup();
    void ai_goes();
    QString get_turn_piece();

};

#endif // GAME_H
