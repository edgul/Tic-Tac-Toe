#ifndef AI_H
#define AI_H

#include <QList>
#include <QString>
#include "data.h"
#include "Board.h"

enum Difficulty
{
    DIFFICULTY_EASY,
    DIFFICULTY_MEDIUM,
    DIFFICULTY_HARD
};

class AI
{
public:
    AI();

    Cell getMove(SimpleBoard simpleBoard, PieceType piece);

    // --
    Quad get_move(Board board);

    Quad get_dumbass_move(Board board);

    Quad highest_productivity_move(Board board);

    void set_piece_type(QString piece);
    QString get_piece();

    void set_difficulty(Difficulty new_diff);

    Quad get_best_move(Board board);

private:
    QString piece_type;

    Difficulty difficulty;

};

#endif // AI_H
