#ifndef GAME_H
#define GAME_H

#include "BoardWidget.h"
#include "AI.h"

class Game : public QObject
{
    Q_OBJECT

public:
    Game();

    void set_board(BoardWidget * board_w);

    void start_multiplayer();
    void start_one_player();

signals:
    void update_msg_label(QString msg);

private slots:
    void board_clicked(Quad quad);

private:
    BoardWidget * board_widget;

    bool turn_x;
    bool active;

    bool one_player;

    void init();

    void clear();
    bool full();

    void turn_cleanup();
    void ai_goes();

    QString get_turn_piece();

    AI ai;

    QList<QString> board;

    // used for win detection
    QList<QList<Quad>> wins;

    void place(QString xo, Quad quad);
    bool quad_empty(Quad quad);

    QString winner();
    QList<Quad> quads_with_piece(QString piece);

    void define_winning_sets();
};

#endif // GAME_H
