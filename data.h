#ifndef DATA_H
#define DATA_H

#define PLAYER_X "X"
#define PLAYER_O "O"

#define DELIMITER       "TTT "
#define SEPARATOR       " "

#define DELIMITER_LENGTH    4
#define FUNCTION_LENGTH     1

#define PID_LENGTH      4

#define PID_STATE "STAT"
#define PID_MOVE  "MOVE"
#define PID_HELLO "HELL"

#define PID_STATE_LENGTH (1)
#define PID_STATE_BOARD_LENGTH (9)

#define SERVER_OK   "SERVER_OK"
#define SERVER_BUSY "SERVER_BUSY"

enum Handshake
{
    HANDSHAKE_OK,
    HANDSHAKE_BUSY
};

enum Function
{
    FUNCTION_HANDSHAKE_REQUEST,
    FUNCTION_HANDSHAKE_RESPONSE,
    FUNCTION_MOVE,
    FUNCTION_UPDATE_BOARD,
    FUNCTION_HELLO_WORLD
};

enum Quad
{
    QUAD_TOP_LEFT = 0,
    QUAD_TOP_MID   ,
    QUAD_TOP_RIGHT ,
    QUAD_MID_LEFT  ,
    QUAD_MID_MID   ,
    QUAD_MID_RIGHT ,
    QUAD_BOT_LEFT  ,
    QUAD_BOT_MID   ,
    QUAD_BOT_RIGHT,
    QUAD_NONE
};

#endif // DATA_H
