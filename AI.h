#ifndef AI_H
#define AI_H

#include <QList>
#include <QString>
#include "data.h"

class AI
{
public:
    AI();

    Quad get_move(QList<QString> board);
};

#endif // AI_H
