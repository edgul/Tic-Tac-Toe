#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include "data.h"

#define EMPTY_CELL "-"

class Board
{
public:
    Board();

    // modifiers
    void clear();
    void place(QString piece, Quad q);
    void set_board_from_string(QString b_string);

    // accessors
    bool full();
    bool quad_empty(Quad quad);
    QString winner();
    int pieces();
    int size();
    QString piece_at(int index);
    QList<Quad> quads_with_piece(QString piece);

    // put in AI
    int productivity(Quad move, QString piece_type); // number of possible wins from this quad placement
    QList<QList<Quad>> wins;
    Quad available_win(QString piece_type);

private:
    QList<QString> board;

    void define_winning_sets();
};

#endif // BOARD_H
