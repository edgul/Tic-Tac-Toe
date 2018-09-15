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

};

#endif // AI_H
