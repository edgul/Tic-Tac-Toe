#ifndef DATA_H
#define DATA_H

#define PLAYER_X  "X"
#define PLAYER_O  "O"

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

#endif // DATA_H
