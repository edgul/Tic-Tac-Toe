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

    void set_board(BoardWidget * board_w);

    void start_multiplayer();
    void start_one_player(Difficulty difficulty);

signals:
    void update_msg_label(QString msg);

private slots:
    void board_clicked(Quad quad);

private:

    AI ai;
    Board board;

    BoardWidget * board_widget;

    bool turn_x;
    bool active;

    bool one_player;

    void init();

    void turn_cleanup();
    void ai_goes();

    QString get_turn_piece();

};

#endif // GAME_H
