#ifndef AI_H
#define AI_H

#include <QList>
#include <QString>
#include "data.h"

#include "BoardModel.h"

class AI
{
public:
    AI();

    Cell getMove(SimpleBoard simpleBoard, PieceType piece, Difficulty difficulty);

    // TODO: remove
    Quad get_move(BoardModel board);
    Quad get_dumbass_move(BoardModel board);
    Quad highest_productivity_move(BoardModel board);
    void set_piece_type(QString piece);
    QString get_piece();
    void set_difficulty(Difficulty new_diff);
    Quad get_best_move(BoardModel board);

private:
    QString piece_type;
    Difficulty difficulty;

    Cell getOkayMove(SimpleBoard simpleBoard, PieceType piece);
    Cell getBestMove(SimpleBoard simpleBoard, PieceType piece);
    Cell getDumbassMove(SimpleBoard simpleBoard, PieceType piece);
    Cell getRandomMove(SimpleBoard simpleBoard, PieceType piece);
    Cell getHighestProductivityMove(SimpleBoard simpleBoard, PieceType piece);

    int productivity(Cell cell, SimpleBoard simpleBoard, PieceType piece);

};

#endif // AI_H
