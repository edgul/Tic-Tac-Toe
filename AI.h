#ifndef AI_H
#define AI_H

#include <QList>
#include <QString>
#include "data.h"
#include "Board.h"

class AI
{
public:
    AI();

    Quad get_move(Board board);

    Quad get_dumbass_move(Board board);

    Quad highest_productivity_move(Board board);

    void set_piece_type(QString piece);
    QString get_piece();

private:
    QString piece_type;

};

#endif // AI_H
