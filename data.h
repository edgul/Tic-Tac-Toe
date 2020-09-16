#ifndef DATA_H
#define DATA_H

#define PLAYER_X  "X"
#define PLAYER_O  "O"

#include <QList>

const int NUM_CELLS = 9;

enum Target
{
    TARGET_NONE,
    TARGET_GAME
};

/*
client:
*******
GAME_START
GAME_PLACE Quad
GAME_QUIT PieceType

server:
*******
GAME_INIT PieceType
GAME_UPDATE Board
GAME_END PieceType
*/
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

// TODO: remove
enum Quad
{
    QUAD_TOP_LEFT  = 0,
    QUAD_TOP_MID   ,
    QUAD_TOP_RIGHT ,
    QUAD_MID_LEFT  ,
    QUAD_MID_MID   ,
    QUAD_MID_RIGHT ,
    QUAD_BOT_LEFT  ,
    QUAD_BOT_MID   ,
    QUAD_BOT_RIGHT ,
    QUAD_NONE
};

enum PieceType
{
    PIECE_TYPE_NONE,
    PIECE_TYPE_X,
    PIECE_TYPE_O
};

struct SimpleBoard
{
    QList<PieceType> board = { PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE,
                               PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE,
                               PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE
                             };
    SimpleBoard(QList<PieceType> board) : board(board) {}
};

#endif // DATA_H
