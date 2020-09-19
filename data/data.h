#ifndef DATA_H
#define DATA_H

#include <QList>
#include <QString>

const QString PIECE_STR_X = "X";
const QString PIECE_STR_O = "O";
const QString PIECE_STR_NONE = "-";

const int NUM_CELLS = 9;

enum Function
{
    FUNCTION_NONE,
    FUNCTION_GAME_START,
    FUNCTION_GAME_PLACE,
    FUNCTION_GAME_QUIT,
    FUNCTION_GAME_INIT,
    FUNCTION_GAME_UPDATE,
    FUNCTION_GAME_END
};

enum Cell
{
    CELL_TOP_LEFT  = 0,
    CELL_TOP_MID   ,
    CELL_TOP_RIGHT ,
    CELL_MID_LEFT  ,
    CELL_MID_MID   ,
    CELL_MID_RIGHT ,
    CELL_BOT_LEFT  ,
    CELL_BOT_MID   ,
    CELL_BOT_RIGHT ,
    CELL_NONE
};

enum PieceType
{
    PIECE_TYPE_NONE,
    PIECE_TYPE_X,
    PIECE_TYPE_O
};


enum Difficulty
{
    DIFFICULTY_EASY,
    DIFFICULTY_MEDIUM,
    DIFFICULTY_HARD,
    DIFFICULTY_NONE
};


struct SimpleBoard
{
    QList<PieceType> board = { PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE,
                               PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE,
                               PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE
                             };
    SimpleBoard() {}
    SimpleBoard(QList<PieceType> board) : board(board) {}
};

#endif // DATA_H
