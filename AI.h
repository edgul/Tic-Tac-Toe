#ifndef AI_H
#define AI_H

#include <QList>
#include <QString>
#include "data/data.h"
#include "data/BoardModel.h"

class AI
{
public:
    AI();
    Cell getMove(SimpleBoard simpleBoard, PieceType piece, Difficulty difficulty);

private:
    Cell getOkayMove(SimpleBoard simpleBoard, PieceType piece);
    Cell getBestMove(SimpleBoard simpleBoard, PieceType piece);
    Cell getDumbassMove(SimpleBoard simpleBoard);
    Cell getRandomMove(SimpleBoard simpleBoard);
    Cell getHighestProductivityMove(SimpleBoard simpleBoard, PieceType piece);

    int productivity(Cell cell, SimpleBoard simpleBoard, PieceType piece);

};

#endif // AI_H
