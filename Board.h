#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include "data.h"

#define EMPTY_CELL "-"

class Board
{
public:
    Board();

    void clear();

    bool full();

    void place(QString piece, Quad q);

    bool quad_empty(Quad quad);

    QString winner();

    int pieces();
    int size();
    QString piece_at(int index);

    int productivity(Quad move, QString piece_type); // number of possible wins from this quad placement

    QList<Quad> quads_with_piece(QString piece);

    QList<QList<Quad>> wins;

    Quad available_win(QString piece_type);

    void set_board_from_string(QString b_string);
private:
    QList<QString> board;

    void define_winning_sets();

};

#endif // BOARD_H
