#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include "data.h"

class Board
{
public:
    Board();

    void clear();

    bool full();

    void place(QString piece, Quad q);

    bool quad_empty(Quad quad);

    QString winner();

    int size();
    QString piece_at(int index);

private:
    QList<QString> board;

    QList<Quad> quads_with_piece(QString piece);

    QList<QList<Quad>> wins;
    void define_winning_sets();


};

#endif // BOARD_H
